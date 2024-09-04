#pragma once
#include <string>
#include <map>
#include <vector>

#include "core/globals.hpp"
#include "render/domain/image.hpp"
#include "render/factory/image_factory.hpp"

namespace render {
    class ImageManager {
        private:
            ImageFactory mImageFactory;
        
            std::map<std::string, Image*> mImages;
            
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
            Image* getImage(std::string name);
    };
}

