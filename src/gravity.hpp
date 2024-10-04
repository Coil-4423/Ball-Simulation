#ifndef GRAVITY_HPP
#define GRAVITY_HPP

#include <SFML/Graphics.hpp>

class GravitySystem
{
private:
    bool gravityEnabled;  // Gravity toggle state
    sf::Font font;        // Font for rendering the text
    sf::Text gravityText; // Text to display the gravity state

public:
    GravitySystem()
        : gravityEnabled(true)  // Gravity is on by default
    {
        // Load a font for the text display (you'll need to have a font file, e.g., "arial.ttf" in your project directory)
        if (!font.loadFromFile("arial.ttf")) {
            // Handle error loading font
        }

        // Setup text display
        gravityText.setFont(font);
        gravityText.setCharacterSize(24);
        gravityText.setFillColor(sf::Color::White);
        gravityText.setPosition(0.0f, 0.0f);
        updateGravityText();
    }

    // Toggle gravity on or off
    void toggleGravity()
    {
        gravityEnabled = !gravityEnabled;
        updateGravityText();
    }

    // Apply gravity to a velocity vector if gravity is enabled
    void applyGravity(Vector3f& velocity)
    {
        if (gravityEnabled) {
            velocity.y -= 0.0f;  // Simple gravity force (pulling downwards on the Y-axis)
        }
    }

    // Draw gravity status text
    void draw(sf::RenderWindow& window)
    {
        window.pushGLStates();  // Switch to SFML rendering state
        window.draw(gravityText); // Draw the text in the window
        window.popGLStates();   // Switch back to OpenGL rendering state
    }

private:
    // Update the text based on gravity state
    void updateGravityText()
    {
        gravityText.setString("Gravity: " + std::string(gravityEnabled ? "ON" : "OFF") + "\nPress 'G' to toggle");
    }
};

#endif // GRAVITY_HPP
