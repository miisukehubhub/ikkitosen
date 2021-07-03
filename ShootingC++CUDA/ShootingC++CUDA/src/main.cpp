#include <DxLib.h>
#include <stdio.h>
#include "MyTimer/MyTimer.h"

#include "Game/Game.h"
#include "Screen/Screen.h"

int TargetFPS = 60; // 目標のFPS
static bool EnableFrameSkip = true; // 高負荷時にスキップするか(falseは処理落ち)
double MaxAllowSkipTime = 0.2; // フレームスキップする最大間隔(秒)
long IntervalTicks = (long)(1.0 / TargetFPS * 10000000); // フレーム間のTick数
int MaxAllowSkipCount = (int)(TargetFPS * MaxAllowSkipTime);

static long nextFrameTicks = IntervalTicks; // 次のフレームの目標時刻
static int skipCount = 0; // 何回連続でフレームスキップしたか
static long fpsTicks = 0; // FPS計測のためのTicks
static int fpsFrameCount = 0; // FPS計測のためのフレームカウント

/// <summary>
/// 現在のFPS
/// </summary>
static float CurrentFPS;

static void GameDraw(Game& game)
{
	ClearDrawScreen(); // いったんキャンパスをまっさらに
	game.Draw(); // パラパラ漫画の描画処理
	ScreenFlip(); // 裏で描いておいたパラパラ漫画を表面に入れ替えフリップ
	skipCount = 0; // フレームスキップのカウントをリセット
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// Windowsの機能 このプログラム実行の処理優先度を上げる
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);
	// 垂直同期とはモニターへの描画が完了するまで処理全体を停止し、
	// 描画処理と更新処理の間隔を双方一定となるように処理の間隔を調整すること
	// 画面リフレッシュレートと目標フレームレートが等しい場合は垂直同期を有効に、等しくない場合は無効にする
	SetWaitVSyncFlag(GetRefreshRate() == TargetFPS ? TRUE : FALSE);

	// 画面モードの設定
	SetGraphMode(Screen::Width, Screen::Height, 32); // 画面サイズとカラービット数
	SetWindowSize(Screen::Width, Screen::Height); // ウィンドウサイズ(SetGraphModeのサイズと異なると歪む)
	ChangeWindowMode(TRUE); // フルスクリーンかウィンドウか
	SetAlwaysRunFlag(TRUE); // ウィンドウが非アクティブでも動作させる
	SetMainWindowText("イッキトウセン"); // この行のエラーはプロパティがダメな可能性あり

	if (DxLib_Init() < 0)
	{
		// エラーが発生したら直ちに終了
		return -1;
	}

	SetMouseDispFlag(TRUE); // FALSEでマウスカーソル非表示

	SetDrawScreen(DX_SCREEN_BACK);
	SetUseTransColor(FALSE); // 画像の指定色を透過する機能を無効化

	Game game;
	game.Init(); // gameの準備

	MyTimer& timer = MyTimer::GetInstance();
	ScreenFlip();

	timer.Init(); // 時刻計測開始

	// アニメーションにするにはwhile文
	while (ProcessMessage() == 0)
	{
		// FPSの計測(FPS = 1秒あたりのパラパラ漫画枚数)
		fpsFrameCount++;
		if (fpsFrameCount >= 60)
		{
			long elapsedTicks = timer.GetElapsedTicks() - fpsTicks;
			float elapsedSec = (float)elapsedTicks / 10000000;
			CurrentFPS = fpsFrameCount / elapsedSec; // 現在のFPS

			fpsFrameCount = 0; // 60枚超えたら0リセット
			// 60枚数えたら現在のFPSを記録
			fpsTicks = timer.GetElapsedTicks();
		}

		game.Update(); // gameの更新処理

		// スローモーション、早送り
		if (timer.isTimeScaleMode && timer.timeScale > 0)
		{	// フレームレートを再計算し早送りやスローモーション
			TargetFPS = (int)(60 / timer.timeScale); // 目標のFPS
			MaxAllowSkipTime = 0.2; // フレームスキップする最大間隔(秒)
			IntervalTicks = (long)(1.0 / TargetFPS * 10000000); // フレーム間のTick数
			MaxAllowSkipCount = (int)(TargetFPS * MaxAllowSkipTime);
		}
		// 垂直同期がDXで効いてるならDXライブラリにWait処理を任せられる(フレームスキップだけ自分でやる)
		if (GetWaitVSyncFlag() == TRUE && timer.isTimeScaleMode == false)
		{
			if (EnableFrameSkip)
			{	// 余った時刻 = 次のパラパラ予定時刻 - 現在の時刻
				long waitTicks = nextFrameTicks - timer.GetElapsedTicks();
				if (waitTicks < 0)
				{
					if (skipCount < MaxAllowSkipCount)
					{
						skipCount++; // フレームスキップ
					}
					else
					{
						nextFrameTicks = timer.GetElapsedTicks();
						GameDraw(game); // 限度超えでスロー描画処理に切り替え
					}
				}
				else
				{
					// DXライブラリが自動で液晶の60Hzとタイミングを合わせて描画
					GameDraw(game); // 描画処理
				}
				// 次のパラパラ予定時刻はIntervalTicksあと
				nextFrameTicks += IntervalTicks;
			}
			else
			{	// ここのelseは何があってもスキップしない設定のときに来る
				GameDraw(game); // スロー描画処理
			}
		}
		else
		{	// 垂直同期がDX設定で効いてないならWait処理を自力でやる(フレームスキップも自分でやる)
			long waitTicks = nextFrameTicks - timer.GetElapsedTicks(); // 余った時間(待機が必要な時間)
			if (EnableFrameSkip && waitTicks < 0)
			{
				if (skipCount < MaxAllowSkipCount)
				{
					skipCount++; // フレームスキップ
				}
				else
				{
					nextFrameTicks = timer.GetElapsedTicks();
					GameDraw(game); // 遅れつつもスローモーションで描いてゆく設定のときはここ
					SetMainWindowText("スロー");
				}
			}
			else
			{	// 自力でwait処理
				if (waitTicks > 20000) // あと2ミリ秒以上待つ必要がある
				{
					// Sleepは指定した時間でぴったり戻ってくるわけではないので、
					// 余裕をもって、待たなければならない時間 - 2ミリ秒Sleepする
					int waitMillsec = (int)(waitTicks / 10000) - 2;
					timer.SleepForMilliSec(waitMillsec);
				}

				// 時間が来るまで何もしないループを回して待機する
				while (timer.GetElapsedTicks() < nextFrameTicks)
				{
					// 所定の時間になるまで空ループ
				}

				GameDraw(game); // 所定の時間になったら描画処理
				SetMainWindowText("60FPS以内");
			}
			nextFrameTicks += IntervalTicks;
		}
	}

	// キー入力待ちをする
	WaitKey();

	// DXライブラリの後始末
	DxLib_End();

	// ソフトの終了
	return 0;
}