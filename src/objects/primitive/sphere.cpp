#include "sphere.h"
#include <cmath>

Sphere::Sphere(const Vector3D& center, float radius, const Material& material) : center(center), radius(radius), material(material) {}

IntersectionInfo Sphere::intersect(const Ray& ray) const {
    IntersectionInfo info;

    double a = 1; // Predefined the ray struct to have normalized direction
    Vector3D k = ray.position - center;

    double b = 2 * ray.normalizedDirection.dot(k);
    double c = k.dot(k) - radius * radius;

    double discriminant = b * b - 4 * a * c;
    if (discriminant >= 0) {
        double sqrtDiscriminant = std::sqrt(discriminant);
        double t1 = (-b - sqrtDiscriminant) / (2 * a);
        double t2 = (-b + sqrtDiscriminant) / (2 * a);

        double smallestT = (t1 < t2) ? t1 : t2;
        if (smallestT > 0) {
            info.point = ray.position + ray.normalizedDirection * smallestT;
            info.normal = (info.point - center);
            info.normal.normalize();
            info.distance = smallestT;
            info.material = &material;
            info.hit = IntersectionHitType::Hit;
        } else {
            info.hit = IntersectionHitType::Behind;
        }
    }else{
        info.hit = IntersectionHitType::None;
    }
    return info;
}