#pragma once
#include <libpng/png.h>

#include "../domain/image.hpp"
#include "../../core/opengl.hpp"

namespace render {
    class ImageFactory {
        private:
            class IImageResource {
                protected:
                    unsigned int mWidth;
                    unsigned int mHeight;
                    GLuint mTextureId;
                public:
                    ~IImageResource();
                
                    unsigned int getWidth();
                    unsigned int getHeight();
                    GLuint getTextureId();
            };
        
            class PNGResource : public IImageResource {
                public:
                    PNGResource(FILE* pFile, BYTE* sig);
            };
        
        public:
            ImageFactory();
            ~ImageFactory();
        
            Image* loadImage(std::string filename);
    };
}
