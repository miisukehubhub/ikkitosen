#ifndef PLAYERNORMALBULLETUPDATERKERNEL_CUH_
#define PLAYERNORMALBULLETUPDATERKERNEL_CUH_

#include <cuda_runtime.h>

#include "../PlayerNormalBullet.h"

namespace PlayerNormalBulletUpdaterKernel
{
	// プレイヤー通常弾の更新カーネル
	__global__ void Process(PlayerNormalBullet* pnbPtr, int length);
}

#endif