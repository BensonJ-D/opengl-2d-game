#include "object.hpp"

#include "../../render/domain/sprite.hpp"

namespace obj {
    IObject::IObject() {};
    IObject::~IObject() {};

    void IObject::setSprite(render::Sprite *sprite) { mSprite = sprite; }
    void IObject::setEnabled(bool enabled) { mEnabled = enabled; }
    void IObject::setPosition(int x, int y) {
        mX = x;
        mY = y;
    }
}
