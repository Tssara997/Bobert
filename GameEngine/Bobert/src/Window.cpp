#include "include/Window.h"

namespace Bobert {
  Window::Window(int width, int height, const char* title, EventManager* eventManager) : m_width{width}, m_height{height}, m_title{title}, m_eventManager{eventManager} {
    m_backgroundColor =  {0.1f, 0.1f, 0.15f, 1.0f};
  }


  Window::~Window() {
    ShutDown();
  }


  bool Window::Init() {
    if (m_title == nullptr) {
      Logger::Info("Init of empty Window");
    }
    else {
      std::string title = m_title;
      Logger::Info(title);
      Logger::Info(std::to_string(m_width));
      Logger::Info(std::to_string(m_height));
    }

    m_window = glfwCreateWindow(m_width, m_height, m_title, nullptr, nullptr);

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
    return true;
  }

  void Window::Update() {
    glfwMakeContextCurrent(m_window);
    glClearColor(m_backgroundColor[0], m_backgroundColor[1], m_backgroundColor[2], m_backgroundColor[3]);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwPollEvents();
    glfwSwapBuffers(m_window);
  }


  void Window::SetAsCurrent() {
    glfwMakeContextCurrent(m_window);
  }


  void Window::ShutDown() {
    glfwDestroyWindow(m_window);
    Logger::Info("Destroyed window");
  }


  void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    Window* app = static_cast<Window*>(glfwGetWindowUserPointer(window));

    if (action == GLFW_RELEASE)
      app->m_eventManager->TriggerEvent(KeyReleaseEvent(key));
    else
      app->m_eventManager->TriggerEvent(KeyPressEvent(key, action == GLFW_REPEAT));
  }


  void Window::mouse_button_callback(GLFWwindow* window, int button, int action, int mode) {
    Window* app = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (action == GLFW_RELEASE)
      app->m_eventManager->TriggerEvent(MouseReleaseEvent(button));
    else
      app->m_eventManager->TriggerEvent(MousePressEvent(button, action == GLFW_REPEAT));
  }


  void Window::cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    Window*app = static_cast<Window*>(glfwGetWindowUserPointer(window));
    app->m_eventManager->TriggerEvent(MousePositionEvent(xpos, ypos));
  }


  void Window::cursor_enter_callback(GLFWwindow* window, int entered) {
    Window* app = static_cast<Window*>(glfwGetWindowUserPointer(window));
    app->m_eventManager->TriggerEvent(MouseEnterEvent(entered == 1, *app));
  }


  void Window::window_should_close_callback(GLFWwindow* window) {
    Window* app = static_cast<Window*>(glfwGetWindowUserPointer(window));
    glfwSetWindowShouldClose(window, GLFW_TRUE);
    app->m_windowShouldClose = true;
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


  void Window::ChangeBackgroundColor(const float& r, const float& b, const float& g, const float& a) {
    m_backgroundColor = {r, b, g, a};
  }


  void Window::ChangeBackgroundColor(const std::array<float, 4>& backgroundColor) {
    m_backgroundColor = backgroundColor;
  }


  Window* Window::GetWindow() {
    return this;
  }


  Window::Window(Window&& other) noexcept : m_width(other.m_width), m_height(other.m_height), m_title(other.m_title),
    m_windowShouldClose(other.m_windowShouldClose), m_window(other.m_window), m_eventManager(other.m_eventManager) {

    m_backgroundColor = std::move(other.m_backgroundColor);

    other.m_width = 0;
    other.m_height = 0;
    other.m_title = nullptr;
    other.m_windowShouldClose = false;
    other.m_window = nullptr;
    other.m_eventManager = nullptr;
    other.m_backgroundColor = {};

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
    m_backgroundColor = std::move(other.m_backgroundColor);

    other.m_width = 0;
    other.m_height = 0;
    other.m_title = nullptr;
    other.m_windowShouldClose = false;
    other.m_window = nullptr;
    other.m_eventManager = nullptr;
    other.m_backgroundColor = {};

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