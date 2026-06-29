#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "../core/object.h"
#include "../intensity/intensity.h"
#include "../core/constants.h"

class Triangle : public Object {
private:
    Vector3D vertex1;
    Vector3D vertex2;
    Vector3D vertex3;
    Vector3D edge1;
    Vector3D edge2;
    Vector3D normal;
    Material material;

public:
    Triangle(const Vector3D& v1, const Vector3D& v2, const Vector3D& v3, const Material& material);

    IntersectionInfo intersect(const Ray& ray) const override;
};

#endif // TRIANGLE_H