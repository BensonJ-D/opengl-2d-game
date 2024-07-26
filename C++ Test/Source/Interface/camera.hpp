#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

const float SPEED       =  125.0f;
const float SENSITIVITY =  0.1f;

enum Camera_Movement {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
    // camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 WorldUp;
    
    // camera options
    float MovementSpeed;
    
    // constructor with vectors
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f)) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED) {
        Position = position;
        WorldUp = up;
    }

    glm::mat4 GetViewMatrix()
    {
        glm::mat4 view = glm::mat4(1.0f);
        return glm::translate(view, Position);
    }
    
    void UpdatePosition(glm::vec3 position) {
        Position = position;
    }
    
    void processInput(Camera_Movement direction, float deltaTime)
    {
        float velocity = MovementSpeed * deltaTime;
        
        if (direction == UP)
            Position += velocity * glm::vec3(0.0f, -1.0f, 0.0f);
        if (direction == DOWN)
            Position += velocity * glm::vec3(0.0f, 1.0f, 0.0f);
        if (direction == LEFT)
            Position += velocity * glm::vec3(-1.0f, 0.0f, 0.0f);
        if (direction == RIGHT)
            Position += velocity * glm::vec3(1.0f, 0.0f, 0.0f);
    }

};
