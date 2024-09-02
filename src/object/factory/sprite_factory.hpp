#pragma once
#include <vector>
#include <map>

#include "object/interface/object_factory_interface.hpp"
#include "object/domain/sprite.hpp"
#include "render/domain/image.hpp"

namespace obj {
    class SpriteFactory : public IObjectFactory {
        public:
            Sprite* create(int x, int y, IObject *pParent = nullptr) override;
            Sprite* create(render::Image *pImage, int x = 0, int y = 0, IObject *pParent = nullptr);
    };
}
