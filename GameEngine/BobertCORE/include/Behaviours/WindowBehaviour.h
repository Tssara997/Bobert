#pragma once

#include "Behaviour.h"
#include "Window.h"

namespace Bobert {

    class Bobert_API WindowBehaviour : public Behaviour {
        public:
            WindowBehaviour() { }
            void SetWindow(Window& window) {m_window = &window;}

            const Window* GetWindow() const {return m_window;}
        protected:
            Window* m_window;
    };
};