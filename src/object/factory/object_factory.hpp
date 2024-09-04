#pragma once
#include <vector>
#include <map>

#include "object/interface/object_factory_interface.hpp"
#include "object/domain/object.hpp"

namespace obj {
    class ObjectFactory : public IObjectFactory {
        public:
            Object* create(int x = 0, int y = 0, IObject *pParent = nullptr) override;
    };
}
