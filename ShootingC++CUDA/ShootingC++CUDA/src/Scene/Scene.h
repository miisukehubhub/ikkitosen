#ifndef SCENE_H_
#define SCENE_H_

#include "../GameManager/GameManager.h"

#include "SceneID.h"
#include "../Image/Image.h"

// シーンの基底クラス
class Scene
{
protected:

	GameManager& gm = GameManager::GetInstance();

	bool m_isDead{ false };

	SceneID nextSceneID{ SceneID::Title };

public:

	Scene() {}; // コンストラクタ

	virtual ~Scene() {}; // デストラクタ

	virtual void Init() = 0; // 初期化処理

	virtual void Update() = 0; // 更新処理

	virtual void Draw() = 0; // 描画処理

	// isDeadを取得
	bool GetIsDead() const
	{
		return m_isDead;
	}

	// isDeadをセット
	void SetIsDead(const bool isDead)
	{
		this->m_isDead = isDead;
	}

	// 次のシーンを取得
	SceneID GetNextSceneID() const
	{
		return nextSceneID;
	}

	void SetNextSceneID(const SceneID id)
	{
		this->nextSceneID = id;
	}
};

#endif
