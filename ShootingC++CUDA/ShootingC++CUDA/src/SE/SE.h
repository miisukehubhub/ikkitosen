#ifndef SE_H_
#define SE_H_

#include <unordered_map>
#include <DxLib.h>

#include "SEID.h"
#include "../Scene/SceneID.h"

class SE
{
public:

	// SEのロード
	static void Load();

	// SEハンドルを取得
	static int At(SEID SEId);

private:

	static std::unordered_map<SEID, int> map; // 画像のマップ
};

#endif
