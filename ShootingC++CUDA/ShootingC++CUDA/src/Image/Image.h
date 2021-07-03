#ifndef IMAGE_H_
#define IMAGE_H_

#include <unordered_map>
#include <DxLib.h>

#include "ImageID.h"
#include "../Scene/SceneID.h"

class Image
{
public:

	// �摜�̃��[�h
	static void Load(SceneID sceneID);

	// �摜�̏���
	static void Delete();

	// �摜�n���h�����擾
	static int At(const unsigned char imageID);

private:

	static void TitleSceneImageLoad(); // �^�C�g���V�[���̉摜�ǂݍ���
	static void PlaySceneImageLoad(); // �v���C�V�[���̉摜�ǂݍ���
	static void ClearSceneImageLoad(); // �N���A�V�[���̉摜�ǂݍ���
	static void GameOverSceneImageLoad(); // �Q�[���I�[�o�[�V�[���̉摜�ǂݍ���

private:

	static std::unordered_map<unsigned char, int> map; // �摜�̃}�b�v
};

#endif
