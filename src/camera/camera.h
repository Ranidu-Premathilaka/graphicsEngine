#ifndef CAMERA_H
#define CAMERA_H

#include "../math/vector3D.h"
#include "../core/ray.h"

typedef struct {
    int width;
    int height;
} ViewPort;


class Camera {
    private:
        Vector3D position;
        Vector3D normalizedDirection;
        Vector3D upVector;
        Vector3D rightVector;
        Vector3D viewPortCenter;
        ViewPort quarterViewport;
        float focalLength;
        int currentPixelX, currentPixelY;
        bool haveMoreRays = true;
    
    void updateToNextPixelCoordinates();
    void cameraDirectionChanged();

    public:
        Camera(const Vector3D& position, const Vector3D& normalizedDirection, const ViewPort& viewport, int FOV);
        void resetScreen();
        bool isScreenRendering();
        Ray getNextRay();
        float getPixelX() const;
        float getPixelY() const;

        void moveForward(float distance);
        void moveBackward(float distance);
        void moveLeft(float distance);
        void moveRight(float distance);

        void lookUp(float angle);
        void lookDown(float angle);
        void lookLeft(float angle);
        void lookRight(float angle);
};


#endif