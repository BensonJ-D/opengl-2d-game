#include "render/manager/image_manager.hpp"
#include "core/manager/window_manager.hpp"
#include "render/domain/shader.hpp"
#include "render/camera.hpp"
#include "render/domain/image.hpp"
#include "object/domain/sprite.hpp"
#include "object/factory/object_factory.hpp"
#include "object/factory/sprite_factory.hpp"

#include <glm/glm.hpp>
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
float deltaTime = 0.0f;
float lastFrame = 0.0f;

void draw(GLFWwindow* window, Camera* camera, Shader shaderProgram, unsigned int VAO, obj::Sprite* sprite, obj::Sprite* sprite2)
{

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glm::mat4 model         = glm::mat4(1.0f);
    glm::mat4 view          = camera->GetViewMatrix();
    glm::mat4 projection    = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -100.0f, 100.0f);
    
    model         = sprite->getModelMatrix();

    shaderProgram.setMat4("projection", projection);
    shaderProgram.setMat4("view", view);
    shaderProgram.setMat4("model", model);

//    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    model         = glm::mat4(1.0f);
    view          = camera->GetViewMatrix();
    projection    = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -100.0f, 100.0f);
    
    if(sprite2) {
        model         = sprite2->getModelMatrix();

        shaderProgram.setMat4("projection", projection);
        shaderProgram.setMat4("view", view);
        shaderProgram.setMat4("model", model);

    //    glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
    
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void processInput(GLFWwindow *window, Camera* camera, obj::IObject* pObject)
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

    float movementSpeed = static_cast<float>(2.5f);
    glm::vec3 movement = glm::vec3(0.0f);
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        movement += movementSpeed * glm::vec3(0.0f, -1.0f, 0.0f);
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        movement += movementSpeed * glm::vec3(0.0f, 1.0f, 0.0f);
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        movement += movementSpeed * glm::vec3(-1.0f, 0.0f, 0.0f);
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        movement += movementSpeed * glm::vec3(1.0f, 0.0f, 0.0f);
    
    movement += pObject->getPosition();
    pObject->setPosition(movement);
}

int start()
{
    WindowManager* windowManager = new WindowManager();
    GLFWwindow* window = windowManager->createWindow(800, 600);

    render::ImageManager* imageManager = new render::ImageManager();
    render::Image* image = imageManager->loadImage("player", "Resources/Images/Player.png");
    auto [ VBO, VAO, EBO ] = imageManager->generateBuffers(vertices, sizeof(vertices), indices, sizeof(indices));
    
    obj::ObjectFactory* objectFactory = new obj::ObjectFactory();
    obj::Object* object = objectFactory->create(rand() % 800, rand() % 600);
    
    obj::SpriteFactory* spriteFactory = new obj::SpriteFactory();
    obj::Sprite* sprite = spriteFactory->create(image, 0, 0, object);
    obj::Sprite* sprite2 = spriteFactory->create(image, 10, 10, object);
    
    Shader shaderProgram("Resources/Shaders/vertex_shader.vs", "Resources/Shaders/fragment_shader.fs");
    
    if(window != NULL){
        Camera* camera = new Camera();
        glBindVertexArray(VAO);
        
        glBindTexture(GL_TEXTURE_2D, sprite->getTextureId());

        // render container
        shaderProgram.use();
        
        while (!glfwWindowShouldClose(window)) {
            processInput(window, camera, object);
            draw(window, camera, shaderProgram, VAO, sprite, sprite2);
            counter++;
            if(counter > 100 && sprite2) {
                delete sprite2;
                sprite2 = nullptr;
                std::cout << "Deleting sprite 2" << std::endl;
            }
        }
        
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    exit(EXIT_SUCCESS);

    return 0;
}
