#ifndef RENDERER_H
#define RENDERER_H

#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>

#include "../camera/camera.h"
#include "../scene/scene.h"

typedef struct {
    float r, g, b;
    float x, y;
} Pixel;


class Renderer {
    public:
        const Scene& scene;
        Camera& camera;

        Renderer(const Scene& scene, Camera& camera);

        void run();
        void init(int argc, char** argv, int width, int height, const char* title);

};

#endif