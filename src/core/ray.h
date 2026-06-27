#ifndef RAY_H
#define RAY_H

#include "../math/vector3D.h"

typedef struct{
    Vector3D position;
    Vector3D normalizedDirection;
} Ray;

#endif // RAY_H