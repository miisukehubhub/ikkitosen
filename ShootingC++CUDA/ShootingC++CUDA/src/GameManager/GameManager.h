#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include "../Singleton/Singleton.h"

#include "../Scene/SceneID.h"

#include <DxLib.h>
#include <memory>
#include <vector>
#include <list>

class Scene;

enum class InputType : unsigned char
{
	DirectInput = 0,
	XInput,
};

class GameManager : public Singleton<GameManager>
{
public:

	friend class Singleton<GameManager>; // Singleton�ł̃C���X�^���X�쐬�͋���

	InputType playingInputType = InputType::XInput; // �g�p�������

	SceneID currentSceneID{ SceneID::Title }; // ���݂̃V�[����ID
	std::shared_ptr<Scene> currentScene; // ���݂̃V�[��
	int score{ 0 }; // �X�R�A
	int maxProgressValue{ 15000 };
	int progressValue{ 0 }; // �X�e�[�W�̐i�s�x
	int level{ 1 }; // ��Փx���x��

	// �폜�������e���v���[�g�֐��ɂ���
	template <typename T, class T_if>
	void EraseRemoveIf(std::vector<T>& v, T_if if_condition)
	{
		v.erase(
			std::remove_if(v.begin(), v.end(), if_condition),
			v.end()
		);
	}

	template <typename T, class T_if>
	void EraseRemoveIf(std::list<T>& v, T_if if_condition)
	{
		v.erase(
			std::remove_if(v.begin(), v.end(), if_condition),
			v.end()
		);
	}

protected:
	GameManager() {};

	virtual ~GameManager() {};
};

#endif
