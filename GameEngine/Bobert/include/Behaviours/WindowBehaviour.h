#pragma once

#include "Behaviour.h"

namespace Bobert {

    class Bobert_API WindowBehaviour : public Behaviour {
        public:
            WindowBehaviour() { }


            void ChangeBackgroundColor(const float& r, const float& b, const float& g, const float& a) {
                if (m_window) {
                    m_window->ChangeBackgroundColor(r, b, g, a);
                }
            }


            void ChangeBackgroundColor(const std::array<float, 4>& backgroundColor) {
                if (m_window)
                    m_window->ChangeBackgroundColor(backgroundColor);
            }

            const std::array<float, 4> defBackgroundColor = {0.1f, 0.1f, 0.15f, 1.0f};
    };
};