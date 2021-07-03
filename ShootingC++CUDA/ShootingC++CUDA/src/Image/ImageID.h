#ifndef IMAGEID_H_
#define IMAGEID_H_

// タイトルシーンの画像ID
enum class TitleSceneImageID : unsigned char
{
	BG,
	Text,
};

// プレイシーンの画像ID
enum class PlaySceneImageID : unsigned char
{
	Enemy,
	Player,
	PlayerNormalBullet,
	PlayerScatterBullet,
	Boss,
	BG,
};

// クリアシーンの画像ID
enum class ClearSceneImageID : unsigned char
{
	BG,
};

// ゲームオーバーシーンの画像ID
enum class GameOverSceneImageID : unsigned char
{
	BG,
};

#endif