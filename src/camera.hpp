#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <SFML/Window.hpp>
#include <GL/gl.h>
#include <GL/glu.h>

class Camera
{
private:
    float angleX = 0.0f; // Rotation around the Y-axis
    float angleY = 0.0f; // Rotation around the X-axis
    float zoom = 50.0f;  // Distance from the object
    float moveSpeed = 0.1f; // Movement speed
    sf::Vector2i lastMousePos; // Last mouse position
    bool isMousePressed = false; // Indicates if the left mouse button is pressed

public:
    Camera() {
        lastMousePos = sf::Mouse::getPosition(); // Initialize last mouse position
    }

    void handleInput(const sf::Event& event)
    {
        // Handle keyboard input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) angleY += moveSpeed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) angleY -= moveSpeed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) angleX += moveSpeed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) angleX -= moveSpeed;

        // Handle mouse input
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (!isMousePressed) { // Check if mouse was just pressed
                lastMousePos = sf::Mouse::getPosition(); // Update last mouse position
                isMousePressed = true; // Set the mouse pressed flag
            }
            else {
                // Get current mouse position
                sf::Vector2i currentMousePos = sf::Mouse::getPosition();
                // Calculate the difference in mouse position
                float deltaX = static_cast<float>(currentMousePos.x - lastMousePos.x);
                float deltaY = static_cast<float>(currentMousePos.y - lastMousePos.y);
                // Update angles based on mouse movement
                angleX -= deltaX * 0.01f; // Sensitivity can be adjusted
                angleY += deltaY * 0.01f; // Sensitivity can be adjusted
                // Update last mouse position
                lastMousePos = currentMousePos;
            }
        }
        else {
            isMousePressed = false; // Reset mouse pressed flag when not pressed
        }

        // Handle mouse scroll for zooming
        if (event.type == sf::Event::MouseWheelScrolled) {
            zoom -= event.mouseWheelScroll.delta * 1.0f; // Adjust zoom sensitivity as needed
            if (zoom < 1.0f) zoom = 1.0f; // Prevent zooming too close
            if (zoom > 100.0f) zoom = 100.0f; // Prevent zooming too far
        }
    }

    void applyCamera()
    {
        gluLookAt(zoom * sin(angleX) * cos(angleY), zoom * sin(angleY), zoom * cos(angleX) * cos(angleY),
            0, 0, 0,
            0, 1, 0);
    }
};

#endif