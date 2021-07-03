#ifndef ENEMYUPDATERKERNEL_CUH_
#define ENEMYUPDATERKERNEL_CUH_

#include <cuda_runtime.h>

#include "../Enemy.h"

namespace EnemyUpdaterKernel
{
	// 敵の更新カーネル
	__global__ void Process(Enemy* ePtr, int length);

	__device__ void SoftEnemyUpdate(Enemy* ePtr);

	__device__ void HardEnemyUpdate(Enemy* ePtr);

	__device__ void MetalEnemyUpdate(Enemy* ePtr);
}

#endif