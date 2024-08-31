#pragma once
#include "../../render/domain/sprite.hpp"

namespace obj {
    class IObject {
        protected:
            bool mEnabled = false;
            render::Sprite *mSprite;
            int mX, mY;
        
        public:
            IObject();
            ~IObject();

            virtual void update() = 0;
            
            void setSprite(render::Sprite *sprite);
            void setEnabled(bool enabled);
            void setPosition(int x, int y);
    };
}
