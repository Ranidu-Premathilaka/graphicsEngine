#ifndef VECTOR3D_H
#define VECTOR3D_H

class Vector3D {
    private:
        float x, y, z;


    public:
        Vector3D(float x = 0, float y = 0, float z = 0);
        Vector3D operator+(const Vector3D& other) const;
        Vector3D operator-(const Vector3D& other) const;
        Vector3D operator*(double scalar) const;
        void normalize();
        double dot(const Vector3D& other) const;
        Vector3D cross(const Vector3D& other) const;
};


#endif