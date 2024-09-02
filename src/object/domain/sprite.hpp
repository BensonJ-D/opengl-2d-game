#pragma once
#include <map>
#include <vector>

#include "object/interface/object_interface.hpp"
#include "render/domain/image.hpp"
#include "core/opengl.hpp"

namespace obj {
    class Sprite : public IObject {
        private:
            render::Image *mImage;
            int mFrame = 0;
            int mFrames = 0;
            int mImgh = 0, mImgw = 0;
            int mFrameTime = 0, mLastFrame = 0;

        public:
            using IObject::IObject;
            
            GLuint getTextureId();
            int getCurrentFrame();
            int getTotalFrames();
            int getImageWidth();
            int getImageHeight();
            void advanceFrame();
            void rewindFrame();
            void setFrame(int frame);
            void setSourceImage(render::Image *image);
        
            void update() override;
    };
}

