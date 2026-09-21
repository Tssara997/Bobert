#include "Window.h"

namespace Bobert {
  Window::Window(int width, int height, std::string title, EventManager* eventManager) : m_width{width}, m_height{height}, m_title{title}, m_eventManager{eventManager} {

  }


  Window::~Window() {
    if (m_window)
      ShutDown();
  }


  bool Window::Init() {
    m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);

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
    glfwSetCursorPosCallback(m_window, cursor_position_callback);
    glfwSetCursorEnterCallback(m_window, cursor_enter_callback);
    glfwSetWindowCloseCallback(m_window, window_should_close_callback);
    glfwSetWindowSizeCallback(m_window, window_size_callback);
    return true;
  }

  void Window::Update() {
  }


  void Window::SetAsCurrent() {
    glfwMakeContextCurrent(m_window);
  }


  void Window::PollEvents() {
    glfwPollEvents();
  }


  void Window::SwapBuffers() {
    glfwSwapBuffers(m_window);
  }


  void Window::ShutDown() {
    if (m_window) {
      glfwDestroyWindow(m_window);
      m_window = nullptr;
      Logger::Info("Destroyed window");
    }
  }


  void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (!glfwGetWindowAttrib(window, GLFW_FOCUSED))
      return;

    Window* app = static_cast<Window*>(glfwGetWindowUserPointer(window));

    if (action == GLFW_RELEASE)
      app->m_eventManager->TriggerEvent(KeyReleaseEvent(key));
    else
      app->m_eventManager->TriggerEvent(KeyPressEvent(key, action == GLFW_REPEAT));
  }


  void Window::mouse_button_callback(GLFWwindow* window, int button, int action, int mode) {
    if (!glfwGetWindowAttrib(window, GLFW_FOCUSED))
      return;

    Window* app = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (action == GLFW_RELEASE)
      app->m_eventManager->TriggerEvent(MouseReleaseEvent(button));
    else
      app->m_eventManager->TriggerEvent(MousePressEvent(button, action == GLFW_REPEAT));
  }


  void Window::cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    if (!glfwGetWindowAttrib(window, GLFW_FOCUSED))
      return;

    Window*app = static_cast<Window*>(glfwGetWindowUserPointer(window));
    app->m_eventManager->TriggerEvent(MousePositionEvent(xpos, ypos));
  }


  void Window::cursor_enter_callback(GLFWwindow* window, int entered) {
    if (!glfwGetWindowAttrib(window, GLFW_FOCUSED))
      return;

    Window* app = static_cast<Window*>(glfwGetWindowUserPointer(window));
    app->m_eventManager->TriggerEvent(MouseEnterEvent(entered == 1));
  }


  void Window::window_should_close_callback(GLFWwindow* window) {
    Window* app = static_cast<Window*>(glfwGetWindowUserPointer(window));
    glfwSetWindowShouldClose(window, GLFW_TRUE);
    app->m_eventManager->TriggerEvent(WindowCloseEvent());
    app->m_windowShouldClose = true;
  }


  void Window::window_size_callback(GLFWwindow* window, int width, int height) {
    Window* app = static_cast<Window*>(glfwGetWindowUserPointer(window));
    app->m_eventManager->TriggerEvent(WindowResizingEvent(width, height));
  }


  void Window::window_focus_callback(GLFWwindow* window, int focus) {
    Window* app = static_cast<Window*>(glfwGetWindowUserPointer(window));
    app->m_eventManager->TriggerEvent(WindowFocusEvent());
  }


  const int Window::GetWidth() const {
    return m_width;
  }


  const int Window::GetHeight() const {
    return m_height;
  }


  const std::string Window::GetTitle() const {
    std::string title = m_title;
    return title;
  }

  const bool Window::WindowShouldClose() const {
    return m_windowShouldClose;
  }


  void Window::Close() {
    m_eventManager->TriggerEvent(WindowCloseEvent());
    m_windowShouldClose = true;
  }


  Window* Window::GetWindow() {
    return this;
  }


  Window::Window(Window&& other) noexcept : m_width(other.m_width), m_height(other.m_height), m_title(other.m_title),
    m_windowShouldClose(other.m_windowShouldClose), m_window(other.m_window), m_eventManager(other.m_eventManager) {

    other.m_width = 0;
    other.m_height = 0;
    other.m_title = "";
    other.m_windowShouldClose = false;
    other.m_window = nullptr;
    other.m_eventManager = nullptr;

    if (m_window)
      glfwSetWindowUserPointer(m_window, this);
  }


  Window& Window::operator=(Window&& other) noexcept {
    if (this == &other)
      return *this;

    if(m_window)
      glfwDestroyWindow(m_window);

    m_width = other.m_width;
    m_height = other.m_height;
    m_title = other.m_title;
    m_windowShouldClose = other.m_windowShouldClose;
    m_window = other.m_window;
    m_eventManager = other.m_eventManager;

    other.m_width = 0;
    other.m_height = 0;
    other.m_title = "";
    other.m_windowShouldClose = false;
    other.m_window = nullptr;
    other.m_eventManager = nullptr;

    if (m_window)
      glfwSetWindowUserPointer(m_window, this);

    return *this;
  }


  bool Window::operator==(const Window& other) const {
    return m_window == other.m_window;
  }

  bool Window::operator==(const GLFWwindow* other) const {
    return m_window == other;
  }
};