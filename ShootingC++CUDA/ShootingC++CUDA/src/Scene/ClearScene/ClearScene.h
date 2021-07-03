#ifndef CLEARSCENE_H_
#define CLEARSCENE_H_

#include "../Scene.h"

// クリアシーン
class ClearScene : public Scene
{
public:

	ClearScene(); // コンストラクタ

	~ClearScene(); // デストラクタ

	// 初期化処理
	void Init() override;

	// 更新処理
	void Update() override;

	// 描画処理
	void Draw() override;

private:

	int m_toAllowActionTime{ 150 };
	int m_toAllowActionTimer{ 150 };
};

#endif