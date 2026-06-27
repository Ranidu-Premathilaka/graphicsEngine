#include "renderer.h"
#include "../utils/logging.h"

void display();
void keyboardInput(unsigned char key, int x, int y);


static Renderer* rendererInstance = nullptr; // Global pointer to the Renderer instance

// PRIVATE METHODS


// PUBLIC METHODS
Renderer::Renderer(const Scene& scene, Camera& camera) : scene(scene), camera(camera) {};

void Renderer::run(){
    rendererInstance = this;
    glutMainLoop();
};
void Renderer::init(int argc, char** argv, int width, int height, const char* title){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(width, height);
    glutCreateWindow(title);

    glClearColor(1.0, 1.0, 1.0, 1.0);  // Default White background
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-width/2, width/2, -height/2, height/2);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboardInput);
    // glutIdleFunc();
};


// Internal GLUT callback functions
void drawPoint(Pixel pixel){

    glColor3f(pixel.r, pixel.g, pixel.b);
    glBegin(GL_POINTS);
    glVertex2f(pixel.x, pixel.y);
    glEnd();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    
    log("Rendering started...");

    while(rendererInstance->camera.isScreenRendering()){
        Ray ray = rendererInstance->camera.getNextRay();
        Intensity intensity = rendererInstance->scene.calculateIntensity(ray);

        Pixel pixel;

        pixel.x = rendererInstance->camera.getPixelX();
        pixel.y = rendererInstance->camera.getPixelY();

        pixel.r = intensity.r;
        pixel.g = intensity.g;
        pixel.b = intensity.b;        

        drawPoint(pixel);
    }

    glutSwapBuffers();

    rendererInstance->camera.resetScreen();
}

void keyboardInput(unsigned char key, int x, int y){
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