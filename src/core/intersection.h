#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "../math/vector3D.h"

enum class IntersectionHitType {
    None = -1,
    Behind = 0,
    Hit = 1
};

typedef struct{
    Vector3D point;
    Vector3D normal;
    float distance;
    IntersectionHitType hit; 
} IntersectionInfo;

#endif 