#ifndef IMAGEID_H_
#define IMAGEID_H_

// �^�C�g���V�[���̉摜ID
enum class TitleSceneImageID : unsigned char
{
	BG,
	Text,
};

// �v���C�V�[���̉摜ID
enum class PlaySceneImageID : unsigned char
{
	Enemy,
	Player,
	PlayerNormalBullet,
	PlayerScatterBullet,
	Boss,
	BG,
};

// �N���A�V�[���̉摜ID
enum class ClearSceneImageID : unsigned char
{
	BG,
};

// �Q�[���I�[�o�[�V�[���̉摜ID
enum class GameOverSceneImageID : unsigned char
{
	BG,
};

#endif