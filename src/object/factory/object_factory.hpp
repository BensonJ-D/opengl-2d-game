#pragma once
#include <vector>
#include <map>

#include "object/interface/object_factory_interface.hpp"
#include "object/domain/object.hpp"

namespace obj {
    class ObjectFactory : public IObjectFactory {
        public:
            Object* create(int x, int y, IObject *pParent = nullptr) override;
    };
}
