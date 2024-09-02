#pragma once
#include "object_interface.hpp"

namespace obj {
    class Object : public IObject {
        private:
            using IObject::IObject;
            
        public:
            void update() override;
    };
}
