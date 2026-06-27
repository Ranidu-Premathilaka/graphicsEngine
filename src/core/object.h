#ifndef OBJECT_H
#define OBJECT_H

#include "../core/intersection.h"
#include "../math/vector3D.h"
#include "../core/ray.h"
#include "../intensity/intensity.h"

class Object {
    public:
        virtual void setIntensities(const Intensity& ambient, const Intensity& diffuse, const Intensity& specular, float shininess) = 0;
        virtual IntersectionInfo intersect(const Ray& ray) const = 0;
        virtual Vector3D getNormalAt(const Vector3D& point) const = 0;
        virtual Intensity getMaterialAmbientIntensity() const = 0;
        virtual Intensity getMaterialDiffuseIntensity() const = 0;
        virtual Intensity getMaterialSpecularIntensity() const = 0;
        virtual float getMaterialShininess() const = 0;
};

#endif
