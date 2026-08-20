#pragma once
#include "Behaviour.h"

namespace Bobert {
    class Bobert_API WindowBehaviour : public Behaviour {
        public:
            WindowBehaviour() {
                backgroundColor = {0.1f, 0.1f, 0.15f, 1.0f};
            }
            void ChangeBackgroundColor(float r, float b, float g, float a) {
                backgroundColor = {r, b, g, a};
            }
        
        public:
            std::array<float, 4> backgroundColor;
    };
};