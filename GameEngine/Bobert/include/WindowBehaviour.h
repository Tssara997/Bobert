#pragma once
#include "Event\InputListener.h"
#include "Window.h"
#include "pch.h"

namespace Bobert {

    class Bobert_API WindowBehaviour : public InputListener {
        public:
            WindowBehaviour() { }

            void SetWindow(Window& window) {m_window = &window;}


            void ChangeBackgroundColor(const float& r, const float& b, const float& g, const float& a) {
                if (m_window) {
                    m_window->ChangeBackgroundColor(r, b, g, a);
                }
            }


            void ChangeBackgroundColor(const std::array<float, 4>& backgroundColor) {
                if (m_window)
                    m_window->ChangeBackgroundColor(backgroundColor);
            }


            const Window* GetWindow() const {return m_window;}


            const std::array<float, 4> defBackgroundColor = {0.1f, 0.1f, 0.15f, 1.0f};
        protected:
            Window* m_window;
    };
};