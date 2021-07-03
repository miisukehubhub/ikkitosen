#include "PlayScene.h"

#include <cuda_runtime.h>

#include "../../MyMemory/MyMemory.h"
#include "../../Screen/Screen.h"
#include "../../MyMath/MyMath.h"
#include "../../Image/Image.h"
#include "../../SE/SE.h"

#include "../../GameObjects/Player/Player.h"
#include "../../GameObjects/Boss/Boss.h"
#include "../../GameObjects/EnemySpawner/EnemySpawner.h"

#include "../../GameObjects/PlayerBullets/PlayerNormalBullet/PlayerNormalBullet.h"
#include "../../GameObjects/PlayerBullets/PlayerNormalBullet/Updater/PlayerNormalBulletUpdater.h"
#include "../../GameObjects/PlayerBullets/PlayerNormalBullet/Drawer/PlayerNormalBulletDrawer.h"

#include "../../GameObjects/PlayerBullets/PlayerScatterBullet/PlayerScatterBullet.h"
#include "../../GameObjects/PlayerBullets/PlayerScatterBullet/Updater/PlayerScatterBulletUpdater.h"
#include "../../GameObjects/PlayerBullets/PlayerScatterBullet/Drawer/PlayerScatterBulletDrawer.h"

#include "../../GameObjects/Enemy/Enemy.h"
#include "../../GameObjects/Enemy/Updater/EnemyUpdater.h"
#include "../../GameObjects/Enemy/Drawer/EnemyDrawer.h"
#include "../../GameObjects/Enemy/CollisionDetection/EnemyCollisionDetection.h"
#include "../../GameObjects/Enemy/BulletCreator/EnemyBulletCreator.h"

#include "../../GameObjects/EnemyBullet/EnemyBullet.h"
#include "../../GameObjects/EnemyBullet/Updater/EnemyBulletUpdater.h"
#include "../../GameObjects/EnemyBullet/Drawer/EnemyBulletDrawer.h"

PlayScene::PlayScene()
	: Scene()
{

}

PlayScene::~PlayScene()
{
	Image::Delete();
	MyMemory::Free(); // メモリ破棄

	// 掃除
	PlayerNormalBulletPtr::Init();
	PlayerScatterBulletPtr::Init();
	EnemyPtr::Init();
	EnemyBulletPtr::Init();
}

void PlayScene::Init()
{
	nextSceneID = SceneID::GameOver; // 次のシーンはゲームオーバー
	Image::Load(gm.currentSceneID);
	gm.score = 0;
	gm.progressValue = 15000;
	gm.level = 1;

	MyMemory::Malloc(); // メモリ確保

	PlayerPtr::Get();
	PlayerPtr::host[0] = Player(Vector2(100.0f, Screen::Height / 2.0f));
	PlayerNormalBulletPtr::Get();
	PlayerScatterBulletPtr::Get();
	EnemyPtr::Get();
	EnemySpawnerPtr::Get();
	EnemySpawnerPtr::host[0] = EnemySpawner();
	EnemySpawnerPtr::host->SetProportion(1, 0, 0);
	EnemySpawnerPtr::host->SetOneClusterNum(300);
	EnemyBulletPtr::Get();
	BossPtr::Get();

	// プログレスバーの生成
	auto pbp = std::make_shared<ProgressBar>(
		Vector2(10.f, 10.f), 300, 50,
		PlayerPtr::host->GetMaxHpPtr(), PlayerPtr::host->GetHpPtr(), GetColor(30, 200, 30));
	m_playerHpBar = pbp;
	UIs.push_back(pbp);

	pbp = std::make_shared<ProgressBar>(
		Vector2(1000.f, 10.f), 800, 50,
		&gm.maxProgressValue, &gm.progressValue, GetColor(200, 200, 30));
	m_stageProgressBar = pbp;
	UIs.push_back(pbp);

	PlayMusic("res/BGM/battle1_bgm.mp3", DX_PLAYTYPE_LOOP); // BGMを再生
}

void PlayScene::Update()
{
	// もしクリアかゲームオーバーになっていたら
	if (m_isClear || m_isGameOver)
	{
		if (m_toDeadTimer > 0)
		{
			m_toDeadTimer--;
			return;
		}
		m_isDead = true;
		return;
	}

	PlayerPtr::host->Update(); // プレイヤーの更新
	PlayerNormalBulletUpdater::Run(); // プレイヤー通常弾の更新
	PlayerScatterBulletUpdater::Run(); // プレイヤー散弾の更新
	EnemySpawnerPtr::host->Update(); // 敵スポナーの更新
	EnemyUpdater::Run(); // 敵の更新
	EnemyBulletCreator::Run(); // 敵弾を生成
	EnemyBulletUpdater::Run(); // 敵弾の更新
	if (gm.level == 4) BossPtr::host->Update(); // ボスの更新

	cudaStreamSynchronize(PlayerNormalBulletPtr::stream); // プレイヤー通常弾の処理が終わるのを待つるのを待つ
	cudaStreamSynchronize(PlayerScatterBulletPtr::stream); // プレイヤー散弾の処理が終わるのを待つ
	cudaStreamSynchronize(EnemyPtr::stream); // 敵の処理が終わるのを待つ

	EnemyCollisionDetection::Run(); // 敵の当たり判定処理

	cudaStreamSynchronize(EnemyBulletPtr::stream); // 敵弾の処理が終わるのを待つ

	int playerHp = *PlayerPtr::host->GetHpPtr(); // 前のプレイヤーのHPを保持しておく

	// 敵弾とプレイヤーの衝突判定
	for (int i = 0; i < EnemyBulletPtr::length; i++)
	{
		// プレイヤーが死んでいたら終わり
		if ((*PlayerPtr::host->GetStatePtr() & (unsigned char)PlayerState::IsDead) != 0) break;

		// 敵弾が死んでいたらスキップ
		if (EnemyBulletPtr::host[i].m_isDead) continue;

		if (MyMath::CircleCircleIntersection(PlayerPtr::host->GetPosition(), PlayerPtr::host->GetCollisionRadius(),
			EnemyBulletPtr::host[i].m_position, EnemyBulletPtr::host[i].m_collisionRadius))
		{
			PlayerPtr::host->TakeDamage();
			EnemyBulletPtr::host[i].m_isDead = true;
		}
	}

	cudaStreamSynchronize(EnemyPtr::stream); // 敵の処理を待つ

	// 敵とプレイヤーの衝突判定
	for (int i = 0; i < EnemyPtr::length; i++)
	{
		// プレイヤーが死んでいたら終わり
		if ((*PlayerPtr::host->GetStatePtr() & (unsigned char)PlayerState::IsDead) != 0) break;

		// 敵が死んでいたらスキップ
		if ((EnemyPtr::host[i].m_state & (unsigned char)EnemyState::IsDead) != 0) continue;

		if (MyMath::CircleCircleIntersection(PlayerPtr::host->GetPosition(), PlayerPtr::host->GetCollisionRadius(),
			EnemyPtr::host[i].m_position, EnemyPtr::host[i].m_collisionRadius))
		{
			PlayerPtr::host->TakeDamage();
		}
	}

	// 難易度レベルが4のとき
	if (gm.level == 4)
	{
		// プレイヤー通常弾とボスの衝突判定
		for (int i = 0; i < PlayerNormalBulletPtr::length; i++)
		{
			// ボスが死んでいたら終わり
			if ((BossPtr::host->GetState() & (unsigned char)BossState::IsDead) != 0) break;

			// プレイヤー通常弾が死んでいたらスキップ
			if (PlayerNormalBulletPtr::host[i].m_isDead) continue;

			if (MyMath::CircleCircleIntersection(PlayerNormalBulletPtr::host[i].m_position, PlayerNormalBulletPtr::host[i].m_collisionRadius,
				BossPtr::host->GetPosition(), BossPtr::host->GetCollisionRadius()))
			{
				BossPtr::host->TakeDamage(PlayerNormalBulletPtr::host[i].m_power);
			}
		}

		// プレイヤー散弾とボスの衝突判定
		for (int i = 0; i < PlayerScatterBulletPtr::length; i++)
		{
			// ボスが死んでいたら終わり
			if ((BossPtr::host->GetState() & (unsigned char)BossState::IsDead) != 0) break;

			// プレイヤー散弾が死んでいたらスキップ
			if (PlayerScatterBulletPtr::host[i].m_isDead) continue;

			if (MyMath::CircleCircleIntersection(PlayerScatterBulletPtr::host[i].m_position, PlayerScatterBulletPtr::host[i].m_collisionRadius,
				BossPtr::host->GetPosition(), BossPtr::host->GetCollisionRadius()))
			{
				BossPtr::host->TakeDamage(PlayerScatterBulletPtr::host[i].m_power);
				PlayerScatterBulletPtr::host[i].m_isDead = true;
			}
		}

		// プレイヤーとボスの衝突判定
		if (MyMath::CircleCircleIntersection(PlayerPtr::host->GetPosition(), PlayerPtr::host->GetCollisionRadius(),
			BossPtr::host->GetPosition(), BossPtr::host->GetCollisionRadius()))
		{
			PlayerPtr::host->TakeDamage();
		}
	}
	if (m_playPlayerDamageSoundTimer > 0)
	{
		m_playPlayerDamageSoundTimer--;
	}
	else
	{
		if (playerHp != *PlayerPtr::host->GetHpPtr())
		{
			m_playPlayerDamageSoundTimer = 3;
			PlaySoundMem(SE::At(SEID::Damaged), DX_PLAYTYPE_BACK); // 音を鳴らす
		}
	}

	cudaStreamSynchronize(EnemyPtr::stream); // 敵の処理を待つ
	EnemyPtr::EraseRemoveIfIsDead(); // 死んでいる敵を削除
	cudaStreamSynchronize(EnemyBulletPtr::stream); // 敵弾の処理を待つ
	EnemyBulletPtr::EraseRemoveIfIsDead(); // 死んでいる敵弾を削除
	cudaStreamSynchronize(PlayerNormalBulletPtr::stream); // プレイヤー通常弾の処理を待つ
	PlayerNormalBulletPtr::EraseRemoveIfIsDead(); // 死んでいるプレイヤー通常弾を削除
	cudaStreamSynchronize(PlayerScatterBulletPtr::stream); // プレイヤー散弾の処理を待つ
	PlayerScatterBulletPtr::EraseRemoveIfIsDead(); // 死んでいるプレイヤー散弾を削除する

	// 進行度がマックスになったら
	if (gm.progressValue <= 0 && gm.level != 4)
	{
		gm.progressValue += gm.maxProgressValue;
		gm.level++; // レベルを上げる
		if (gm.level == 4)
		{
			EnemySpawnerPtr::host->SetProportion(10, 10, 2); // 敵出現比率を変える
			EnemySpawnerPtr::host->SetOneClusterNum(200); // 敵出現数を変える
			BossPtr::host[0] = Boss(Vector2(Screen::Width + 100.0f, Screen::Height / 2.0f)); // ボスを出現させる
			m_stageProgressBar.lock()->ChangeReference(BossPtr::host->GetMaxHpPtr(), BossPtr::host->GetHpPtr());
			PlayMusic("res/BGM/boss_bgm.mp3", DX_PLAYTYPE_LOOP); // BGMを変える
			
			return;
		}
		if (gm.level == 3)
		{
			EnemySpawnerPtr::host->SetProportion(20, 10, 1); // 敵出現比率を変える
			EnemySpawnerPtr::host->SetOneClusterNum(280); // 敵出現数を変える
			PlayMusic("res/BGM/battle3_bgm.mp3", DX_PLAYTYPE_LOOP); // BGMを変える
			return;
		}
		if (gm.level == 2)
		{
			EnemySpawnerPtr::host->SetProportion(5, 2, 0); // 敵出現比率を変える
			EnemySpawnerPtr::host->SetOneClusterNum(320); // 敵出現数を変える
			PlayMusic("res/BGM/battle2_bgm.mp3", DX_PLAYTYPE_LOOP); // BGMを変える
			return;
		}
	}

	// UIの更新
	for (auto ui : UIs)
	{
		ui->Update();
	}

	// プレイヤーのHPが0以下だったら
	if (*PlayerPtr::host->GetHpPtr() <= 0)
	{
		m_isGameOver = true; // ゲームオーバーにする
		nextSceneID = SceneID::GameOver; // 次のシーンはゲームオーバー
		StopMusic(); // BGMを止める
		PlaySoundMem(SE::At(SEID::GameOver), DX_PLAYTYPE_BACK); // 音を鳴らす
		return;
	}
	// ボスのHPが0以下だったら
	if (gm.level == 4 && *BossPtr::host->GetHpPtr() <= 0)
	{
		m_isClear = true; // クリアにする
		nextSceneID = SceneID::Clear; // 次のシーンはクリア
		StopMusic(); // BGMを止める
		PlaySoundMem(SE::At(SEID::BossDead), DX_PLAYTYPE_BACK); // 音を鳴らす
		PlaySoundMem(SE::At(SEID::Clear), DX_PLAYTYPE_BACK); // 音を鳴らす
		return;
	}
}

void PlayScene::Draw()
{
	// 背景
	DrawGraph(0, 0, Image::At((unsigned char)PlaySceneImageID::BG), FALSE);

	// スコア表示
	DrawFormatString(0, 60, 255 << 16, "SCORE : %d", gm.score);

	PlayerNormalBulletDrawer::Run(); // プレイヤー通常弾描画
	PlayerScatterBulletDrawer::Run(); // プレイヤー散弾描画
	EnemyDrawer::Run(); // 敵描画
	EnemyBulletDrawer::Run(); // 敵弾描画

	if (gm.level == 4) BossPtr::host->Draw(); // ボス描画
	PlayerPtr::host->Draw(); // プレイヤー描画

	// UI描画
	for (auto ui : UIs)
	{
		ui->Draw();
	}

#ifdef _DEBUG

	DrawFormatString(0,  80, 255 << 8, "MemorySize    : %6d", MyMemory::usingSize);
	DrawFormatString(0, 100, 255 << 8, "NormalBullet  : %6d", PlayerNormalBulletPtr::length);
	DrawFormatString(0, 120, 255 << 8, "ScatterBullet : %6d", PlayerScatterBulletPtr::length);
	DrawFormatString(0, 140, 255 << 8, "Enemy         : %6d", EnemyPtr::length);
	DrawFormatString(0, 160, 255 << 8, "EnemyBullet   : %6d", EnemyBulletPtr::length);
	DrawFormatString(0, 200, 255 << 8, "進行度        : %6d", gm.progressValue);
	DrawFormatString(0, 220, 255 << 8, "レベル        : %6d", gm.level);

#endif

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (m_toDeadTime - m_toDeadTimer) * 255 / m_toDeadTime);
	if (m_isClear) DrawBox(0, 0, Screen::Width, Screen::Height, GetColor(255, 255, 255), TRUE);
	else if (m_isGameOver) DrawBox(0, 0, Screen::Width, Screen::Height, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}