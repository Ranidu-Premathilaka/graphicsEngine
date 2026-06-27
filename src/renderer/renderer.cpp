#include "renderer.h"
#include "../utils/logging.h"

void display();
void keyboardInput(unsigned char key, int x, int y);


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
    rendererInstance = this;
};

Renderer::~Renderer() {
    delete[] frameBuffer; 
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
    glutKeyboardFunc(keyboardInput);
};

void Renderer::updateFrameBuffer(){
        
        for(int y = 0; y < height; ++y){
            for(int x = 0; x < width; ++x){
                Ray ray = camera.getNextRay(x - width / 2, y - height / 2);
                Intensity intensity = scene.calculateIntensity(ray);

                frameBuffer[(y * width + x) * 3 + 0] = intensity.r;
                frameBuffer[(y * width + x) * 3 + 1] = intensity.g;
                frameBuffer[(y * width + x) * 3 + 2] = intensity.b;        
            }
        }
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

void keyboardInput(unsigned char key, int x, int y){

    // log("Key pressed: " + std::to_string(key));

    switch(key){
        case 27: // ESC key
            exit(0);
            break;

        case 'w':
            rendererInstance->camera.moveForward(100.0f);
            break;

        case 's':
            rendererInstance->camera.moveBackward(100.0f);
            break;
        
        case 'a':
            rendererInstance->camera.moveLeft(100.0f);
            break;
        
        case 'd':
            rendererInstance->camera.moveRight(100.0f);
            break;

        case 'k':
            rendererInstance->camera.lookUp(5.0f);
            break;
        case 'h':
            rendererInstance->camera.lookLeft(5.0f);
            break;
        case 'l':
            rendererInstance->camera.lookRight(5.0f);
            break;
        case 'j':
            rendererInstance->camera.lookDown(5.0f);
            break;

        default:
            break;
    }

    glutPostRedisplay(); 
    
}