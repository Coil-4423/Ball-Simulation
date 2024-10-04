#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <GL/gl.h>
#include <GL/glu.h>

class LightSystem
{
public:
    LightSystem() {}

    // Set up lighting
    void setupLight()
    {
        // Define the ambient light (global lighting, dim)
        GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
        glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);

        // Define the diffuse light (direct light, brighter)
        GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);

        // Define the light position (above the scene, casting light downward)
        GLfloat lightPosition[] = { 0.0f, 20.0f, 0.0f, 1.0f };
        glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

        // Enable color tracking to apply material properties
        glEnable(GL_COLOR_MATERIAL);
        glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

        // Set material properties
        GLfloat materialSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
        glMateriali(GL_FRONT, GL_SHININESS, 50);  // Shininess factor

        // Enable shading for smooth transitions between colors
        glShadeModel(GL_SMOOTH);
    }
};

#endif // LIGHT_HPP
