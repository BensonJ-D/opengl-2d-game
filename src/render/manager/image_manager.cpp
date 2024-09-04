#include "image_manager.hpp"

#include <iostream>

#include "render/domain/image.hpp"
#include "render/factory/image_factory.hpp"

namespace render {
    ImageManager::ImageManager() {
        mImageFactory = ImageFactory();
    };
    ImageManager::~ImageManager() {};

    ImageManager::ImageBuffers ImageManager::generateBuffers(float vertices[], unsigned long verticesSize, unsigned int indices[], unsigned long indicesSize) {
        unsigned int VBO, VAO, EBO;

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);
        
        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        
        // color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        
        // texture coord attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
        
        
        return { VBO, VAO, EBO };
    }

    Image* ImageManager::loadImage(std::string name, std::string resourcePath) {
        auto existingImage = mImages.find(name);
        if(existingImage != mImages.end()) {
            std::cout << "Image already exists, returning existing image." << std::endl;
            return existingImage->second;
        }
        
        render::Image* image = mImageFactory.loadImage(resourcePath);
        mImages.emplace(name, image);
        return image;
    }
    
    Image* ImageManager::getImage(std::string name) {
        auto imagePair = mImages.find(name);
        
        if(imagePair == mImages.end()) {
            return nullptr;
        }
        return imagePair->second;
    }
}
