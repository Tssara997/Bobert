#include "include/Application.h"

namespace Bobert {

  Application::Application() : m_eventManager{}, m_window{800, 600, &m_eventManager} {
    Logger::Init();
    InitEventSubscriptions();
  }


  void Application::InitEventSubscriptions() {
    m_eventManager.Subscribe<KeyPressEvent>(KeyPressEvent::GetStaticType(), [this](const KeyPressEvent& e) {
      for (auto& winBeh : m_behaviours)
        winBeh->OnKeyPress(e);
      m_window.OnKeyPress(e);
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

    if (!m_window.Init()) {
      glfwTerminate();
      Logger::Info("Terminated GLFW");
      return;
    }

    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
        Logger::Error("Failed to initialize GLAD");
        Logger::Info("Engine is closing");
        return;
    }

    Logger::Info("Initialization GLAD succseful");

    while(!m_window.WindowShouldClose()) {
      m_window.Update();
    }

    ShutDown();
  }


  void Application::Update() {
    return;
  }


  void Application::ShutDown() {
    m_window.ShutDown();
    Logger::Info("Engine is closing");
    glfwTerminate();
    Logger::Info("Terminated GLFW");
    Logger::Shutdown();
  }


  Window& Application::GetWindow() {
    return m_window;
  }
};

