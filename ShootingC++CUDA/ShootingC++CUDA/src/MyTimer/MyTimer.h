#ifndef MYTIMER_H_
#define MYTIMER_H_

#include<chrono> // ���x�̍��������𓾂�
#include<thread> // �����x�~sleep_for���邽�߂ɕK�v
#include<vector>
#include<map> // �����^�A�z�z��ɕK�v
#include<memory>
#include<string>
#include<sstream> // ostringstream�ɕK�v
#include<iomanip> // ���Ԃ̕�����o��put_time()�ɕK�v

#include"../Singleton/Singleton.h"

class MyTimer : public Singleton<MyTimer>
{
public:
	friend class Singleton<MyTimer>;

	// �ŏ���system_clock��steady_clock�̗����Ō��ݎ��Ԃ��擾
	// system_clock��OS�̎���
	// steady_clock��OS�Ɉˑ����Ȃ�����
	std::chrono::system_clock::time_point systemInitTime = std::chrono::system_clock::now();
	std::chrono::steady_clock::time_point steadyInitTime = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point steadyNowTime = std::chrono::steady_clock::now();

	std::chrono::system_clock::time_point systemTimeFromStart = UpdateSystemTimeFromStart();

	// ���Ԃ�ۊǂ��镶����  UpdateSystemTimeFromStart()�Ă΂Ȃ������͍X�V����Ȃ�
	std::string timeStringSystemClock = GetTimeString("%Y�N%m��%d��%H��%M��%S�b");
	float timeScale = 1.0f; // main.cpp�ŉ�ʂ�`�����x�ƘA�������ăX���[���[�V�����⑁�����
	bool isTimeScaleMode = false; // �X���[���[�V�����A�����胂�[�h��ON,OFF

	// �N�����̋L�^�̏�����/���Z�b�g
	void Init()
	{
		// �ŏ���system_clock��steady_clock�̗����Ō��ݎ��Ԃ��擾
		systemInitTime = std::chrono::system_clock::now();
		steadyInitTime = std::chrono::steady_clock::now();
	}

	// ��������OS�ɍ��E���ꂸ���߂�
	std::chrono::system_clock::time_point UpdateSystemTimeFromStart()
	{
		steadyNowTime = std::chrono::steady_clock::now(); // �������𓾂�
		// �J�n����steady_clock::now�Ƃ̍�������āA�J�n����system_clock::now�ɑ���
		systemTimeFromStart = systemInitTime + std::chrono::duration_cast<std::chrono::seconds>(steadyNowTime - steadyInitTime);
		return systemTimeFromStart;
	}

	// �����������̕�����t�H�[�}�b�g�œ���
	// �o�͂�"%c"�Ȃ�t�H�[�}�b�g��[Mon Nov 27 10:58:32 2017]
	// "%Y�N%m��%d��%H��%M��%S�b"�Ȃ�[2020�N12��11��14��30��15�b](�f�t�H���g)
	std::string GetTimeString(const char* timeStringFormat = "%Y�N%m��%d��%H��%M��%S�b")
	{
		systemTimeFromStart = UpdateSystemTimeFromStart(); // ��������OS�ɍ��E���ꂸ����

		// �����^�C�v�^��system_clock��time_point�^����time_t�^�ɕϊ�����
		std::time_t timeFromStart = std::chrono::system_clock::to_time_t(systemTimeFromStart);
		// ���[�J���^�C���𓾂�
		struct tm localTimeFromStart;
		localtime_s(&localTimeFromStart, &timeFromStart);
		std::ostringstream oss;
		oss << std::put_time(&localTimeFromStart, timeStringFormat) << std::endl;

		timeStringSystemClock = oss.std::ostringstream::str(); // str()�ŕ�����string�����ĕۑ�
		return timeStringSystemClock; // �������𕶎��x�Ƃ��ĕԂ�
	}

	// Init���Ă��猻�݂܂ł̌o�ߎ��Ԃ𓾂�(�P��Tick = 100�i�m�b = 1/10000000�b)
	long GetElapsedTicks()
	{	// �������X�V
		UpdateSystemTimeFromStart();
		// Init���Ă��猻�݂܂ł̌o�ߎ���(�i�m�b)
		auto durationFromInit = std::chrono::duration_cast<std::chrono::nanoseconds>(steadyNowTime - steadyInitTime);
		return (long)(durationFromInit.count() / 100);
	}

	// �w��i�m�b �v���O�������x�~
	void SleepForNanoSec(int waittime)
	{
		std::this_thread::sleep_for(std::chrono::nanoseconds(waittime));
	}

	// �w��}�C�N���b �v���O�������x�~
	void SleepForMicroSec(int waittime)
	{
		std::this_thread::sleep_for(std::chrono::microseconds(waittime));
	}

	// �w��~���b �v���O�������x�~
	void SleepForMilliSec(int waittime)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(waittime));
	}

	// �w�� �b �v���O�������x�~
	void SleepForSec(int waittime)
	{
		std::this_thread::sleep_for(std::chrono::seconds(waittime));
	}

	// �w�� �� �v���O�������x�~
	void SleepForMinutes(int waittime)
	{
		std::this_thread::sleep_for(std::chrono::minutes(waittime));
	}

protected:
	// �O������̃C���X�^���X�쐬�͋֎~
	MyTimer() {};
	// �O������̃C���X�^���X�j�����֎~
	virtual ~MyTimer() {};
};

#endif
