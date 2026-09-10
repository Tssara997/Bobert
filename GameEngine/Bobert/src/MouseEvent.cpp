#include "include/Event/MouseEvent.h"
#include "include/Window.h"

namespace Bobert {
  MouseEnterEvent::MouseEnterEvent(bool isEnter, Window& window) : m_isEnter(isEnter), m_window(&window) {}

  const Window& MouseEnterEvent::GetWindow() const {
    return *m_window;
  }
};