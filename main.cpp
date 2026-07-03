#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include "src/scene/scene.h"
#include "src/renderer/renderer.h"
#include "src/camera/camera.h"
#include "src/objects/primitive/sphere.h"
#include "src/objects/primitive/triangle.h"
#include "src/lightSource/lightSource.h"

void testPerformance() {
    ViewPort viewport = {800, 600};
    Camera camera(Vector3D(0, 0, 0), Vector3D(1, 0, 0), viewport, 30);
    Scene scene(Intensity(0.1f, 0.1f, 0.1f), Intensity(0.0f, 0.0f, 0.0f));

    Material metal(Intensity(0.1f, 0.1f, 0.1f), Intensity(0.8f, 0.2f, 0.2f), Intensity(1.0f, 1.0f, 1.0f), 32.0f);
    Sphere sphere(Vector3D(5000, 0, 0), 800.0f, metal);
    scene.addObject(&sphere);
    
    LightSource lightSource(Vector3D(0, 1000, 0), Intensity(1.0f, 1.0f, 1.0f));
    scene.addLightSource(&lightSource);

    Renderer renderer(scene, camera, viewport.width, viewport.height);

    renderer.updateFrameBuffer();
}

int main(int argc, char** argv) {

    if(argc > 1){
        testPerformance();
        return 0;
    }

    ViewPort viewport = {800, 600};
    Camera camera(Vector3D(0, 0, 0), Vector3D(1, 0, 0), viewport, 30);
    Scene scene(Intensity(0.5f, 0.5f, 0.5f), Intensity(0.0f, 0.0f, 0.0f));
    Material metal(
        Intensity(0.1f, 0.1f, 0.1f),  
        Intensity(0.8f, 0.2f, 0.2f),  
        Intensity(1.0f, 1.0f, 1.0f),  
        32.0f                         
    );

    Material matte(
        Intensity(0.1f, 0.1f, 0.1f),
        Intensity(0.2f, 0.6f, 0.9f),
        Intensity(1.0f, 1.0f, 1.0f),
        16.0f
    );

    Sphere bigSphere(
        Vector3D(48, 0, 0),
        12.0f,
        matte
    );

    // facing the light
    Triangle triangle(
        Vector3D(24, 3, 3),
        Vector3D(24, 3, -3),
        Vector3D(24, 0, 3), 
        metal
    );

    scene.addObject(&bigSphere);
    scene.addObject(&triangle);

    LightSource lightSource(
        Vector3D(0, 0, 0),   
        Intensity(1.0f, 1.0f, 1.0f)
    );

    scene.addLightSource(&lightSource);

    Renderer renderer(scene, camera, viewport.width, viewport.height);

    renderer.initGLUT(argc, argv, "Test");
    renderer.run();

    return 0;
}