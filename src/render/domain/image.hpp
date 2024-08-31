#pragma once

#define GL_SILENCE_DEPRECATION

#include <stdlib.h>
#include <string>

#include "../../core/globals.hpp"
#include "../../core/opengl.hpp"

namespace render {
    class Image {
        private:
            const unsigned int mWidth;
            const unsigned int mHeight;
            const GLuint mTextureId;
            
        public:
            Image(unsigned int width, unsigned int height, GLuint textureId);
            ~Image();
        
            unsigned int getWidth();
            unsigned int getHeight();
            GLuint getTextureId();
    };
}
