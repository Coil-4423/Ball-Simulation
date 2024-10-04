#ifndef BALL_HPP
#define BALL_HPP

#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "vector3f.hpp"
#include "gravity.hpp" // Add gravity system

// Constants
const int BALL_COUNT = 3;   // Number of small balls
const float SMALL_BALL_RADIUS = 1.0f; // Relatively small balls
const float LARGE_BALL_RADIUS = 1.0f; // Large ball for Brownian motion
const float SPHERE_RADIUS = 10.0f;


class BallSystem
{
private:
    std::vector<Vector3f> positions;
    std::vector<Vector3f> velocities;
    GravitySystem* gravitySystem;  // Reference to the gravity system
    Vector3f largeBallPosition = { 0.0f, 0.0f, 0.0f };
    Vector3f largeBallVelocity = { 0.0f, 0.0f, 0.0f };
    Vector3f sphereCenter = { 0.0f, 0.0f, 0.0f };
    float boundary; // Boundary variable

public:
    // Constructor now takes Shpere radius
    BallSystem(GravitySystem* gravity, float length)
        : gravitySystem(gravity), boundary(length) // Initialize boundary
    {
        // Initialize random seed
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        // Initialize small balls
        for (int i = 0; i < BALL_COUNT; ++i)
        {
            positions.push_back({ (rand() % 200 - 100) / 10.0f, (rand() % 200 - 100) / 10.0f, (rand() % 200 - 100) / 10.0f });
            //positions.push_back({ 9.0f, 0.0f, 0.0f });
            //velocities.push_back({ 0.0f, -0.01f, 0.0f });

            velocities.push_back({ (rand() % 200 - 100) / 1000.0f, (rand() % 200 - 100) / 1000.0f, (rand() % 200 - 100) / 1000.0f });
        }
    }

    // Check if the ball is colliding with the surface of a wall
    void checkWallCollision(Vector3f& position, Vector3f& velocity, float radius)
    {
        // X-axis collision (left and right walls)
        if (position.x - radius < -boundary)  // Left wall collision
        {
            position.x = -boundary + radius;  // Prevent ball from going through the wall
            velocity.x = -velocity.x;         // Reflect velocity
        }
        else if (position.x + radius > boundary)  // Right wall collision
        {
            position.x = boundary - radius;
            velocity.x = -velocity.x;
        }
        // Y-axis collision (top and bottom walls)
        if (position.y - radius < -boundary)  // Bottom wall collision
        {
            position.y = -boundary + radius;
            velocity.y = -velocity.y;
        }
        else if (position.y + radius > boundary)  // Top wall collision
        {
            position.y = boundary - radius;
            velocity.y = -velocity.y;
        }
        // Z-axis collision (front and back walls)
        if (position.z - radius < -boundary)  // Front wall collision
        {
            position.z = -boundary + radius;
            velocity.z = -velocity.z;
        }
        else if (position.z + radius > boundary)  // Back wall collision
        {
            position.z = boundary - radius;
            velocity.z = -velocity.z;
        }
    }

// Check if the ball is colliding with the spherical wall and handle reflection
void checkSphereCollision(Vector3f& position, Vector3f& velocity, float ballRadius, const Vector3f& sphereCenter, float sphereRadius)
{
    // Calculate the vector from the sphere's center to the ball's position
    Vector3f centerToBall = position - sphereCenter;

    // Calculate the distance between the ball and the sphere's center
    float distance = centerToBall.length();  // Assuming Vector3f has a length() method

    // Check if the ball is inside the sphere (i.e., within the combined radius)
    if (distance + ballRadius > sphereRadius)
    {
        // Normalize the collision normal (centerToBall vector)
        Vector3f normal = centerToBall.normalize();

        // Reflect the velocity based on the collision normal
        float dotProduct = velocity.dot(normal);
        velocity = velocity - normal * (2 * dotProduct);

        // Adjust the ball's position to avoid overlapping with the spherical wall
        position = sphereCenter + normal * (boundary - ballRadius);
    }

     //Check if the ball is outside the sphere (i.e., within the combined radius)
//    if (distance < sphereRadius + ballRadius)
//    {
//        // Normalize the collision normal (centerToBall vector)
//        Vector3f normal = centerToBall.normalize();
//
//        // Reflect the velocity based on the collision normal
//        float dotProduct = velocity.dot(normal);
//        velocity = velocity - normal * (2 * dotProduct);
//
//        // Adjust the ball's position to avoid overlapping with the spherical wall
//        position = sphereCenter + normal * (sphereRadius + ballRadius);
//    }
}


    // Check if two balls are colliding
    bool areBallsColliding(const Vector3f& pos1, const Vector3f& pos2, float radius1, float radius2)
    {
        float distanceSquared = (pos1 - pos2).dot(pos1 - pos2);
        float radiiSum = radius1 + radius2;
        return distanceSquared <= (radiiSum * radiiSum); // Collision if distance <= sum of radii
    }

    // Handle ball-to-ball collision
    void resolveCollision(Vector3f& pos1, Vector3f& vel1, float radius1, Vector3f& pos2, Vector3f& vel2, float radius2)
    {
        // Calculate the collision normal
        Vector3f collisionNormal = (pos1 - pos2).normalize();
        // Calculate relative velocity
        Vector3f relativeVelocity = vel1 - vel2;
        // Calculate velocity along the normal
        float velocityAlongNormal = relativeVelocity.dot(collisionNormal);
        // Prevent resolving collisions if balls are moving apart
        if (velocityAlongNormal > 0) return;
        // Simple impulse-based resolution
        float impulse = (2.0f * velocityAlongNormal) / (radius1 + radius2);
        vel1 -= collisionNormal * impulse * radius2;
        vel2 += collisionNormal * impulse * radius1;
    }

    void update()
    {
        // Move small balls and check collisions
        for (int i = 0; i < BALL_COUNT; ++i)
        {
            gravitySystem->applyGravity(velocities[i]); // Apply gravity
            positions[i].x += velocities[i].x;
            positions[i].y += velocities[i].y;
            positions[i].z += velocities[i].z;
            // Check for ball-wall surface collisions
            checkSphereCollision(positions[i], velocities[i], SMALL_BALL_RADIUS, sphereCenter, boundary);
            checkWallCollision(positions[i], velocities[i], SMALL_BALL_RADIUS);
            // Check for collisions with other balls
            for (int j = i + 1; j < BALL_COUNT; ++j)
            {
                if (areBallsColliding(positions[i], positions[j], SMALL_BALL_RADIUS, SMALL_BALL_RADIUS))
                {
                    resolveCollision(positions[i], velocities[i], SMALL_BALL_RADIUS, positions[j], velocities[j], SMALL_BALL_RADIUS);
                }
            }
        }
        // Update the light effects
        //lightEffect.update();
    }

    void draw()
    {
        glColor3f(0.0f, 1.0f, 1.0f); // Cyan color for small balls
        for (int i = 0; i < BALL_COUNT; ++i)
        {
            glPushMatrix();
            glTranslatef(positions[i].x, positions[i].y, positions[i].z);
            drawSphere(SMALL_BALL_RADIUS, 20, 20);
            glPopMatrix();
        }
        // Optionally, draw large ball here
        // Draw the light effects
        //lightEffect.draw();
    }

    // Draw 3D sphere
    void drawSphere(float radius, int slices, int stacks)
    {
        GLUquadric* quadric = gluNewQuadric();
        gluSphere(quadric, radius, slices, stacks);
        gluDeleteQuadric(quadric);
    }
};

#endif // BALL_HPP