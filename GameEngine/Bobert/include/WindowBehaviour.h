#pragma once
#include "Event\InputListener.h"

namespace Bobert {
    class Bobert_API WindowBehaviour : public InputListener {
        public:
            WindowBehaviour() : handled{true} {
                backgroundColor = defBackgroundColor;
            }

            void OnKeyPress(const KeyPressEvent& e) override {}
            void OnKeyRelease(const KeyReleaseEvent& e) override {}

            void ChangeBackgroundColor(float r, float b, float g, float a) {
                backgroundColor = {r, b, g, a};
                handled = false;
            }
        
        public:
            const std::array<float, 4> defBackgroundColor = {0.1f, 0.1f, 0.15f, 1.0f};
            std::array<float, 4> backgroundColor;
            bool handled;
    };
};