#include "renderer.h"
#include "../utils/logging.h"

void display();
void keyboardInputDown(unsigned char key, int x, int y);
void keyboardInputUp(unsigned char key, int x, int y);
void handleKeyboardInput(int value);

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

    glutKeyboardFunc(keyboardInputDown);
    glutKeyboardUpFunc(keyboardInputUp);
    glutIgnoreKeyRepeat(1);

    glutPassiveMotionFunc(passiveMouseMovement);
    glutMotionFunc(passiveMouseMovement);

    glutTimerFunc(KEYBOARD_CALLBACK_INTERVAL, handleKeyboardInput, 0);

    glutSetCursor(GLUT_CURSOR_NONE);
    glutWarpPointer(this->centerX, this->centerY);
    
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

void keyboardInputDown(unsigned char key, int x, int y){
    // log(std::string("Key pressed: ") + std::to_string(key));

    heldKeys[key] = true;

    if(key == 27){ // ESC key
        exit(0);
    }
}

void keyboardInputUp(unsigned char key, int x, int y){
    // log(std::string("Key released: ") + std::to_string(key));

    heldKeys[key] = false;
}

void handleKeyboardInput(int value){
    // log("Handling keyboard input...");

    if(heldKeys['w']){
        rendererInstance->camera.moveForward(10.0f);
    }
    if(heldKeys['s']){
        rendererInstance->camera.moveForward(-10.0f);
    }
    if(heldKeys['a']){
        rendererInstance->camera.moveRight(-10.0f);
    }
    if(heldKeys['d']){
        rendererInstance->camera.moveRight(10.0f);
    }

    glutPostRedisplay(); 
    glutTimerFunc(KEYBOARD_CALLBACK_INTERVAL, handleKeyboardInput, 0);
}

void passiveMouseMovement(int x, int y){
    if(x == rendererInstance->centerX && y == rendererInstance->centerY){
        return;
    }

    int deltaX = x - rendererInstance->centerX;
    int deltaY = rendererInstance->centerY - y;

    if(deltaX != 0 || deltaY != 0){
        float sensitivity = MOUSE_SENSITIVITY; 

        rendererInstance->camera.lookRight(deltaX * sensitivity);
        rendererInstance->camera.lookUp(deltaY * sensitivity);

        glutPostRedisplay();
        glutWarpPointer(rendererInstance->centerX, rendererInstance->centerY); 
    }
}