#include <DxLib.h>
#include <stdio.h>
#include "MyTimer/MyTimer.h"

#include "Game/Game.h"
#include "Screen/Screen.h"

int TargetFPS = 60; // �ڕW��FPS
static bool EnableFrameSkip = true; // �����׎��ɃX�L�b�v���邩(false�͏�������)
double MaxAllowSkipTime = 0.2; // �t���[���X�L�b�v����ő�Ԋu(�b)
long IntervalTicks = (long)(1.0 / TargetFPS * 10000000); // �t���[���Ԃ�Tick��
int MaxAllowSkipCount = (int)(TargetFPS * MaxAllowSkipTime);

static long nextFrameTicks = IntervalTicks; // ���̃t���[���̖ڕW����
static int skipCount = 0; // ����A���Ńt���[���X�L�b�v������
static long fpsTicks = 0; // FPS�v���̂��߂�Ticks
static int fpsFrameCount = 0; // FPS�v���̂��߂̃t���[���J�E���g

/// <summary>
/// ���݂�FPS
/// </summary>
static float CurrentFPS;

static void GameDraw(Game& game)
{
	ClearDrawScreen(); // ��������L�����p�X���܂������
	game.Draw(); // �p���p������̕`�揈��
	ScreenFlip(); // ���ŕ`���Ă������p���p�������\�ʂɓ���ւ��t���b�v
	skipCount = 0; // �t���[���X�L�b�v�̃J�E���g�����Z�b�g
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// Windows�̋@�\ ���̃v���O�������s�̏����D��x���グ��
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);
	// ���������Ƃ̓��j�^�[�ւ̕`�悪��������܂ŏ����S�̂��~���A
	// �`�揈���ƍX�V�����̊Ԋu��o�����ƂȂ�悤�ɏ����̊Ԋu�𒲐����邱��
	// ��ʃ��t���b�V�����[�g�ƖڕW�t���[�����[�g���������ꍇ�͐���������L���ɁA�������Ȃ��ꍇ�͖����ɂ���
	SetWaitVSyncFlag(GetRefreshRate() == TargetFPS ? TRUE : FALSE);

	// ��ʃ��[�h�̐ݒ�
	SetGraphMode(Screen::Width, Screen::Height, 32); // ��ʃT�C�Y�ƃJ���[�r�b�g��
	SetWindowSize(Screen::Width, Screen::Height); // �E�B���h�E�T�C�Y(SetGraphMode�̃T�C�Y�ƈقȂ�Ƙc��)
	ChangeWindowMode(TRUE); // �t���X�N���[�����E�B���h�E��
	SetAlwaysRunFlag(TRUE); // �E�B���h�E����A�N�e�B�u�ł����삳����
	SetMainWindowText("�C�b�L�g�E�Z��"); // ���̍s�̃G���[�̓v���p�e�B���_���ȉ\������

	if (DxLib_Init() < 0)
	{
		// �G���[�����������璼���ɏI��
		return -1;
	}

	SetMouseDispFlag(TRUE); // FALSE�Ń}�E�X�J�[�\����\��

	SetDrawScreen(DX_SCREEN_BACK);
	SetUseTransColor(FALSE); // �摜�̎w��F�𓧉߂���@�\�𖳌���

	Game game;
	game.Init(); // game�̏���

	MyTimer& timer = MyTimer::GetInstance();
	ScreenFlip();

	timer.Init(); // �����v���J�n

	// �A�j���[�V�����ɂ���ɂ�while��
	while (ProcessMessage() == 0)
	{
		// FPS�̌v��(FPS = 1�b������̃p���p�����文��)
		fpsFrameCount++;
		if (fpsFrameCount >= 60)
		{
			long elapsedTicks = timer.GetElapsedTicks() - fpsTicks;
			float elapsedSec = (float)elapsedTicks / 10000000;
			CurrentFPS = fpsFrameCount / elapsedSec; // ���݂�FPS

			fpsFrameCount = 0; // 60����������0���Z�b�g
			// 60���������猻�݂�FPS���L�^
			fpsTicks = timer.GetElapsedTicks();
		}

		game.Update(); // game�̍X�V����

		// �X���[���[�V�����A������
		if (timer.isTimeScaleMode && timer.timeScale > 0)
		{	// �t���[�����[�g���Čv�Z���������X���[���[�V����
			TargetFPS = (int)(60 / timer.timeScale); // �ڕW��FPS
			MaxAllowSkipTime = 0.2; // �t���[���X�L�b�v����ő�Ԋu(�b)
			IntervalTicks = (long)(1.0 / TargetFPS * 10000000); // �t���[���Ԃ�Tick��
			MaxAllowSkipCount = (int)(TargetFPS * MaxAllowSkipTime);
		}
		// ����������DX�Ō����Ă�Ȃ�DX���C�u������Wait������C������(�t���[���X�L�b�v���������ł��)
		if (GetWaitVSyncFlag() == TRUE && timer.isTimeScaleMode == false)
		{
			if (EnableFrameSkip)
			{	// �]�������� = ���̃p���p���\�莞�� - ���݂̎���
				long waitTicks = nextFrameTicks - timer.GetElapsedTicks();
				if (waitTicks < 0)
				{
					if (skipCount < MaxAllowSkipCount)
					{
						skipCount++; // �t���[���X�L�b�v
					}
					else
					{
						nextFrameTicks = timer.GetElapsedTicks();
						GameDraw(game); // ���x�����ŃX���[�`�揈���ɐ؂�ւ�
					}
				}
				else
				{
					// DX���C�u�����������ŉt����60Hz�ƃ^�C�~���O�����킹�ĕ`��
					GameDraw(game); // �`�揈��
				}
				// ���̃p���p���\�莞����IntervalTicks����
				nextFrameTicks += IntervalTicks;
			}
			else
			{	// ������else�͉��������Ă��X�L�b�v���Ȃ��ݒ�̂Ƃ��ɗ���
				GameDraw(game); // �X���[�`�揈��
			}
		}
		else
		{	// ����������DX�ݒ�Ō����ĂȂ��Ȃ�Wait���������͂ł��(�t���[���X�L�b�v�������ł��)
			long waitTicks = nextFrameTicks - timer.GetElapsedTicks(); // �]��������(�ҋ@���K�v�Ȏ���)
			if (EnableFrameSkip && waitTicks < 0)
			{
				if (skipCount < MaxAllowSkipCount)
				{
					skipCount++; // �t���[���X�L�b�v
				}
				else
				{
					nextFrameTicks = timer.GetElapsedTicks();
					GameDraw(game); // �x����X���[���[�V�����ŕ`���Ă䂭�ݒ�̂Ƃ��͂���
					SetMainWindowText("�X���[");
				}
			}
			else
			{	// ���͂�wait����
				if (waitTicks > 20000) // ����2�~���b�ȏ�҂K�v������
				{
					// Sleep�͎w�肵�����Ԃł҂�����߂��Ă���킯�ł͂Ȃ��̂ŁA
					// �]�T�������āA�҂��Ȃ���΂Ȃ�Ȃ����� - 2�~���bSleep����
					int waitMillsec = (int)(waitTicks / 10000) - 2;
					timer.SleepForMilliSec(waitMillsec);
				}

				// ���Ԃ�����܂ŉ������Ȃ����[�v���񂵂đҋ@����
				while (timer.GetElapsedTicks() < nextFrameTicks)
				{
					// ����̎��ԂɂȂ�܂ŋ󃋁[�v
				}

				GameDraw(game); // ����̎��ԂɂȂ�����`�揈��
				SetMainWindowText("60FPS�ȓ�");
			}
			nextFrameTicks += IntervalTicks;
		}
	}

	// �L�[���͑҂�������
	WaitKey();

	// DX���C�u�����̌�n��
	DxLib_End();

	// �\�t�g�̏I��
	return 0;
}