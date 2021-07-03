#ifndef WEAPON_H_
#define WEAPON_H_

// プレイヤーの武器の基底クラス
class PlayerWeapon
{
public:

	PlayerWeapon() = default; // コンストラクタ

	virtual ~PlayerWeapon() = default; // デストラクタ

	virtual void Update() = 0; //	更新処理
};

#endif