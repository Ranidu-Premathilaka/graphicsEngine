#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "../math/vector3D.h"
#include "../material/material.h"

enum class IntersectionHitType {
    None = -1,
    Behind = 0,
    Hit = 1
};

typedef struct{
    Vector3D point;
    Vector3D normal;
    float distance;
    const Material *material;
    IntersectionHitType hit; 
} IntersectionInfo;

#endif 