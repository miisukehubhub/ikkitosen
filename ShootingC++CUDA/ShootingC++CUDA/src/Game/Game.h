#ifndef GAME_H_
#define GAME_H_

#include <DxLib.h>

#include "../GameManager/GameManager.h"

#include "../Scene/Scene.h"
#include "../Scene/SceneID.h"

class Game
{
public:

	Game(); // �R���X�g���N�^

	~Game(); // �f�X�g���N�^

	void Init(); // Init����

	void Update(); // �X�V����

	void Draw(); // �`�揈��

private:

	// �V�[����ς���
	void ChangeScene(SceneID sceneID);

private:

	GameManager& gm = GameManager::GetInstance();
};

#endif
