#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include "src/scene/scene.h"
#include "src/renderer/renderer.h"
#include "src/camera/camera.h"
#include "src/objects/sphere.h"
#include "src/lightSource/lightSource.h"


int main(int argc, char** argv) {
    ViewPort viewport = {800, 600};
    Camera camera(Vector3D(0, 0, 0), Vector3D(1, 0, 0), viewport, 30);
    Scene scene(Intensity(0.1f, 0.1f, 0.1f), Intensity(0.0f, 0.0f, 0.0f));

    Sphere sphere(Vector3D(5000, 0, 0), 800.0f);
    sphere.setIntensities(Intensity(0.1f, 0.1f, 0.1f), Intensity(0.8f, 0.2f, 0.2f), Intensity(1.0f, 1.0f, 1.0f), 32.0f);
    scene.addObject(&sphere);
    
    LightSource lightSource(Vector3D(0, 1000, 0), Intensity(1.0f, 1.0f, 1.0f));
    scene.addLightSource(&lightSource);

    Renderer renderer(scene, camera);
    renderer.init(argc, argv, viewport.width, viewport.height, "Test");
    renderer.run();

    return 0;
}