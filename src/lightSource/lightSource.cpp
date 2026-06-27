#include "lightSource.h"

LightSource::LightSource(const Vector3D& position, const Intensity& intensity) : position(position), intensity(intensity) {}

Vector3D LightSource::lightDirectionFrom(const Vector3D& point) const {
    Vector3D direction = (position - point);
    direction.normalize();
    return direction;
}

Intensity LightSource::getIntensity() const {
    return intensity;
}

