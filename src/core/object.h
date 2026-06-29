#ifndef OBJECT_H
#define OBJECT_H

#include "../core/intersection.h"
#include "../core/ray.h"

class Object {
    public:
        virtual IntersectionInfo intersect(const Ray& ray) const = 0;
};

#endif
