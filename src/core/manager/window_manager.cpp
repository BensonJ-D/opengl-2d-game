#include "window_manager.hpp"
#include <experimental/coroutine>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

KeyState KeyStates[256];

GLFWwindow* WindowManager::createWindow(int width, int height)
{
    if (!glfwInit()) {
        std::cout << "Failed to initialise GLFW" << std::endl;
        return NULL;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    // Without these two hints, nothing above OpenGL version 2.1 is supported
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    std::cout << "Creating window ..." << std::endl;
    GLFWwindow* window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        mWindow = window;
        return mWindow;
    }
    
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        mWindow = window;
        return mWindow;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, 
        []([[maybe_unused]] GLFWwindow* window, int width, int height) { 
            glViewport(0, 0, width, height); 
        });

    glfwMakeContextCurrent(window);
    
    std::cout << "Setting draw methods..." << std::endl;
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    std::cout << "Resizing display..." << std::endl;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    std::cout << "Setup complete, proceeding to main loop.\n" << std::endl;
   
    mWindow = window;
    return mWindow;
}

GLFWwindow* WindowManager::getWindow() {
    return mWindow;
}
