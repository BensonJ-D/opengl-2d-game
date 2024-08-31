#pragma once
#include "object_interface.hpp"

namespace obj {
    class Object : public IObject {
        private:
            
        public:
            Object(int x, int y);
            void update() override;
    };
}
