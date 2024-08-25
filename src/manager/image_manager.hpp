#pragma once
#include "../core/globals.hpp"

class ImageManager {
public:
    ImageManager() { };
    ~ImageManager() { };

    GLFWwindow* createWindow(int width, int height);
    GLFWwindow* getWindow();

private:
    std::map<const char*, Image*> mImages;

    struct ImageBuffers {
        unsigned int VBO;
        unsigned int VAO;
        unsigned int EBO;
    };
};