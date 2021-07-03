#ifndef TITLESCENE_H_
#define TITLESCENE_H_

#include <vector>
#include <memory>

#include "../Scene.h"

#include "../../UI/UI.h"
#include "../../UI/Button/Button.h"

// タイトルシーン
class TitleScene : public Scene
{
public:

	TitleScene(); // コンストラクタ

	~TitleScene(); // デストラクタ

	// 初期化処理
	void Init() override;

	// 更新処理
	void Update() override;

	// 描画処理
	void Draw() override;

private:

	std::vector<std::shared_ptr<UI>> UIs{ std::vector<std::shared_ptr<UI>>() };
	std::weak_ptr<UI> DirectInputButton;
	std::weak_ptr<UI> XInputButton;
};

#endif