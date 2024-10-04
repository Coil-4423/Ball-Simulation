#ifndef VECTOR3F_HPP
#define VECTOR3F_HPP

#include <cmath>

struct Vector3f {
    float x, y, z;

    // Overloading + operator
    Vector3f operator+(const Vector3f& other) const
    {
        return { x + other.x, y + other.y, z + other.z };
    }

    // Overloading - operator for vector subtraction
    Vector3f operator-(const Vector3f& other) const
    {
        return { x - other.x, y - other.y, z - other.z };
    }

    // Overloading * operator for scalar multiplication
    Vector3f operator*(float scalar) const
    {
        return { x * scalar, y * scalar, z * scalar };
    }

    // Overloading += operator
    Vector3f& operator+=(const Vector3f& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    // Overloading -= operator
    Vector3f& operator-=(const Vector3f& other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    // Dot product function (not overloaded to avoid ambiguity)
    float dot(const Vector3f& other) const
    {
        return x * other.x + y * other.y + z * other.z;
    }

    // Length (magnitude) function
    float length() const
    {
        return std::sqrt(x * x + y * y + z * z);
    }

    // Normalize function
    Vector3f normalize() const
    {
        float length = std::sqrt(x * x + y * y + z * z);
        if (length == 0.0f) return {0.0f, 0.0f, 0.0f}; // Prevent division by zero
        return { x / length, y / length, z / length };
    }

    // Cross product function
    Vector3f cross(const Vector3f& other) const
    {
        return {
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        };
    }
};

#endif // VECTOR3F_HPP
