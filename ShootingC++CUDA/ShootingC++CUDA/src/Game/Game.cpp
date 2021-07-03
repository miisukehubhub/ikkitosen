#include "Game.h"

#include "../Input/DInput.h"
#include "../Input/XInput.h"
#include "../Input/MouseInput.h"
#include "../SE/SE.h"

// �V�[��include
#include "../Scene/TitleScene/TitleScene.h"
#include "../Scene/PlayScene/PlayScene.h"
#include "../Scene/GameOverScene/GameOverScene.h"
#include "../Scene/ClearScene/ClearScene.h"

Game::Game()
{
}

Game::~Game()
{

}

void Game::Init()
{
	DInput::Init(); // DirectInput�̏�����
	XInput::Init(); // XInput�̏�����
	MouseInput::Init(); // MouseInput�̏�����
	SE::Load(); // SE�̓ǂݍ���

	ChangeScene(gm.currentSceneID);
}

void Game::Update()
{
	DInput::Update();
	XInput::Update();
	MouseInput::Update();

	// ���݂̃V�[��������ł����玟�̃V�[���Ɉڍs
	if (gm.currentScene->GetIsDead())
	{
		gm.currentSceneID = gm.currentScene->GetNextSceneID();
		ChangeScene(gm.currentSceneID);
	}

	// ���݂̃V�[���̍X�V
	gm.currentScene->Update();
}

void Game::Draw()
{
	// ���݂̃V�[���̕`��
	gm.currentScene->Draw();
}

void Game::ChangeScene(SceneID sceneID)
{
	if (sceneID == SceneID::Title) gm.currentScene = std::make_shared<TitleScene>();
	else if (sceneID == SceneID::Play) gm.currentScene = std::make_shared<PlayScene>();
	else if (sceneID == SceneID::GameOver) gm.currentScene = std::make_shared<GameOverScene>();
	else if (sceneID == SceneID::Clear) gm.currentScene = std::make_shared<ClearScene>();

	gm.currentScene->Init();
}