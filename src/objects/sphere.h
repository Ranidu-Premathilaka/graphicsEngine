#ifndef SPHERE_H
#define SPHERE_H

#include "../core/object.h"
#include "../intensity/intensity.h"

class Sphere : public Object {
private:
    Vector3D center;
    float radius;
    float shininess = 32.0f;
    Intensity ambientIntensity = Intensity(0.1f, 0.1f, 0.1f);
    Intensity diffuseIntensity = Intensity(0.5f, 0.5f, 0.5f);
    Intensity specularIntensity = Intensity(1.0f, 1.0f, 1.0f);

public:
    Sphere(const Vector3D& center,float radius);

    void setIntensities(const Intensity& ambient, const Intensity& diffuse, const Intensity& specular, float shininess) override;
    IntersectionInfo intersect(const Ray& ray) const override;
    Vector3D getNormalAt(const Vector3D& point) const override;
    Intensity getMaterialAmbientIntensity() const override;
    Intensity getMaterialDiffuseIntensity() const override;
    Intensity getMaterialSpecularIntensity() const override;
    float getMaterialShininess() const override;
};

#endif // SPHERE_H