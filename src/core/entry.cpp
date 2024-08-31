#include "../render/manager/image_manager.hpp"
#include "../manager/window_manager.hpp"
#include "../render/shader.hpp"
#include "../interface/camera.hpp"
#include "../render/domain/image.hpp"
#include "../render/domain/sprite.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


float vertices[] = {
    // positions          // colors           // texture coords
    32.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f/6.0f, 0.0f,   // top right
    32.0f, 64.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f/6.0f, 1.0/4.0f,   // bottom right
    0.0f, 64.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f/4.0f,   // bottom left
    0.0f, 0.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.0f,    // top left
};


unsigned int indices[] = {
    0, 1, 3, // first triangle
    1, 2, 3,  // second triangle
};

int counter = 0;

glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
float deltaTime = 0.0f;
float lastFrame = 0.0f;

void draw(GLFWwindow* window, Camera* camera, Shader shaderProgram, unsigned int VAO, render::Sprite* image)
{

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindTexture(GL_TEXTURE_2D, image->getTextureId());

    // render container
    shaderProgram.use();
    
    glm::mat4 model         = glm::mat4(1.0f);
    glm::mat4 view          = camera->GetViewMatrix();
    glm::mat4 projection    = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -100.0f, 100.0f);
    
    model         = glm::translate(model, position);

    shaderProgram.setMat4("projection", projection);
    shaderProgram.setMat4("view", view);
    shaderProgram.setMat4("model", model);

//    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
}

void processInput(GLFWwindow *window, Camera* camera)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->processInput(UP, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->processInput(DOWN, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->processInput(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->processInput(RIGHT, deltaTime);
    
    float movementSpeed = static_cast<float>(72.5 * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        position += movementSpeed * glm::vec3(0.0f, -1.0f, 0.0f);
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        position += movementSpeed * glm::vec3(0.0f, 1.0f, 0.0f);
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        position += movementSpeed * glm::vec3(-1.0f, 0.0f, 0.0f);
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        position += movementSpeed * glm::vec3(1.0f, 0.0f, 0.0f);
}

int start()
{
    WindowManager* windowManager = new WindowManager();
    GLFWwindow* window = windowManager->createWindow(800, 600);

    render::ImageManager* imageManager = new render::ImageManager();
    render::Image* image = imageManager->loadImage("player", "Resources/Images/Player.png");
    
    auto [ VBO, VAO, EBO ] = imageManager->generateBuffers(vertices, sizeof(vertices), indices, sizeof(indices));
    auto sprite = imageManager->createSprite(image);
    
    Shader shaderProgram("Resources/Shaders/vertex_shader.vs", "Resources/Shaders/fragment_shader.fs");
    
    if(window != NULL){
        Camera* camera = new Camera();
        
        while (!glfwWindowShouldClose(window)) {
            glBindVertexArray(VAO);
            processInput(window, camera);
            draw(window, camera, shaderProgram, VAO, sprite);
        }
        
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    exit(EXIT_SUCCESS);

    return 0;
}
