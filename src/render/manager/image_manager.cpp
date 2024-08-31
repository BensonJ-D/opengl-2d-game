#include "image_manager.hpp"

#include <iostream>

#include "../domain/image.hpp"
#include "../factory/image_factory.hpp"
#include "../factory/sprite_factory.hpp"

namespace render {
    ImageManager::ImageManager() {
        mImageFactory = ImageFactory();
        mSpriteFactory = SpriteFactory();
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

    Sprite* ImageManager::createSprite(Image* image) {
        Sprite* _sprite = new Sprite(0, 0, 32, 64, 0, 0, image);

        auto keyExists = mSpriteBatches.count(image);
        if (keyExists != 1) {
            auto pair = std::pair<Image*, std::vector<Sprite*>*>(image, new std::vector<Sprite*>{ _sprite });
            mSpriteBatches.insert(pair);
            printf("New batch\n");
        } else {
            auto vector = mSpriteBatches.at(image);
            vector->push_back(_sprite);
            printf("Existing batch\n");
        }

        printf("Number of sprite in batch: %lu\n", mSpriteBatches.at(image)->size());

        return _sprite;
    }
}
