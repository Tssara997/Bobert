#pragma once

#include "include\Core.h"
#include "KeyEvent.h"
#include "MouseEvent.h"
#include "include\Logger.h"

namespace Bobert {
  class Bobert_API InputListener {
    public:
    // Keyboard
      virtual void OnKeyPress(const KeyPressEvent& e) {};
      virtual void OnKeyRelease(const KeyReleaseEvent& e) {};

    // Mouse
      virtual void OnMouse(const MouseEvent& e) {};
  };
}