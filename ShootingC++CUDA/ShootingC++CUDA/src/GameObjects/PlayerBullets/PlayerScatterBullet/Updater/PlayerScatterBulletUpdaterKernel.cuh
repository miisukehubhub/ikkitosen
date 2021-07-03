#ifndef PLAYERSCATTERBULLETUPDATERKERNEL_H_
#define PLAYERSCATTERBULLETUPDATERKERNEL_H_

#include <cuda_runtime.h>

#include "../PlayerScatterBullet.h"

namespace PlayerScatterBulletUpdaterKernel
{
	// プレイヤー散弾更新カーネル
	__global__ void Process(PlayerScatterBullet* psbPtr, int length);
}

#endif