#ifndef SCENE_H
#define SCENE_H

#include "../core/object.h"
#include "../lightSource/lightSource.h"
#include <vector>

typedef struct {
    IntersectionInfo intersection;
    const Object* object;
} ObjectIntersectionInfo;

class Scene{
    private:
        std::vector<Object*> objects;
        std::vector<LightSource*> lightSources;
        Intensity ambientIntensity, backgroundIntensity;
        ObjectIntersectionInfo traceRay(const Ray& ray) const;

    public:
        Scene(Intensity ambientIntensity = Intensity(0.1f, 0.1f, 0.1f), Intensity backgroundIntensity = Intensity(0.0f, 0.0f, 0.0f));
        int addObject(Object* object);
        int addLightSource(LightSource* lightSource);
        Intensity calculateIntensity(const Ray& ray) const;
};




#endif 