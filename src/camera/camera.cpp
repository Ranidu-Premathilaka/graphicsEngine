#include "camera.h"
#include "../core/constants.h"
#include <cmath>

// PRIVATE METHODS

void Camera::cameraDirectionChanged() {
    this->viewPortCenter = position + normalizedDirection * focalLength;

    this->rightVector = normalizedDirection.cross(WORLD_UP);
    this->rightVector.normalize();

    this->upVector = rightVector.cross(normalizedDirection);
    this->upVector.normalize();
    this->cameraDirectionChangedFlag = true;
}

// PUBLIC METHODS
Camera::Camera(const Vector3D& position, const Vector3D& normalizedDirection, const ViewPort& viewport, int FOV) {
    this->position = position;

    this->normalizedDirection = normalizedDirection;
    this->normalizedDirection.normalize();

    this->focalLength = viewport.width / (2.0f * tan(FOV * M_PI / 360.0f));

    this->rightVector = normalizedDirection.cross(WORLD_UP);
    this->rightVector.normalize();

    this->upVector = rightVector.cross(normalizedDirection);
    this->upVector.normalize();

    this->viewPortCenter = position + normalizedDirection * focalLength;

    // This is so that the first image is rendered at first
    this->cameraDirectionChangedFlag = true;
}


// Make sure this pixel is within the viewport bounds as checks aren't done for optimization purposes
// This pixels should be relative to the venter of the viewport
Ray Camera::getNextRay(int pixelX, int pixelY) const {
    Ray ray;
    ray.position = position;

    Vector3D pixelPosition = viewPortCenter + rightVector * pixelX + upVector * pixelY;
    ray.normalizedDirection = pixelPosition - position;
    ray.normalizedDirection.normalize();

    return ray; 
}

bool Camera::hasCameraDirectionChanged() const {
    return this->cameraDirectionChangedFlag;
}

void Camera::resetCameraDirectionChangedFlag() {
    this->cameraDirectionChangedFlag = false;
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

