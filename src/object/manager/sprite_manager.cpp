#include "sprite_manager.hpp"

#include <iostream>
#include "object/interface/object_interface.hpp"
#include "render/domain/image.hpp"

namespace obj {
    SpriteManager::SpriteManager() {
        mSpriteFactory = new SpriteFactory();
    }
    
    Sprite* SpriteManager::create(render::Image *pImage, int x, int y, IObject *pParent) {
        Sprite *sprite = mSpriteFactory->create(pImage, x, y, pParent);
        auto keyExists = mSpritesByImage.count(pImage);
        if (keyExists != 1) {
            auto pair = std::pair<render::Image*, std::vector<Sprite*>*>(pImage, new std::vector<Sprite*>{ sprite });
            mSpritesByImage.insert(pair);
            printf("New batch\n");
        } else {
            auto vector = mSpritesByImage.at(pImage);
            vector->push_back(sprite);
            printf("Existing batch\n");
        }
        
        std::cout << "Number of sprite in batch: " << mSpritesByImage.at(pImage)->size() << std::endl;
        return sprite;
    }
}
