#ifndef ENEMYCOLLISIONDETECTIONKERNEL_CUH_
#define ENEMYCOLLISIONDETECTIONKERNEL_CUH_

#include <cuda_runtime.h>

#include "../Enemy.h"

class PlayerNormalBullet;
class PlayerScatterBullet;

namespace EnemyCollisionDetectionKernel
{
	// 敵の当たり判定カーネル
	__global__ void Process(Enemy* ePtr, int eLength, PlayerNormalBullet* pnbPtr, int pnbLength, PlayerScatterBullet* psbPtr, int psbLength);
}

#endif