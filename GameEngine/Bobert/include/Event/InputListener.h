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
      virtual void OnMousePress(const MousePressEvent& e) {};
      virtual void OnMouseRelease(const MouseReleaseEvent& e) {};
      virtual void OnMousePosition(const MousePositionEvent& e) {};
      virtual void OnMouseEnter(const MouseEnterEvent& e) {};
  };
}