#ifndef MYTIMER_H_
#define MYTIMER_H_

#include<chrono> // 精度の高い時刻を得る
#include<thread> // 処理休止sleep_forするために必要
#include<vector>
#include<map> // 辞書型連想配列に必要
#include<memory>
#include<string>
#include<sstream> // ostringstreamに必要
#include<iomanip> // 時間の文字列出力put_time()に必要

#include"../Singleton/Singleton.h"

class MyTimer : public Singleton<MyTimer>
{
public:
	friend class Singleton<MyTimer>;

	// 最初にsystem_clockとsteady_clockの両方で現在時間を取得
	// system_clockはOSの時刻
	// steady_clockはOSに依存しない時刻
	std::chrono::system_clock::time_point systemInitTime = std::chrono::system_clock::now();
	std::chrono::steady_clock::time_point steadyInitTime = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point steadyNowTime = std::chrono::steady_clock::now();

	std::chrono::system_clock::time_point systemTimeFromStart = UpdateSystemTimeFromStart();

	// 時間を保管する文字列  UpdateSystemTimeFromStart()呼ばないうちは更新されない
	std::string timeStringSystemClock = GetTimeString("%Y年%m月%d日%H時%M分%S秒");
	float timeScale = 1.0f; // main.cppで画面を描く速度と連動させてスローモーションや早送りも
	bool isTimeScaleMode = false; // スローモーション、早送りモードをON,OFF

	// 起動時の記録の初期化/リセット
	void Init()
	{
		// 最初にsystem_clockとsteady_clockの両方で現在時間を取得
		systemInitTime = std::chrono::system_clock::now();
		steadyInitTime = std::chrono::steady_clock::now();
	}

	// 現時刻をOSに左右されず求める
	std::chrono::system_clock::time_point UpdateSystemTimeFromStart()
	{
		steadyNowTime = std::chrono::steady_clock::now(); // 現時刻を得る
		// 開始時のsteady_clock::nowとの差を取って、開始時のsystem_clock::nowに足す
		systemTimeFromStart = systemInitTime + std::chrono::duration_cast<std::chrono::seconds>(steadyNowTime - steadyInitTime);
		return systemTimeFromStart;
	}

	// 現時刻を特定の文字列フォーマットで得る
	// 出力は"%c"ならフォーマットは[Mon Nov 27 10:58:32 2017]
	// "%Y年%m月%d日%H時%M分%S秒"なら[2020年12月11日14時30分15秒](デフォルト)
	std::string GetTimeString(const char* timeStringFormat = "%Y年%m月%d日%H時%M分%S秒")
	{
		systemTimeFromStart = UpdateSystemTimeFromStart(); // 現時刻をOSに左右されず得る

		// 時刻タイプ型をsystem_clockのtime_point型からtime_t型に変換する
		std::time_t timeFromStart = std::chrono::system_clock::to_time_t(systemTimeFromStart);
		// ローカルタイムを得る
		struct tm localTimeFromStart;
		localtime_s(&localTimeFromStart, &timeFromStart);
		std::ostringstream oss;
		oss << std::put_time(&localTimeFromStart, timeStringFormat) << std::endl;

		timeStringSystemClock = oss.std::ostringstream::str(); // str()で文字列string化して保存
		return timeStringSystemClock; // 現時刻を文字悦として返す
	}

	// Initしてから現在までの経過時間を得る(単位Tick = 100ナノ秒 = 1/10000000秒)
	long GetElapsedTicks()
	{	// 時刻を更新
		UpdateSystemTimeFromStart();
		// Initしてから現在までの経過時間(ナノ秒)
		auto durationFromInit = std::chrono::duration_cast<std::chrono::nanoseconds>(steadyNowTime - steadyInitTime);
		return (long)(durationFromInit.count() / 100);
	}

	// 指定ナノ秒 プログラムを休止
	void SleepForNanoSec(int waittime)
	{
		std::this_thread::sleep_for(std::chrono::nanoseconds(waittime));
	}

	// 指定マイクロ秒 プログラムを休止
	void SleepForMicroSec(int waittime)
	{
		std::this_thread::sleep_for(std::chrono::microseconds(waittime));
	}

	// 指定ミリ秒 プログラムを休止
	void SleepForMilliSec(int waittime)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(waittime));
	}

	// 指定 秒 プログラムを休止
	void SleepForSec(int waittime)
	{
		std::this_thread::sleep_for(std::chrono::seconds(waittime));
	}

	// 指定 分 プログラムを休止
	void SleepForMinutes(int waittime)
	{
		std::this_thread::sleep_for(std::chrono::minutes(waittime));
	}

protected:
	// 外部からのインスタンス作成は禁止
	MyTimer() {};
	// 外部からのインスタンス破棄も禁止
	virtual ~MyTimer() {};
};

#endif
