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
	MyMemory::Free(); // �������j��

	// �|��
	PlayerNormalBulletPtr::Init();
	PlayerScatterBulletPtr::Init();
	EnemyPtr::Init();
	EnemyBulletPtr::Init();
}

void PlayScene::Init()
{
	nextSceneID = SceneID::GameOver; // ���̃V�[���̓Q�[���I�[�o�[
	Image::Load(gm.currentSceneID);
	gm.score = 0;
	gm.progressValue = 15000;
	gm.level = 1;

	MyMemory::Malloc(); // �������m��

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

	// �v���O���X�o�[�̐���
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

	PlayMusic("res/BGM/battle1_bgm.mp3", DX_PLAYTYPE_LOOP); // BGM���Đ�
}

void PlayScene::Update()
{
	// �����N���A���Q�[���I�[�o�[�ɂȂ��Ă�����
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

	PlayerPtr::host->Update(); // �v���C���[�̍X�V
	PlayerNormalBulletUpdater::Run(); // �v���C���[�ʏ�e�̍X�V
	PlayerScatterBulletUpdater::Run(); // �v���C���[�U�e�̍X�V
	EnemySpawnerPtr::host->Update(); // �G�X�|�i�[�̍X�V
	EnemyUpdater::Run(); // �G�̍X�V
	EnemyBulletCreator::Run(); // �G�e�𐶐�
	EnemyBulletUpdater::Run(); // �G�e�̍X�V
	if (gm.level == 4) BossPtr::host->Update(); // �{�X�̍X�V

	cudaStreamSynchronize(PlayerNormalBulletPtr::stream); // �v���C���[�ʏ�e�̏������I���̂�҂�̂�҂�
	cudaStreamSynchronize(PlayerScatterBulletPtr::stream); // �v���C���[�U�e�̏������I���̂�҂�
	cudaStreamSynchronize(EnemyPtr::stream); // �G�̏������I���̂�҂�

	EnemyCollisionDetection::Run(); // �G�̓����蔻�菈��

	cudaStreamSynchronize(EnemyBulletPtr::stream); // �G�e�̏������I���̂�҂�

	int playerHp = *PlayerPtr::host->GetHpPtr(); // �O�̃v���C���[��HP��ێ����Ă���

	// �G�e�ƃv���C���[�̏Փ˔���
	for (int i = 0; i < EnemyBulletPtr::length; i++)
	{
		// �v���C���[������ł�����I���
		if ((*PlayerPtr::host->GetStatePtr() & (unsigned char)PlayerState::IsDead) != 0) break;

		// �G�e������ł�����X�L�b�v
		if (EnemyBulletPtr::host[i].m_isDead) continue;

		if (MyMath::CircleCircleIntersection(PlayerPtr::host->GetPosition(), PlayerPtr::host->GetCollisionRadius(),
			EnemyBulletPtr::host[i].m_position, EnemyBulletPtr::host[i].m_collisionRadius))
		{
			PlayerPtr::host->TakeDamage();
			EnemyBulletPtr::host[i].m_isDead = true;
		}
	}

	cudaStreamSynchronize(EnemyPtr::stream); // �G�̏�����҂�

	// �G�ƃv���C���[�̏Փ˔���
	for (int i = 0; i < EnemyPtr::length; i++)
	{
		// �v���C���[������ł�����I���
		if ((*PlayerPtr::host->GetStatePtr() & (unsigned char)PlayerState::IsDead) != 0) break;

		// �G������ł�����X�L�b�v
		if ((EnemyPtr::host[i].m_state & (unsigned char)EnemyState::IsDead) != 0) continue;

		if (MyMath::CircleCircleIntersection(PlayerPtr::host->GetPosition(), PlayerPtr::host->GetCollisionRadius(),
			EnemyPtr::host[i].m_position, EnemyPtr::host[i].m_collisionRadius))
		{
			PlayerPtr::host->TakeDamage();
		}
	}

	// ��Փx���x����4�̂Ƃ�
	if (gm.level == 4)
	{
		// �v���C���[�ʏ�e�ƃ{�X�̏Փ˔���
		for (int i = 0; i < PlayerNormalBulletPtr::length; i++)
		{
			// �{�X������ł�����I���
			if ((BossPtr::host->GetState() & (unsigned char)BossState::IsDead) != 0) break;

			// �v���C���[�ʏ�e������ł�����X�L�b�v
			if (PlayerNormalBulletPtr::host[i].m_isDead) continue;

			if (MyMath::CircleCircleIntersection(PlayerNormalBulletPtr::host[i].m_position, PlayerNormalBulletPtr::host[i].m_collisionRadius,
				BossPtr::host->GetPosition(), BossPtr::host->GetCollisionRadius()))
			{
				BossPtr::host->TakeDamage(PlayerNormalBulletPtr::host[i].m_power);
			}
		}

		// �v���C���[�U�e�ƃ{�X�̏Փ˔���
		for (int i = 0; i < PlayerScatterBulletPtr::length; i++)
		{
			// �{�X������ł�����I���
			if ((BossPtr::host->GetState() & (unsigned char)BossState::IsDead) != 0) break;

			// �v���C���[�U�e������ł�����X�L�b�v
			if (PlayerScatterBulletPtr::host[i].m_isDead) continue;

			if (MyMath::CircleCircleIntersection(PlayerScatterBulletPtr::host[i].m_position, PlayerScatterBulletPtr::host[i].m_collisionRadius,
				BossPtr::host->GetPosition(), BossPtr::host->GetCollisionRadius()))
			{
				BossPtr::host->TakeDamage(PlayerScatterBulletPtr::host[i].m_power);
				PlayerScatterBulletPtr::host[i].m_isDead = true;
			}
		}

		// �v���C���[�ƃ{�X�̏Փ˔���
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
			PlaySoundMem(SE::At(SEID::Damaged), DX_PLAYTYPE_BACK); // ����炷
		}
	}

	cudaStreamSynchronize(EnemyPtr::stream); // �G�̏�����҂�
	EnemyPtr::EraseRemoveIfIsDead(); // ����ł���G���폜
	cudaStreamSynchronize(EnemyBulletPtr::stream); // �G�e�̏�����҂�
	EnemyBulletPtr::EraseRemoveIfIsDead(); // ����ł���G�e���폜
	cudaStreamSynchronize(PlayerNormalBulletPtr::stream); // �v���C���[�ʏ�e�̏�����҂�
	PlayerNormalBulletPtr::EraseRemoveIfIsDead(); // ����ł���v���C���[�ʏ�e���폜
	cudaStreamSynchronize(PlayerScatterBulletPtr::stream); // �v���C���[�U�e�̏�����҂�
	PlayerScatterBulletPtr::EraseRemoveIfIsDead(); // ����ł���v���C���[�U�e���폜����

	// �i�s�x���}�b�N�X�ɂȂ�����
	if (gm.progressValue <= 0 && gm.level != 4)
	{
		gm.progressValue += gm.maxProgressValue;
		gm.level++; // ���x�����グ��
		if (gm.level == 4)
		{
			EnemySpawnerPtr::host->SetProportion(10, 10, 2); // �G�o���䗦��ς���
			EnemySpawnerPtr::host->SetOneClusterNum(200); // �G�o������ς���
			BossPtr::host[0] = Boss(Vector2(Screen::Width + 100.0f, Screen::Height / 2.0f)); // �{�X���o��������
			m_stageProgressBar.lock()->ChangeReference(BossPtr::host->GetMaxHpPtr(), BossPtr::host->GetHpPtr());
			PlayMusic("res/BGM/boss_bgm.mp3", DX_PLAYTYPE_LOOP); // BGM��ς���
			
			return;
		}
		if (gm.level == 3)
		{
			EnemySpawnerPtr::host->SetProportion(20, 10, 1); // �G�o���䗦��ς���
			EnemySpawnerPtr::host->SetOneClusterNum(280); // �G�o������ς���
			PlayMusic("res/BGM/battle3_bgm.mp3", DX_PLAYTYPE_LOOP); // BGM��ς���
			return;
		}
		if (gm.level == 2)
		{
			EnemySpawnerPtr::host->SetProportion(5, 2, 0); // �G�o���䗦��ς���
			EnemySpawnerPtr::host->SetOneClusterNum(320); // �G�o������ς���
			PlayMusic("res/BGM/battle2_bgm.mp3", DX_PLAYTYPE_LOOP); // BGM��ς���
			return;
		}
	}

	// UI�̍X�V
	for (auto ui : UIs)
	{
		ui->Update();
	}

	// �v���C���[��HP��0�ȉ���������
	if (*PlayerPtr::host->GetHpPtr() <= 0)
	{
		m_isGameOver = true; // �Q�[���I�[�o�[�ɂ���
		nextSceneID = SceneID::GameOver; // ���̃V�[���̓Q�[���I�[�o�[
		StopMusic(); // BGM���~�߂�
		PlaySoundMem(SE::At(SEID::GameOver), DX_PLAYTYPE_BACK); // ����炷
		return;
	}
	// �{�X��HP��0�ȉ���������
	if (gm.level == 4 && *BossPtr::host->GetHpPtr() <= 0)
	{
		m_isClear = true; // �N���A�ɂ���
		nextSceneID = SceneID::Clear; // ���̃V�[���̓N���A
		StopMusic(); // BGM���~�߂�
		PlaySoundMem(SE::At(SEID::BossDead), DX_PLAYTYPE_BACK); // ����炷
		PlaySoundMem(SE::At(SEID::Clear), DX_PLAYTYPE_BACK); // ����炷
		return;
	}
}

void PlayScene::Draw()
{
	// �w�i
	DrawGraph(0, 0, Image::At((unsigned char)PlaySceneImageID::BG), FALSE);

	// �X�R�A�\��
	DrawFormatString(0, 60, 255 << 16, "SCORE : %d", gm.score);

	PlayerNormalBulletDrawer::Run(); // �v���C���[�ʏ�e�`��
	PlayerScatterBulletDrawer::Run(); // �v���C���[�U�e�`��
	EnemyDrawer::Run(); // �G�`��
	EnemyBulletDrawer::Run(); // �G�e�`��

	if (gm.level == 4) BossPtr::host->Draw(); // �{�X�`��
	PlayerPtr::host->Draw(); // �v���C���[�`��

	// UI�`��
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
	DrawFormatString(0, 200, 255 << 8, "�i�s�x        : %6d", gm.progressValue);
	DrawFormatString(0, 220, 255 << 8, "���x��        : %6d", gm.level);

#endif

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (m_toDeadTime - m_toDeadTimer) * 255 / m_toDeadTime);
	if (m_isClear) DrawBox(0, 0, Screen::Width, Screen::Height, GetColor(255, 255, 255), TRUE);
	else if (m_isGameOver) DrawBox(0, 0, Screen::Width, Screen::Height, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}