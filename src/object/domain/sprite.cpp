#include "sprite.hpp"

#include "render/domain/image.hpp"
#include "core/opengl.hpp"

namespace obj {
    GLuint Sprite::getTextureId() { return mImage->getTextureId(); }
    int Sprite::getCurrentFrame() { return mFrame; }
    int Sprite::getTotalFrames() { return mFrames; }
    int Sprite::getImageWidth() { return mImage->getWidth(); }
    int Sprite::getImageHeight() { return mImage->getHeight(); }
    
    void Sprite::setSourceImage(render::Image *image) { mImage = image; }
    void Sprite::setFrame(int frame) { mFrame = frame; }
    void Sprite::advanceFrame() { mFrame = mFrame + 1 % mFrames; }
    void Sprite::rewindFrame() { mFrame = mFrame - 1 % mFrames; }
    
    void Sprite::update() {}
}
