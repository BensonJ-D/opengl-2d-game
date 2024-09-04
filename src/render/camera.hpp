#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

const float SPEED       =  25.0f;
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
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 GetViewMatrix();
    
    void UpdatePosition(glm::vec3 position);
    void processInput(Camera_Movement direction, float deltaTime);
};
