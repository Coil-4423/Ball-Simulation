#ifndef WALLS_HPP
#define WALLS_HPP

#include <GL/gl.h>
#include <GL/glu.h> // Include GLU for gluNewQuadric and gluSphere
#include <cmath>

class Walls
{
private:
    float halfWallSize; // Member variable to store half wall size

public:
    // Constructor to initialize halfWallSize
    Walls(float size = 10.0f) : halfWallSize(size) {}

    // Method to get the half wall size
       float getHalfWallSize() const
       {
           return halfWallSize;
       }

    // Function to draw walls as dotted grids with large dots at the corners
    void draw()
    {
        const float dotSpacing = 1.0f; // Distance between dots
        const float smallDotRadius = 0.05f; // Radius for small dots
        const float largeDotRadius = 0.1f;  // Radius for large dots

        // Set color for walls (dots)
        glColor3f(1.0f, 1.0f, 1.0f); // White color

        // Draw small dots on walls
        drawWallDots(dotSpacing, smallDotRadius);
        // Draw large dots at the corners of the walls
        drawCornerDots(largeDotRadius);
    }

private:
    // Function to draw small dots on the walls
    void drawWallDots(float dotSpacing, float smallDotRadius)
    {
        for (float x = -halfWallSize; x <= halfWallSize; x += dotSpacing)
        {
            for (float y = -halfWallSize; y <= halfWallSize; y += dotSpacing)
            {
                // Draw dots on all four walls
                drawDot(x, y, -halfWallSize, smallDotRadius); // Front wall
                drawDot(x, y, halfWallSize, smallDotRadius);  // Back wall
                drawDot(-halfWallSize, x, y, smallDotRadius); // Left wall
                drawDot(halfWallSize, x, y, smallDotRadius);  // Right wall
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

    // Function to draw large dots at the corners of the walls
    void drawCornerDots(float largeDotRadius)
    {
        // Define corner positions
        float corners[8][3] = {
            {-halfWallSize, halfWallSize, -halfWallSize}, // Top-front-left
            {halfWallSize, halfWallSize, -halfWallSize},  // Top-front-right
            {-halfWallSize, halfWallSize, halfWallSize},  // Top-back-left
            {halfWallSize, halfWallSize, halfWallSize},   // Top-back-right
            {-halfWallSize, -halfWallSize, -halfWallSize}, // Bottom-front-left
            {halfWallSize, -halfWallSize, -halfWallSize},  // Bottom-front-right
            {-halfWallSize, -halfWallSize, halfWallSize},  // Bottom-back-left
            {halfWallSize, -halfWallSize, halfWallSize}    // Bottom-back-right
        };

        for (int i = 0; i < 8; ++i)
        {
            drawLargeDot(corners[i][0], corners[i][1], corners[i][2], largeDotRadius);
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

#endif // WALLS_HPP