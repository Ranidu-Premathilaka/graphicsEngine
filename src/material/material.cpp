#include "material.h"
#include <cmath>

//PRIVATE METHODS

// PUBLIC METHODS

Material::Material(const Intensity& ambient, const Intensity& diffuse, const Intensity& specular,float shininess, const Intensity& emissive)
    : ambientIntensity(ambient), diffuseIntensity(diffuse), specularIntensity(specular), shininess(shininess), emissiveIntensity(emissive) {}


Intensity Material::getActualLightIntensity(Intensity lightIntensity, Vector3D viewDirection, Vector3D intersectionNormal, Vector3D lightDirection) const {

    Intensity tempIntensity(0, 0, 0);

    // Diffusion reflection
    double dotProduct = lightDirection.dot(intersectionNormal);

    // Light is behind the surface
    if(dotProduct < 0) {
        return tempIntensity; 
    }

    tempIntensity = this->diffuseIntensity * dotProduct;

    // Specular reflection
    Vector3D reflectionDirection = (intersectionNormal * 2 * dotProduct) - lightDirection;
    reflectionDirection.normalize();

    double specularReflection = std::pow(reflectionDirection.dot(viewDirection), this->shininess);
    tempIntensity = tempIntensity + (this->specularIntensity * specularReflection);

    return tempIntensity * lightIntensity + this->emissiveIntensity;
}

Intensity Material::getAmbientIntensity(Intensity ambientSceneIntensity) const {
    return this->ambientIntensity * ambientSceneIntensity;
}