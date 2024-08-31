#include "image.hpp"

namespace render {
    Image::Image(unsigned int width, unsigned int height, GLuint textureId) : mWidth(width), mHeight(height), mTextureId(textureId) { };
    Image::~Image(){};

    unsigned int Image::getWidth() { return mWidth; }
    unsigned int Image::getHeight() { return mHeight; }
    GLuint Image::getTextureId() { return mTextureId; }
}
