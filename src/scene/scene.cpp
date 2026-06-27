#include "scene.h"
#include "../intensity/intensity.h"

// PRIVATE METHODS
ObjectIntersectionInfo Scene::traceRay(const Ray& ray) const {
    ObjectIntersectionInfo closestIntersection;
    closestIntersection.intersection.distance = std::numeric_limits<float>::max();
    closestIntersection.intersection.hit = IntersectionHitType::None;
    closestIntersection.object = nullptr;

    for (const Object* object : objects) {
        IntersectionInfo intersection = object->intersect(ray);
        if (intersection.hit == IntersectionHitType::Hit && intersection.distance < closestIntersection.intersection.distance) {
            closestIntersection.intersection = intersection;
            closestIntersection.object = object;
        }
    }

    return closestIntersection;
}


// PUBLIC METHODS

Scene::Scene(Intensity ambientIntensity, Intensity backgroundIntensity) 
    : ambientIntensity(ambientIntensity), backgroundIntensity(backgroundIntensity) {}

int Scene::addObject(Object* object) {
    objects.push_back(object);
    return objects.size() - 1; 
}

int Scene::addLightSource(LightSource* lightSource) {
    lightSources.push_back(lightSource);
    return lightSources.size() - 1;
}

Intensity Scene::calculateIntensity(const Ray& ray) const {
    ObjectIntersectionInfo closestIntersection = this->traceRay(ray);
    const IntersectionInfo& intersection = closestIntersection.intersection;
    const Object* intersectedObject = closestIntersection.object;

    if (intersectedObject != nullptr) {
        Intensity totalIntensity = ambientIntensity * intersectedObject->getMaterialAmbientIntensity();

        //Phong Illumination Model
        for (const LightSource* lightSource : lightSources) {

            // Diffusion reflection
            Vector3D intersectionNormal = intersectedObject->getNormalAt(intersection.point);
            Vector3D lightDirection = lightSource->lightDirectionFrom(intersection.point);
            double dotProduct = lightDirection.dot(intersectionNormal);

            // Light is behind the surface
            if(dotProduct < 0) {
                continue;
            }

            Intensity tempIntensity = intersectedObject->getMaterialDiffuseIntensity() * dotProduct;

            // Specular reflection
            Vector3D viewDirection = (ray.position - intersection.point);
            viewDirection.normalize();

            Vector3D reflectionDirection = (intersectionNormal * 2 * dotProduct) - lightDirection;
            reflectionDirection.normalize();

            double specularReflection = std::pow(reflectionDirection.dot(viewDirection), intersectedObject->getMaterialShininess());
            tempIntensity = tempIntensity + (intersectedObject->getMaterialSpecularIntensity() * specularReflection);

            totalIntensity = totalIntensity + (tempIntensity * lightSource->getIntensity());
        }

        return totalIntensity;
    } else {
        return this->backgroundIntensity;
    }
}



