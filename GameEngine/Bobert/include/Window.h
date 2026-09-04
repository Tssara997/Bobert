#pragma once

#include "Core.h"
#include "Logger.h"
#include "Event/EventManager.h"
#include "Event/KeyEvent.h"
#include "Event/MouseEvent.h"

namespace Bobert {
  class Bobert_API Window {
    public:

    Window(int width, int height, EventManager* eventManager);
    // ~Window();

    bool Init();
    void Update();
    void ShutDown();

    const int GetWidth() const;
    const int GetHeight() const;
    const bool WindowShouldClose() const;

    private:
     int m_width;
     int m_height;
     bool m_windowShouldClose = false;
     GLFWwindow* m_window;
     EventManager* m_eventManager;

     std::array<float, 4> m_backgroundColor;

     static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
     static void mouse_button_callback(GLFWwindow* window, int button, int action, int mode);
     static void window_should_close_callback(GLFWwindow* window);
     void OnKeyPress(const KeyPressEvent& e);

  };
};