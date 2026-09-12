#include "include/Application.h"

namespace Bobert {

  Application::Application() : m_eventManager{}, m_currentWindow(800, 600, "WHSAAAT", &m_eventManager) {
    Logger::Init();
    InitEventSubscriptions();
  }


  void Application::InitEventSubscriptions() {
    Subscribe<KeyPressEvent>(&WindowBehaviour::OnKeyPress);
    Subscribe<KeyReleaseEvent>(&WindowBehaviour::OnKeyRelease);
    Subscribe<MousePressEvent>(&WindowBehaviour::OnMousePress);
    Subscribe<MouseReleaseEvent>(&WindowBehaviour::OnMouseRelease);
    Subscribe<MousePositionEvent>(&WindowBehaviour::OnMousePosition);
    Subscribe<MouseEnterEvent>(&WindowBehaviour::OnMouseEnter);
  }


  template <typename EventType>
  void Application::Subscribe(void (WindowBehaviour::*memberFunc)(const EventType&)) {
    m_eventManager.Subscribe<EventType>(EventType::GetStaticType(), [this, memberFunc](const EventType& e) {
      for (auto& winBeh : m_behaviours)
        if (winBeh->GetWindow() && &e.GetWindow() == winBeh->GetWindow())
          (winBeh.get()->*memberFunc)(e);
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

    m_windows.front()->SetAsCurrent();

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
      if (m_windows[i - 1]->WindowShouldClose()) {
        m_windows.erase(m_windows.begin() + (i - 1));
      }
    }

    GLFWwindow* active_window = glfwGetCurrentContext();
    for (auto& window : m_windows) {
      window->Update();
    }

  }


  void Application::ShutDown() {
    for (auto& window : m_windows) {
      window->ShutDown();
    }

    Logger::Info("Engine is closing");
    glfwTerminate();
    Logger::Info("Terminated GLFW");
    Logger::Shutdown();
  }


  Window* Application::GetWindow() {
    return m_windows.front().get();
  }


  Window* Application::CreateNewWindow(int width, int height, const char* title) {
    std::unique_ptr<Window> window = std::make_unique<Window>(width, height, title, &m_eventManager);
      if (!window->Init()) {
        glfwTerminate();
        Logger::Info("Terminated GLFW");
        return nullptr;
      }
    m_windows.push_back(std::move(window));
    AddBehaviour<DefaultWindowBehaviour>()->SetWindow(*m_windows.back().get());

    return m_windows.back().get();
  }


  const bool Application::AppShouldClose() const {
    for (const auto& window : m_windows)
      if (!window->WindowShouldClose())
        return false;

    return true;
  }
};

