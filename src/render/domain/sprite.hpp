#pragma once
#include "image.hpp"

#include <map>
#include <vector>

#include "../../core/opengl.hpp"

namespace render {
    class Sprite {
        private:
            const GLuint mTextureID;
            int mXOffset, mYOffset;
            int mHeight, mWidth;
            int mFrame;
            int mFrames;
            int mImgh, mImgw;
            int mFrameTime, mLastFrame;

        public:
            Sprite(int xOffset, int yOffset, int width, int height, int frames, int frameTime, Image* image);
            ~Sprite() {};
            
            GLuint getTextureId();
            
            void advanceFrame(Sprite* sprite);
    };
}

