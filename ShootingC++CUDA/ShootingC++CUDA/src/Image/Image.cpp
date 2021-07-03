#include "Image.h"

std::unordered_map<unsigned char, int> Image::map = std::unordered_map<unsigned char, int>();

void Image::Load(SceneID sceneID)
{
	// シーンによってロードする画像を変える
	if (sceneID == SceneID::Title) TitleSceneImageLoad();
	else if (sceneID == SceneID::Play) PlaySceneImageLoad();
	else if (sceneID == SceneID::Clear)ClearSceneImageLoad();
	else if (sceneID == SceneID::GameOver) GameOverSceneImageLoad();
}

void Image::Delete()
{
	// 読み込んだ画像を破棄する
	for (auto itr = map.begin(); itr != map.end(); ++itr)
	{
		DeleteGraph(itr->second);
	}

	// マップの要素を削除する
	map.erase(map.begin(), map.end());
}

int Image::At(const unsigned char imageID)
{
	return map[imageID];
}

void Image::TitleSceneImageLoad()
{
	map[(unsigned char)TitleSceneImageID::BG] = LoadGraph("res/Image/bg.png");
	map[(unsigned char)TitleSceneImageID::Text] = LoadGraph("res/Image/title_text.png");
}

void Image::PlaySceneImageLoad()
{
	map[(unsigned char)PlaySceneImageID::Enemy] = LoadGraph("res/Image/enemy_bullet_16.png");
	map[(unsigned char)PlaySceneImageID::BG] = LoadGraph("res/Image/bg.png");
	map[(unsigned char)PlaySceneImageID::Player] = LoadGraph("res/Image/player.png");
	map[(unsigned char)PlaySceneImageID::PlayerNormalBullet] = LoadGraph("res/Image/player_normal_bullet.png");
	map[(unsigned char)PlaySceneImageID::PlayerScatterBullet] = LoadGraph("res/Image/player_scatter_bullet.png");
	map[(unsigned char)PlaySceneImageID::Boss] = LoadGraph("res/Image/boss.png");
}

void Image::ClearSceneImageLoad()
{
	map[(unsigned char)ClearSceneImageID::BG] = LoadGraph("res/Image/gameclear.png");
}

void Image::GameOverSceneImageLoad()
{
	map[(unsigned char)GameOverSceneImageID::BG] = LoadGraph("res/Image/gameover.png");
}