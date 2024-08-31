#include "object_factory.hpp"

#include "../domain/object.hpp"
#include "../../render/domain/sprite.hpp"

namespace obj {
    ObjectFactory::ObjectFactory() {};
    ObjectFactory::~ObjectFactory() {};
    
    Object* ObjectFactory::createObject(int x, int y) {
        return new Object(x, y);
    };
    
    Object* ObjectFactory::attachSprite(Object *pObject, render::Sprite *pSprite) {
        pObject->setSprite(pSprite);
        return pObject;
    };
}
