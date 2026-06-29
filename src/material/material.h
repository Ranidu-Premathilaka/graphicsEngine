#ifndef MATERIAL_H
#define MATERIAL_H

#include "../math/vector3D.h"
#include "../intensity/intensity.h"

class Material {
    private:
        Intensity ambientIntensity;
        Intensity diffuseIntensity;
        Intensity specularIntensity;
        float shininess;
        Intensity emissiveIntensity;

public:
    Material(
         const Intensity& ambient,
         const Intensity& diffuse,
         const Intensity& specular,
         float shininess,
         const Intensity& emissive = Intensity(0, 0, 0)
    );

    Intensity getActualLightIntensity(Intensity lightIntensity, Vector3D viewDirection, Vector3D intersectionNormal, Vector3D lightDirection) const;
    Intensity getAmbientIntensity(Intensity ambientSceneIntensity) const;

};

#endif