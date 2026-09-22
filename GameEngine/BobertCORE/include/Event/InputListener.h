#pragma once

#include "KeyEvent.h"
#include "MouseEvent.h"
#include "WindowEvent.h"
#include "Logger.h"

namespace Bobert {
  /// @brief Base class for all behaviours. Sets all callback functions that can be used by a client to receive an event. The function is called when event manager gets the corresponding event.
  class InputListener {
    public:
    // Keyboard Events
      virtual void OnKeyPress(const KeyPressEvent& e) {};
      virtual void OnKeyRelease(const KeyReleaseEvent& e) {};

    // Mouse Events
      virtual void OnMousePress(const MousePressEvent& e) {};
      virtual void OnMouseRelease(const MouseReleaseEvent& e) {};
      virtual void OnMousePosition(const MousePositionEvent& e) {};
      virtual void OnMouseEnter(const MouseEnterEvent& e) {};

    // Window Events
      virtual void OnWindowClose(const WindowCloseEvent& e) {};
      virtual void OnWindowFocus(const WindowFocusEvent& e) {};
      virtual void OnWindowResize(const WindowResizingEvent& e) {};
  };
}