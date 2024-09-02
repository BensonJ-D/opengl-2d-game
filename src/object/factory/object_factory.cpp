#include "object_factory.hpp"

#include "object/domain/object.hpp"

namespace obj {
    Object* ObjectFactory::create(int x, int y, IObject *pParent) {
        return new Object(x, y, pParent);
    }
}
