#include "object.hpp"

namespace obj {
    Object::Object(int x, int y) {
        setPosition(x, y);
    };
    
    void Object::update() {};
}
