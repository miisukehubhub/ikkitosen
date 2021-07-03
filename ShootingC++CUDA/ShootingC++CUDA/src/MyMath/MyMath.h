#ifndef MYMATH_H_
#define MYMATH_H_

#include <cuda_runtime.h>

#include "../Vector2/Vector2.h"

namespace MyMath
{
    // ‰~“¯Žm‚Ì“–‚½‚è”»’è
    __device__ __host__ static bool CircleCircleIntersection(
        Vector2 pos1, float radius1,
        Vector2 pos2, float radius2)
    {
        return (pos1 - pos2).lengthSquared()
            < ((radius1 + radius2) * (radius1 + radius2));
    }
    
}

#endif
