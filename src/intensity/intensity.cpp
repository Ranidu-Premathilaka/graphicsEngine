#include "intensity.h"

Intensity::Intensity(float r, float g, float b) : r(r), g(g), b(b) {}

Intensity Intensity::operator+(const Intensity& other) const {
    return Intensity(r + other.r, g + other.g, b + other.b);
}

Intensity Intensity::operator*(float scalar) const {
    return Intensity(r * scalar, g * scalar, b * scalar);
}

Intensity Intensity::operator*(Intensity other) const {
    return Intensity(r * other.r, g * other.g, b * other.b);
}

Intensity Intensity::operator-(float scalar) const {
    return Intensity(r - scalar, g - scalar, b - scalar);
}