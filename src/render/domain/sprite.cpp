#include "sprite.hpp"

namespace render {
    Sprite::Sprite(int xOffset, int yOffset, int width, int height, int frames, int frameTime, Image* image) :
        mXOffset(xOffset), mYOffset(yOffset), mWidth(width), mHeight(height), mFrame(0), mFrames(frames), mFrameTime(frameTime),
        mTextureID(image->getTextureId()), mImgh(image->getHeight()), mImgw(image->getWidth()) {};

    GLuint Sprite::getTextureId() { return mTextureID; }
}
