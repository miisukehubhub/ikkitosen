#ifndef ENEMYKIND_H_
#define ENEMYKIND_H_

#include <cuda_runtime.h>

// �G�̎��
enum class EnemyKind : unsigned char
{
	SoftEnemy = 0,
	HardEnemy,
	MetalEnemy,
};

#endif
