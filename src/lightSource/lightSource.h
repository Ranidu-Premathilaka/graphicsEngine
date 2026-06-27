#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include "../math/vector3D.h"
#include "../intensity/intensity.h"

class LightSource {
    private:
        Vector3D position;
        Intensity intensity;

    public:
        LightSource(const Vector3D& position, const Intensity& intensity);

        Vector3D lightDirectionFrom(const Vector3D& point) const;
        Intensity getIntensity() const;
};

#endif