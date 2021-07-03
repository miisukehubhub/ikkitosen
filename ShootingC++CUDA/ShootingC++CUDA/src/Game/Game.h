#ifndef GAME_H_
#define GAME_H_

#include <DxLib.h>

#include "../GameManager/GameManager.h"

#include "../Scene/Scene.h"
#include "../Scene/SceneID.h"

class Game
{
public:

	Game(); // コンストラクタ

	~Game(); // デストラクタ

	void Init(); // Init処理

	void Update(); // 更新処理

	void Draw(); // 描画処理

private:

	// シーンを変える
	void ChangeScene(SceneID sceneID);

private:

	GameManager& gm = GameManager::GetInstance();
};

#endif
