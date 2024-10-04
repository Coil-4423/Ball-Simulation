#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <GL/gl.h>
#include <GL/glu.h> // Include GLU for gluNewQuadric and gluSphere
#include <cmath>

const float M_PI = 3.14159265358979323846f;

class Sphere
{
private:
    float radius; // Member variable to store half wall size

public:
    // Constructor to initialize radius
    Sphere(float size = 10.0f) : radius(size) {}

    // Method to get the half wall size
       float getRadius() const
       {
           return radius;
       }

    // Function to draw sphere as dotted grids with large dots at the corners
    void draw()
    {
        const float dotSpacing = 6.0f; // Distance between dots
        const float smallDotRadius = 0.05f; // Radius for small dots
        const float largeDotRadius = 0.1f;  // Radius for large dots

        // Set color for sphere (dots)
        glColor3f(1.0f, 1.0f, 1.0f); // White color

        // Draw small dots on sphere
        drawSphereDots(dotSpacing, smallDotRadius);
        // Draw large dots at the corners of the sphere
        drawPoleDots(largeDotRadius);
    }

private:
    // Function to draw small dots on the sphere
    void drawSphereDots(float dotSpacing, float smallDotRadius)
{
    for (float theta = 0.0f; theta <= 180.0f; theta += dotSpacing)
    {
        for (float phi = 0.0f; phi <= 360.0f; phi += dotSpacing)
        {
            float x = radius * sin(theta * M_PI / 180.0f) * cos(phi * M_PI / 180.0f);
            float y = radius * cos(theta * M_PI / 180.0f);
            float z = radius * sin(theta * M_PI / 180.0f) * sin(phi * M_PI / 180.0f);
            drawDot(x, y, z, smallDotRadius);
        }
    }
}

    // Function to draw a dot at a specific position
    void drawDot(float x, float y, float z, float radius)
    {
        glPushMatrix();
        glTranslatef(x, y, z);
        drawSphere(radius, 10, 10);
        glPopMatrix();
    }

    // Function to draw large dots at the pole of the sphere
    void drawPoleDots(float largeDotRadius)
    {
        // Define corner positions
        float pole[2][3] = {
            {0, radius, 0}, // Top-front-left
            {0, -radius, 0},  // Top-front-right
        };

        for (int i = 0; i < 2; ++i)
        {
            drawLargeDot(pole[i][0], pole[i][1], pole[i][2], largeDotRadius);
        }
    }

    // Helper function to draw a large dot at a specific position
    void drawLargeDot(float x, float y, float z, float radius)
    {
        glPushMatrix();
        glTranslatef(x, y, z);
        drawSphere(radius, 20, 20);
        glPopMatrix();
    }

    // Function to draw a 3D sphere
    void drawSphere(float radius, int slices, int stacks)
    {
        GLUquadric* quadric = gluNewQuadric();
        gluSphere(quadric, radius, slices, stacks);
        gluDeleteQuadric(quadric);
    }
};

#endif // sphere_HPP