#pragma once

#include "../domain/object.hpp"
#include "../../render/domain/sprite.hpp"

namespace obj {
    class ObjectFactory {
        public:
            ObjectFactory();
            ~ObjectFactory();
            Object* createObject(int x, int y);
            Object* attachSprite(Object *pObject, render::Sprite *pSprite);
    };
}
