#include "SE.h"

#include <DxLib.h>

std::unordered_map<SEID, int> SE::map = std::unordered_map<SEID, int>();

void SE::Load()
{
	map[SEID::Start] = LoadSoundMem("res/SE/start.mp3");
	ChangeVolumeSoundMem(200, map[SEID::Start]);
	map[SEID::NormalBulletFire] = LoadSoundMem("res/SE/normal_bullet_fire.mp3");
	ChangeVolumeSoundMem(200, map[SEID::NormalBulletFire]);
	map[SEID::ScatterBulletFire] = LoadSoundMem("res/SE/scatter_bullet_fire.mp3");
	ChangeVolumeSoundMem(200, map[SEID::ScatterBulletFire]);
	map[SEID::EnemyDead] = LoadSoundMem("res/SE/enemy_dead.mp3");
	ChangeVolumeSoundMem(200, map[SEID::EnemyDead]);
	map[SEID::BossDead] = LoadSoundMem("res/SE/boss_dead.mp3");
	ChangeVolumeSoundMem(200, map[SEID::BossDead]);
	map[SEID::Clear] = LoadSoundMem("res/SE/clear.mp3");
	ChangeVolumeSoundMem(200, map[SEID::Clear]);
	map[SEID::GameOver] = LoadSoundMem("res/SE/gameover.mp3");
	ChangeVolumeSoundMem(200, map[SEID::GameOver]);
	map[SEID::Damaged] = LoadSoundMem("res/SE/damaged.mp3");
	ChangeVolumeSoundMem(200, map[SEID::Damaged]);
}

int SE::At(SEID SEId)
{
	return map[SEId];
}