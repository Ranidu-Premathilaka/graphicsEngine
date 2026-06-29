#include "lightSource.h"
#include <cmath>

LightSource::LightSource(const Vector3D& position, const Intensity& intensity) : position(position), intensity(intensity) {}

Vector3D LightSource::lightDirectionFrom(const Vector3D& point) const {
    Vector3D direction = (position - point);
    direction.normalize();
    return direction;
}

double LightSource::distanceFrom(const Vector3D& point) const {
    Vector3D direction = (position - point);
    return std::sqrt(direction.dot(direction));
}

Intensity LightSource::getIntensity() const {
    return intensity;
}

