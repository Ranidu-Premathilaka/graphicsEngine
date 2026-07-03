#ifndef SPHERE_H
#define SPHERE_H

#include "../../core/object.h"
#include "../../intensity/intensity.h"

class Sphere : public Object {
private:
    Vector3D center;
    float radius;
    Material material;

public:
    Sphere(const Vector3D& center,float radius, const Material& material); 

    IntersectionInfo intersect(const Ray& ray) const override;
};

#endif // SPHERE_H