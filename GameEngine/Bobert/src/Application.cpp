#include "include/Application.h"

namespace Bobert {

  Application::Application() : m_eventManager{}, m_currentWindow(800, 600, "WHSAAAT", &m_eventManager) {
    Logger::Init();
    InitEventSubscriptions();
  }


  void Application::InitEventSubscriptions() {
    m_eventManager.Subscribe<KeyPressEvent>(KeyPressEvent::GetStaticType(), [this](const KeyPressEvent& e) {
      for (auto& winBeh : m_behaviours)
        winBeh->OnKeyPress(e);
    });
    m_eventManager.Subscribe<KeyReleaseEvent>(KeyReleaseEvent::GetStaticType(), [this](const KeyReleaseEvent& e) {
      for (auto& winBeh : m_behaviours)
        winBeh->OnKeyRelease(e);
    });
    m_eventManager.Subscribe<MousePressEvent>(MousePressEvent::GetStaticType(), [this](const MousePressEvent& e) {
      for (auto& winBeh : m_behaviours)
        winBeh->OnMousePress(e);
    });
    m_eventManager.Subscribe<MouseReleaseEvent>(MouseReleaseEvent::GetStaticType(), [this](const MouseReleaseEvent& e) {
      for (auto& winBeh : m_behaviours)
        winBeh->OnMouseRelease(e);
    });
    m_eventManager.Subscribe<MousePositionEvent>(MousePositionEvent::GetStaticType(), [this](const MousePositionEvent& e) {
      for (auto& winBeh : m_behaviours)
        winBeh->OnMousePosition(e);
    });
    m_eventManager.Subscribe<MouseEnterEvent>(MouseEnterEvent::GetStaticType(), [this](const MouseEnterEvent& e) {
      for (auto& winBeh : m_behaviours)
        winBeh->OnMouseEnter(e);
      OnMouseEnter(e);
    });
  }


  Application::~Application() {
    // Destruktor klasy Application
  }


  void Application::Run() {

    if (!glfwInit()) {
        Logger::Error("Failed to initialize GLFW");
        Logger::Info("Engine is closing");
        return;
    }

    Logger::Info("Initialization GLFW succseful");

    CreateNewWindow(800, 600, "Main Window");
    Start();

    m_windows.front().SetAsCurrent();

    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
        Logger::Error("Failed to initialize GLAD");
        Logger::Info("Engine is closing");
        return;
    }

    Logger::Info("Initialization GLAD succseful");

    while(!AppShouldClose()) {
      Update();
    }

    ShutDown();
  }


  void Application::Update() {
    for (size_t i{m_windows.size()}; i > 0; --i) {
      if (m_windows[i - 1].WindowShouldClose()) {
        m_windows.erase(m_windows.begin() + (i - 1));
      }
    }

    GLFWwindow* active_window = glfwGetCurrentContext();
    for (auto& window : m_windows) {
      window.Update();
    }

  }


  void Application::ShutDown() {
    for (Window& window : m_windows) {
      window.ShutDown();
    }

    Logger::Info("Engine is closing");
    glfwTerminate();
    Logger::Info("Terminated GLFW");
    Logger::Shutdown();
  }


  Window* Application::GetWindow() {
    return &m_windows.front();
  }


  Window* Application::CreateNewWindow(int width, int height, const char* title) {
    Window window(width, height, title, &m_eventManager);
      if (!window.Init()) {
        glfwTerminate();
        Logger::Info("Terminated GLFW");
        return nullptr;
      }
    m_windows.push_back(std::move(window));
    return &m_windows.back();
  }


  void Application::OnMouseEnter(const MouseEnterEvent& e) {

  }


  const bool Application::AppShouldClose() const {
    for (const auto& window : m_windows)
      if (!window.WindowShouldClose())
        return false;

    return true;
  }
};

