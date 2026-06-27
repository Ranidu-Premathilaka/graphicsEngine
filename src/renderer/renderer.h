#ifndef RENDERER_H
#define RENDERER_H

#define GL_SILENCE_DEPRECATION
#define STARTING_POINT_X -1
#define STARTING_POINT_Y -1

#include <GLUT/glut.h>

#include "../camera/camera.h"
#include "../scene/scene.h"

class Renderer {
    public:
        const Scene& scene;
        Camera& camera;
        float* frameBuffer;
        int width, height;


        Renderer(const Scene& scene, Camera& camera, int width, int height);
        ~Renderer();

        void run();
        void initGLUT(int argc, char** argv, const char* title);
        void updateFrameBuffer();

};

#endif