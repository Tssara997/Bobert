#include "include/Event/Event.h"
#include "include/Window.h"

namespace Bobert {
  UserEvent::UserEvent(Window& window) : m_window(&window) {}

  const Window& UserEvent::GetWindow() const {
    return *m_window;
  }
};
