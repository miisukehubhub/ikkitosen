#ifndef ENEMYBULLETUPDATERKERNEL_CUH_
#define ENEMYBULLETUPDATERKERNEL_CUH_

#include <cuda_runtime.h>

#include "../EnemyBullet.h"

namespace EnemyBulletUpdaterKernel
{
	// 敵弾更新カーネル
	__global__ void Process(EnemyBullet* ebPtr, int length);
}

#endif