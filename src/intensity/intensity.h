#ifndef INTENSITY_H
#define INTENSITY_H

class Intensity {
    public:
        float r, g, b;
        Intensity(float r, float g, float b); 
        Intensity operator+(const Intensity& other) const;
        Intensity operator*(float scalar) const;
        Intensity operator*(Intensity other) const;
        Intensity operator-(float scalar) const;
};

#endif