#include "camera.h"
#include "../core/constants.h"
#include <cmath>

// PRIVATE METHODS

void Camera::updateToNextPixelCoordinates(){
    if(this->currentPixelX == quarterViewport.width){
        // Move to the next row
        this->currentPixelX = -quarterViewport.width;
        this->currentPixelY++;
    }else{
        this->currentPixelX++;
    }

    if(this->currentPixelY > quarterViewport.height){
        this->haveMoreRays = false;
    }
}

void Camera::cameraDirectionChanged() {
    this->viewPortCenter = position + normalizedDirection * focalLength;

    this->rightVector = normalizedDirection.cross(WORLD_UP);
    this->rightVector.normalize();

    this->upVector = rightVector.cross(normalizedDirection);
    this->upVector.normalize();
}

// PUBLIC METHODS
Camera::Camera(const Vector3D& position, const Vector3D& normalizedDirection, const ViewPort& viewport, int FOV) {
    this->position = position;

    this->normalizedDirection = normalizedDirection;
    this->normalizedDirection.normalize();

    this->quarterViewport = {viewport.width/2, viewport.height/2};
    this->focalLength = viewport.width / (2.0f * tan(FOV * M_PI / 360.0f));

    this->rightVector = normalizedDirection.cross(WORLD_UP);
    this->rightVector.normalize();

    this->upVector = rightVector.cross(normalizedDirection);
    this->upVector.normalize();

    this->viewPortCenter = position + normalizedDirection * focalLength;

    resetScreen();
}

void Camera::resetScreen(){
    this->currentPixelX = -quarterViewport.width -1;
    this->currentPixelY = -quarterViewport.height;
    this->haveMoreRays = true;
}

bool Camera::isScreenRendering(){
    return this->haveMoreRays;
}

Ray Camera::getNextRay(){
    Ray ray;
    ray.position = position;

    updateToNextPixelCoordinates();

    Vector3D pixelPosition = viewPortCenter + rightVector * currentPixelX + upVector * currentPixelY;
    ray.normalizedDirection = pixelPosition - position;
    ray.normalizedDirection.normalize();

    return ray; 
}

float Camera::getPixelX() const {
    return (float)currentPixelX;
}

float Camera::getPixelY() const {
    return (float)currentPixelY;
}

// Movement methods
void Camera::moveForward(float distance) {
    this->position = position + normalizedDirection * distance;
    this->cameraDirectionChanged();
}

void Camera::moveBackward(float distance) {
    this->position = position - normalizedDirection * distance;
    this->cameraDirectionChanged();
}

void Camera::moveLeft(float distance) {
    this->position = position - rightVector * distance;
    this->cameraDirectionChanged();
}

void Camera::moveRight(float distance) {
    this->position = position + rightVector * distance;
    this->cameraDirectionChanged();
}

// Look methods
void Camera::lookUp(float angle) {
    // Rotate the normalizedDirection around the rightVector
    float radians = angle * M_PI / 180.0f;
    Vector3D newDirection = normalizedDirection * cos(radians) + upVector * sin(radians);
    newDirection.normalize();

    if(newDirection.dot(WORLD_UP) > 0.98f){
        // Prevent looking too far up (around 10 degrees)
        return;
    }

    this->normalizedDirection = newDirection;
    this->cameraDirectionChanged();
}

void Camera::lookDown(float angle) {
    // Rotate the normalizedDirection around the rightVector
    float radians = -angle * M_PI / 180.0f;
    Vector3D newDirection = normalizedDirection * cos(radians) + upVector * sin(radians);
    newDirection.normalize();

    if(newDirection.dot(WORLD_UP) < -0.98f){
        // Prevent looking too far down (around 10 degrees)
        return;
    }

    this->normalizedDirection = newDirection;
    this->cameraDirectionChanged();
}

void Camera::lookLeft(float angle) {
    // Rotate the normalizedDirection around the upVector
    float radians = angle * M_PI / 180.0f;
    Vector3D newDirection = normalizedDirection * cos(radians) - rightVector * sin(radians);
    newDirection.normalize();
    this->normalizedDirection = newDirection;
    this->cameraDirectionChanged();
}

void Camera::lookRight(float angle) {
    // Rotate the normalizedDirection around the upVector
    float radians = -angle * M_PI / 180.0f;
    Vector3D newDirection = normalizedDirection * cos(radians) - rightVector * sin(radians);
    newDirection.normalize();
    this->normalizedDirection = newDirection;
    this->cameraDirectionChanged();
}

