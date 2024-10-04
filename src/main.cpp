#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <GL/gl.h>
#include <GL/glu.h>
#include "ball.hpp"
#include "walls.hpp"
#include "camera.hpp"
#include "light.hpp" // Add the light system
#include "gravity.hpp"  // Include gravity system
#include "sphere.hpp"

// Constants
const unsigned int WINDOW_WIDTH = 2560;
const unsigned int WINDOW_HEIGHT = 1440;

int main()
{
    // Create the window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "3D Bouncing Balls with Lighting", sf::Style::Default, sf::ContextSettings(24));
    window.setFramerateLimit(60);

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glClearDepth(1.f);

    // Enable lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);  // Enable a light source

    // Set the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.f, static_cast<float>(WINDOW_WIDTH) / WINDOW_HEIGHT, 1.f, 500.f);

    // Initialize objects
    Walls walls(10.0f);
    Sphere Sphere(10.0f);
    Camera camera;
    GravitySystem gravitySystem; //Initialize gravity system
    //BallSystem ballSystem(&gravitySystem, walls.getHalfWallSize()); // Pass gravity system pointer and halfWallSize to BallSystem
    BallSystem ballSystem(&gravitySystem, Sphere.getRadius()); // Pass gravity system pointer and halfWallSize to BallSystem
    LightSystem lightSystem; // Initialize the light system


    // Main loop
    while (window.isOpen())
    {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // Pass the event to the camera for handling
            camera.handleInput(event);
        }

        // Set up the light system (before drawing)
        lightSystem.setupLight();

        // Update ball system (position, collision)
        ballSystem.update();

        // Clear the window
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Set up the modelview matrix and apply camera transformations
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        camera.applyCamera();

        // Draw objects
        //walls.draw();
        ballSystem.draw();
        Sphere.draw();

        // Display the window
        window.display();
    }

    return 0;
}
