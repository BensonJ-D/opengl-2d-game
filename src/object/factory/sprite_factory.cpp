#include "sprite_factory.hpp"

#include "object/domain/sprite.hpp"
#include "render/domain/image.hpp"

namespace obj {
    Sprite* SpriteFactory::create(int x, int y, IObject *pParent) {
        return new Sprite(x, y, pParent);
    }
    
    Sprite* SpriteFactory::create(render::Image* pImage, int x, int y, IObject *pParent) {
        Sprite *pSprite = create(x, y, pParent);
        pSprite->setSourceImage(pImage);
        return pSprite;
    }
}
