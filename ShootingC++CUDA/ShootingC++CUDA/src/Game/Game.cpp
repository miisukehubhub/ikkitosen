#include "Game.h"

#include "../Input/DInput.h"
#include "../Input/XInput.h"
#include "../Input/MouseInput.h"
#include "../SE/SE.h"

// シーンinclude
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
	DInput::Init(); // DirectInputの初期化
	XInput::Init(); // XInputの初期化
	MouseInput::Init(); // MouseInputの初期化
	SE::Load(); // SEの読み込み

	ChangeScene(gm.currentSceneID);
}

void Game::Update()
{
	DInput::Update();
	XInput::Update();
	MouseInput::Update();

	// 現在のシーンが死んでいたら次のシーンに移行
	if (gm.currentScene->GetIsDead())
	{
		gm.currentSceneID = gm.currentScene->GetNextSceneID();
		ChangeScene(gm.currentSceneID);
	}

	// 現在のシーンの更新
	gm.currentScene->Update();
}

void Game::Draw()
{
	// 現在のシーンの描画
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