#pragma once

#include "KeyEvent.h"
#include "MouseEvent.h"
#include "WindowEvent.h"
#include "include\Logger.h"

namespace Bobert {
  class InputListener {
    public:
    // Keyboard
      virtual void OnKeyPress(const KeyPressEvent& e) {};
      virtual void OnKeyRelease(const KeyReleaseEvent& e) {};

    // Mouse
      virtual void OnMousePress(const MousePressEvent& e) {};
      virtual void OnMouseRelease(const MouseReleaseEvent& e) {};
      virtual void OnMousePosition(const MousePositionEvent& e) {};
      virtual void OnMouseEnter(const MouseEnterEvent& e) {};

    // Window
      virtual void OnWindowClose(const WindowCloseEvent& e) {};
      virtual void OnWindowFocus(const WindowFocusEvent& e) {};
      virtual void OnWindowResize(const WindowResizingEvent& e) {};
  };
}