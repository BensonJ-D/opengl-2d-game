#pragma once
#include "../core/globals.hpp"
#include <string>

class ImageManager {
public:
    ImageManager() { };
    ~ImageManager() { };

    Image* loadImage(std::string name, std::string resourcePath);

private:
    std::map<std::string, Image*> mImages;

    struct ImageBuffers {
        unsigned int VBO;
        unsigned int VAO;
        unsigned int EBO;
    };
};