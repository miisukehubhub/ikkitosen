#ifndef SE_H_
#define SE_H_

#include <unordered_map>
#include <DxLib.h>

#include "SEID.h"
#include "../Scene/SceneID.h"

class SE
{
public:

	// SE�̃��[�h
	static void Load();

	// SE�n���h�����擾
	static int At(SEID SEId);

private:

	static std::unordered_map<SEID, int> map; // �摜�̃}�b�v
};

#endif
