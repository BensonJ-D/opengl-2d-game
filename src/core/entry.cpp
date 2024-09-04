#include "render/manager/image_manager.hpp"
#include "core/manager/window_manager.hpp"
#include "render/domain/shader.hpp"
#include "render/camera.hpp"
#include "render/domain/image.hpp"
#include "object/domain/sprite.hpp"
#include "object/factory/object_factory.hpp"
#include "object/factory/sprite_factory.hpp"
#include "object/manager/sprite_manager.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>
#include <iostream>

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

void draw(GLFWwindow* window, Camera* camera, Shader shaderProgram, unsigned int instanceVBO, obj::SpriteManager* spriteManager)
{

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glm::mat4 view          = camera->GetViewMatrix();
    glm::mat4 projection    = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -100.0f, 100.0f);

    shaderProgram.setMat4("projection", projection);
    shaderProgram.setMat4("view", view);
    
    for(auto spriteBatch : spriteManager->mSpritesByImage){
        glBindTexture(GL_TEXTURE_2D, spriteBatch.first->getTextureId());
        
        std::vector<glm::mat4> modelMatrices;
        
        for(auto sprite : *(spriteBatch.second)) {
            modelMatrices.push_back(sprite->getModelMatrix());
        }
        
        glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * modelMatrices.size(), &modelMatrices[0], GL_STATIC_DRAW);
        
        glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
        
        int pos = 3;
        int pos1 = pos + 0;
        int pos2 = pos + 1;
        int pos3 = pos + 2;
        int pos4 = pos + 3;
        glEnableVertexAttribArray(pos1);
        glEnableVertexAttribArray(pos2);
        glEnableVertexAttribArray(pos3);
        glEnableVertexAttribArray(pos4);
        glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
        glVertexAttribPointer(pos1, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4 * 4, (void*)(0));
        glVertexAttribPointer(pos2, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4 * 4, (void*)(sizeof(float) * 4));
        glVertexAttribPointer(pos3, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4 * 4, (void*)(sizeof(float) * 8));
        glVertexAttribPointer(pos4, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4 * 4, (void*)(sizeof(float) * 12));
        glVertexAttribDivisor(pos1, 1);
        glVertexAttribDivisor(pos2, 1);
        glVertexAttribDivisor(pos3, 1);
        glVertexAttribDivisor(pos4, 1);
        
        glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, (int)modelMatrices.size());
    }
//    std::cin.get();
    
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
    render::Image* enemyImage = imageManager->loadImage("enemy", "Resources/Images/Enemy.png");
    auto [ VBO, VAO, EBO ] = imageManager->generateBuffers(vertices, sizeof(vertices), indices, sizeof(indices));
    
    
    unsigned int instanceVBO;
    glGenBuffers(1, &instanceVBO);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    
    obj::ObjectFactory* objectFactory = new obj::ObjectFactory();
    obj::Object* object = objectFactory->create();
    
    obj::SpriteManager* spriteManager = new obj::SpriteManager();
    
    for(int i = 0; i < 8000; i++) {
        spriteManager->create(enemyImage, rand() % 800, rand() % 600, object);
    }
    
    Shader shaderProgram("Resources/Shaders/vertex_shader.vs", "Resources/Shaders/fragment_shader.fs");
    
    if(window != NULL){
        Camera* camera = new Camera();
        glBindVertexArray(VAO);

        // render container
        shaderProgram.use();
        
        while (!glfwWindowShouldClose(window)) {
            processInput(window, camera, object);
            draw(window, camera, shaderProgram, instanceVBO, spriteManager);
        }
        
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    exit(EXIT_SUCCESS);

    return 0;
}
