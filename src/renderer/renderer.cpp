#include "renderer.h"
#include "../utils/logging.h"
#include "rendererThread/renderThreadPool.h"

void display();
void handleKeyboardInput(unsigned char key, int x, int y);

void passiveMouseMovement(int x, int y);

bool heldKeys[256] = {false}; 


static Renderer* rendererInstance = nullptr; // Global pointer to the Renderer instance

// PRIVATE METHODS


// PUBLIC METHODS
Renderer::Renderer(const Scene& scene, Camera& camera, int width, int height) : scene(scene), camera(camera) {
    frameBuffer = new float[width * height * 6]; 
    if(frameBuffer == nullptr){
        log("Failed to allocate memory for frame buffer.");
        exit(EXIT_FAILURE);
    }

    this->width = width;
    this->height = height;
    this->centerX = width / 2;
    this->centerY = height / 2;

    rendererInstance = this;
    this->threadPool = new RenderThreadPool(this);
};

Renderer::~Renderer() {
    delete[] frameBuffer;
    delete threadPool;
}

void Renderer::run(){
    glutPostRedisplay(); 
    glutMainLoop();
};
void Renderer::initGLUT(int argc, char** argv, const char* title){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(this->width, this->height);
    glutCreateWindow(title);
    glutDisplayFunc(display);

    glutKeyboardFunc(handleKeyboardInput);

    glutPassiveMotionFunc(passiveMouseMovement);
    glutMotionFunc(passiveMouseMovement);


    glutSetCursor(GLUT_CURSOR_NONE);
    glutWarpPointer(this->centerX, this->centerY);
    
};

void Renderer::workerTask(int workerId, int numOfWorkers){
    for(int y = workerId; y < this->height; y += numOfWorkers){
        for(int x = 0; x < this->width; ++x){
            Ray ray = camera.getNextRay(x - this->width / 2, y - this->height / 2);
            Intensity intensity = scene.calculateIntensity(ray);

            frameBuffer[(y * this->width + x) * 3 + 0] = intensity.r;
            frameBuffer[(y * this->width + x) * 3 + 1] = intensity.g;
            frameBuffer[(y * this->width + x) * 3 + 2] = intensity.b;        
        }
    }
}

void Renderer::updateFrameBuffer(){
    this->threadPool->startWorkers();
}


void display(){

    if(!rendererInstance->camera.hasCameraDirectionChanged()){
        return;
    }
    rendererInstance->updateFrameBuffer();

    glClear(GL_COLOR_BUFFER_BIT);
    glRasterPos2i(STARTING_POINT_X, STARTING_POINT_Y); 

    glDrawPixels(
        rendererInstance->width,
        rendererInstance->height,
        GL_RGB,
        GL_FLOAT,
        rendererInstance->frameBuffer
    );
    glutSwapBuffers();

}


void handleKeyboardInput(unsigned char key, int x, int y) {
    switch(key) {
        case 27: // ESC key
            exit(0);
        case 'w':
            rendererInstance->camera.moveForward(1.0f);
            break;
        case 's':
            rendererInstance->camera.moveForward(-1.0f);
            break;
        case 'a':
            rendererInstance->camera.moveRight(-1.0f);
            break;
        case 'd':
            rendererInstance->camera.moveRight(1.0f);
            break;
        default:
            break;
    }

    glutPostRedisplay();
}

void passiveMouseMovement(int x, int y){
    if(x == rendererInstance->centerX && y == rendererInstance->centerY){
        return;
    }

    int deltaX = x - rendererInstance->centerX;
    int deltaY = rendererInstance->centerY - y;

    if(deltaX != 0 || deltaY != 0){

        rendererInstance->camera.lookRight(deltaX * MOUSE_SENSITIVITY);
        rendererInstance->camera.lookUp(deltaY * MOUSE_SENSITIVITY);

        glutPostRedisplay();
        glutWarpPointer(rendererInstance->centerX, rendererInstance->centerY); 
    }
}