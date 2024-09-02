#pragma once

#include "object_interface.hpp"
#include "core/interface/factory_interface.hpp"

namespace obj {
    class IObjectFactory : public interface::IFactory<IObject> {
        public:
            virtual IObject* create(int x, int y, IObject *pParent = nullptr) = 0;
    };
}
