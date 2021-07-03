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

	friend class Singleton<GameManager>; // Singletonでのインスタンス作成は許可

	InputType playingInputType = InputType::XInput; // 使用する入力

	SceneID currentSceneID{ SceneID::Title }; // 現在のシーンのID
	std::shared_ptr<Scene> currentScene; // 現在のシーン
	int score{ 0 }; // スコア
	int maxProgressValue{ 15000 };
	int progressValue{ 0 }; // ステージの進行度
	int level{ 1 }; // 難易度レベル

	// 削除処理をテンプレート関数にする
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
