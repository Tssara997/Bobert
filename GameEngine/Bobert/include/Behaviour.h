#pragma once

#include "Core.h"
#include "Event.h"

namespace Bobert {
  class Bobert_API Behaviour {
    public:
      virtual void OnKeyInput(const KeyEvent& e) {};
      virtual void OnMouseInput(const MouseEvent& e) {};
  };
}