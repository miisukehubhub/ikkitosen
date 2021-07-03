#ifndef IMAGE_H_
#define IMAGE_H_

#include <unordered_map>
#include <DxLib.h>

#include "ImageID.h"
#include "../Scene/SceneID.h"

class Image
{
public:

	// 画像のロード
	static void Load(SceneID sceneID);

	// 画像の消去
	static void Delete();

	// 画像ハンドルを取得
	static int At(const unsigned char imageID);

private:

	static void TitleSceneImageLoad(); // タイトルシーンの画像読み込み
	static void PlaySceneImageLoad(); // プレイシーンの画像読み込み
	static void ClearSceneImageLoad(); // クリアシーンの画像読み込み
	static void GameOverSceneImageLoad(); // ゲームオーバーシーンの画像読み込み

private:

	static std::unordered_map<unsigned char, int> map; // 画像のマップ
};

#endif
