#pragma once
#include <string>
#include <map>
#include <vector>

#include "../../core/globals.hpp"
#include "../domain/sprite.hpp"
#include "../domain/image.hpp"
#include "../factory/image_factory.hpp"
#include "../factory/sprite_factory.hpp"

namespace render {
    class ImageManager {
        private:
            ImageFactory mImageFactory;
            SpriteFactory mSpriteFactory;
        
            std::map<std::string, Image*> mImages;
            std::map<Image*, std::vector<Sprite*>*> mSpriteBatches;
            
            typedef struct {
                unsigned int VBO;
                unsigned int VAO;
                unsigned int EBO;
            } ImageBuffers;
            
        public:
            ImageManager();
            ~ImageManager();

            ImageBuffers generateBuffers(float vertices[], unsigned long verticesSize, unsigned int indices[], unsigned long indicesSize);
            Image* loadImage(std::string name, std::string resourcePath);
            Sprite* createSprite(Image* image);
    };
}

