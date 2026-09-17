#include "include/Application.h"

namespace Bobert {

  Application::Application() {
    Logger::Init();
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

    Start();

    if (m_windowScenes.empty()) {
      Logger::Error("No Window Scene was found, the Engine is going to close");
      ShutDown();
    }

    m_windowScenes.front()->SetAsCurrent();

    // TODO: Docelowo w Renderer
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
    for (size_t i{m_windowScenes.size()}; i > 0; --i) {
      if (m_windowScenes[i - 1]->ShouldClose())
        m_windowScenes.erase(m_windowScenes.begin() + i - 1);
    }

    for (auto& windowScene : m_windowScenes) {
      windowScene->Update();
    }

  }


  void Application::ShutDown() {
    for (auto& windowScene : m_windowScenes) {
      windowScene->ShutDown();
    }

    Logger::Info("Engine is closing");
    glfwTerminate();
    Logger::Info("Terminated GLFW");
    Logger::Shutdown();
  }


  WindowScene* Application::CreateNewWindowScene(int width, int height, std::string title) {
    std::unique_ptr<WindowScene> windowScene = std::make_unique<WindowScene>();
      if (!windowScene->CreateWindow(width, height, title)) {
        glfwTerminate();
        Logger::Info("Terminated GLFW");
        return nullptr;
      }
    m_windowScenes.push_back(std::move(windowScene));

    return m_windowScenes.back().get();
  }


  const bool Application::AppShouldClose() const {
    return !m_windowScenes.size();
  }
};

