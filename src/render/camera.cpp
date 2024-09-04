#include "camera.hpp"


// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
Camera::Camera(glm::vec3 position, glm::vec3 up) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED) {
    Position = position;
    WorldUp = up;
}

glm::mat4 Camera::GetViewMatrix()
{
    glm::mat4 view = glm::mat4(1.0f);
    return glm::translate(view, Position);
}
    
void Camera::UpdatePosition(glm::vec3 position) {
    Position = position;
}

void Camera::processInput(Camera_Movement direction, float deltaTime)
{
    float velocity = MovementSpeed;
    
    if (direction == UP)
        Position += velocity * glm::vec3(0.0f, 1.0f, 0.0f);
    if (direction == DOWN)
        Position += velocity * glm::vec3(0.0f, -1.0f, 0.0f);
    if (direction == LEFT)
        Position += velocity * glm::vec3(1.0f, 0.0f, 0.0f);
    if (direction == RIGHT)
        Position += velocity * glm::vec3(-1.0f, 0.0f, 0.0f);
}
