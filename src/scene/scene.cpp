#include "scene.h"
#include "../intensity/intensity.h"
#include "../utils/logging.h"
#include "../core/constants.h"

// PRIVATE METHODS
IntersectionInfo Scene::traceRay(const Ray& ray) const {
    IntersectionInfo closestIntersection;
    closestIntersection.distance = std::numeric_limits<float>::max();
    closestIntersection.hit = IntersectionHitType::None;

    for (const Object* object : objects) {
        IntersectionInfo intersection = object->intersect(ray);
        if (intersection.hit == IntersectionHitType::Hit && intersection.distance < closestIntersection.distance) {
            closestIntersection = intersection;
        }
    }

    return closestIntersection;
}

bool Scene::isShadowed(const Vector3D& point, const Vector3D& lightDirection, double lightDistance) const {

    Ray shadowRay{point + lightDirection * EPSILON, lightDirection};

    for (const Object* object : objects) {
        IntersectionInfo intersection = object->intersect(shadowRay);
        if (intersection.hit == IntersectionHitType::Hit && intersection.distance < lightDistance) {
            return true; 
        }
    }

    return false;
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
    IntersectionInfo closestIntersection = this->traceRay(ray);

    if (closestIntersection.hit == IntersectionHitType::Hit) {
        // Might not be needed as material specific ambient intensity seems silly
        Intensity totalIntensity = closestIntersection.material->getLightIndependentIntensity(this->ambientIntensity);

        for (const LightSource* lightSource : lightSources) {
            Vector3D lightDirection = lightSource->lightDirectionFrom(closestIntersection.point);
            double dotProduct = lightDirection.dot(closestIntersection.normal);

            if(dotProduct < 0) {
                // log("Light source is behind the surface, skipping.");
                continue; 
            }

            if(this->isShadowed(closestIntersection.point, lightDirection, lightSource->distanceFrom(closestIntersection.point))) {
                // log("Point is shadowed, skipping light source.");
                continue; 
            }

            totalIntensity = totalIntensity + closestIntersection.material->getLightDependentIntensity(
                lightSource->getIntensity(),
                -ray.normalizedDirection,
                closestIntersection.normal,
                lightDirection
            );
        }

        return totalIntensity;
    } else {
        return this->backgroundIntensity;
    }
}



