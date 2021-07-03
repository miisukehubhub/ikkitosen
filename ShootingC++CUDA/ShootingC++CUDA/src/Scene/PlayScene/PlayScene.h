#ifndef PLAYSCENE_H_
#define PLAYSCENE_H_

#include <vector>
#include <memory>

#include "../Scene.h"

#include "../../UI/UI.h"
#include "../../UI/ProgressBar/ProgressBar.h"

// プレイシーン
class PlayScene : public Scene
{
public:

	PlayScene(); // コンストラクタ

	~PlayScene(); // デストラクタ

	// 初期化処理
	void Init() override;

	// 更新処理
	void Update() override;

	// 描画処理
	void Draw() override;

private:

	std::vector<std::shared_ptr<UI>> UIs{ std::vector<std::shared_ptr<UI>>() };
	std::weak_ptr<ProgressBar> m_playerHpBar;
	std::weak_ptr<ProgressBar> m_stageProgressBar;
	bool m_isClear{ false };
	bool m_isGameOver{ false };
	int m_toDeadTime{ 300 };
	int m_toDeadTimer{ 300 };
	int m_playPlayerDamageSoundTimer{ 0 };
};

#endif