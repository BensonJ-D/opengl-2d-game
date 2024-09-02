#pragma once

namespace interface {
    template <typename T>
    class IFactory {
        public:
            IFactory() { };
            ~IFactory() { };
        
            virtual T* create() { return new T(); };
    };
}
