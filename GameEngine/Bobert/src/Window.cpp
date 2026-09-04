#include "include/Window.h"

namespace Bobert {
  Window::Window(int width, int height, EventManager* eventManager) : m_width{m_width}, m_height{m_height}, m_eventManager{eventManager} {
    m_backgroundColor =  {0.1f, 0.1f, 0.15f, 1.0f};
  }


  bool Window::Init() {
    m_window = glfwCreateWindow(800, 600, "Okno z Window", nullptr, nullptr);
    Logger::Info("WINDOW");
    if (!m_window) {
      Logger::Error("Failed to create a GLFW window");
      ShutDown();
      return false;
    }

    Logger::Info("Created a GLFW window");
    glfwSetWindowUserPointer(m_window, this);

    glfwMakeContextCurrent(m_window);

    glfwSetKeyCallback(m_window, key_callback);
    glfwSetMouseButtonCallback(m_window, mouse_button_callback);
    glfwSetWindowCloseCallback(m_window, window_should_close_callback);
    return true;
  }

  void Window::Update() {
    glClearColor(m_backgroundColor[0], m_backgroundColor[1], m_backgroundColor[2], m_backgroundColor[3]);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwPollEvents();
    glfwSwapBuffers(m_window);
  }


  void Window::ShutDown() {
    glfwDestroyWindow(m_window);
    Logger::Info("Destroyed window");
  }


  void Window::window_should_close_callback(GLFWwindow* window) {
    Window* app = static_cast<Window*>(glfwGetWindowUserPointer(window));
    glfwSetWindowShouldClose(window, GLFW_TRUE);
    app->m_windowShouldClose = true;
  }


  void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    Window* app = static_cast<Window*>(glfwGetWindowUserPointer(window));

    if (action == GLFW_RELEASE)
      app->m_eventManager->TriggerEvent(KeyReleaseEvent(key));
    else
      app->m_eventManager->TriggerEvent(KeyPressEvent(key, action == GLFW_REPEAT));
  }


  void Window::mouse_button_callback(GLFWwindow* window, int button, int action, int mode) {
    if (action != GLFW_PRESS)
      return;
    Window* app = static_cast<Window*>(glfwGetWindowUserPointer(window));
    app->m_eventManager->TriggerEvent(MouseEvent(button));
  }


  void Window::OnKeyPress(const KeyPressEvent& e) {
    if (e.GetKey() == 256)
      m_windowShouldClose = true;
  }


  const int Window::GetWidth() const {
    return m_width;
  }


  const int Window::GetHeight() const {
    return m_height;
  }


  const bool Window::WindowShouldClose() const {
    return m_windowShouldClose;
  }
};