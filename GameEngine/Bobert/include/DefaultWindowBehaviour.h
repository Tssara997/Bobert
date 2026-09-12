#pragma once
#include "WindowBehaviour.h"

namespace Bobert {

  class DefaultWindowBehaviour : public WindowBehaviour {
    public:
      DefaultWindowBehaviour() : WindowBehaviour() {}

      void OnKeyPress(const KeyPressEvent& e) override {
        if (e.GetKey() == 256)
          m_window->Close();
      }

    private:

  };
};