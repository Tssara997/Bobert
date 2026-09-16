#pragma once

#include "include/Event/InputListener.h"
#include "include/Window.h"

namespace Bobert {
  class Bobert_API Behaviour : public InputListener {
    public:
      Behaviour() {}

      void SetWindow(Window& window) {m_window = &window;}

      const Window* GetWindow() const {return m_window;}

    protected:
      Window* m_window;
  };
};