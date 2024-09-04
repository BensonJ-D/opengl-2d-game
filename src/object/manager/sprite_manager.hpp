#pragma once

#include <map>
#include <vector>

#include "object/domain/sprite.hpp"
#include "object/factory/sprite_factory.hpp"
#include "render/domain/image.hpp"

namespace obj {
    class SpriteManager {
        private:
            SpriteFactory *mSpriteFactory;
        
        public:
            std::map<render::Image*, std::vector<Sprite*>*> mSpritesByImage;
        
            SpriteManager();
            ~SpriteManager();
        
            Sprite* create(render::Image* pImage, int x = 0, int y = 0, IObject *pParent = nullptr);
            void remove(Sprite* pSprite) {};
        
            
    };
}
