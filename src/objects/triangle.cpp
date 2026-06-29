#include "triangle.h"

Triangle::Triangle(const Vector3D& v1, const Vector3D& v2, const Vector3D& v3, const Material& material) : vertex1(v1), vertex2(v2), vertex3(v3), material(material) {
    this->edge1 = vertex2 - vertex1;
    this->edge2 = vertex3 - vertex1;
    this->normal = this->edge1.cross(this->edge2);
    this->normal.normalize();
}


IntersectionInfo Triangle::intersect(const Ray& ray) const {
    // Moller trumbore intersection algorithm
    IntersectionInfo info;

    Vector3D x = ray.normalizedDirection.cross(edge2);
    float det = this->edge1.dot(x);

    if(det > -EPSILON && det < EPSILON) {
        info.hit = IntersectionHitType::None; // Ray is parallel to the triangle
        return info;
    }

    float invDet = 1.0f / det;
    Vector3D s = ray.position - vertex1;

    float beta = x.dot(s) * invDet;

    if(beta < 0.0f || beta > 1.0f) {
        info.hit = IntersectionHitType::None; // Outside the triangle
        return info;
    }

    Vector3D y = s.cross(edge1);
    float gamma = y.dot(ray.normalizedDirection) * invDet;

    if(gamma < 0.0f || beta + gamma > 1.0f) {
        info.hit = IntersectionHitType::None; // Outside the triangle
        return info;
    }

    float distance = y.dot(edge2) * invDet;

    // Ray intersection
    if(distance > EPSILON) { 
        info.point = ray.position + ray.normalizedDirection * distance;
        info.normal = ray.normalizedDirection.dot(this->normal) < 0 ? this->normal : -this->normal; 
        info.distance = distance;
        info.material = &material;
        info.hit = IntersectionHitType::Hit;
    } else {
        info.hit = IntersectionHitType::Behind; // Intersection is behind the ray origin
    }

    return info;
}
