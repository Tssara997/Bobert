#include "include/Application.h"

bool Bobert::Application::windowShouldClose = Bobert::Application::defWindowShouldClose;

namespace Bobert {

  Application::Application() : eventManager{} {
    Logger::Init();
    InitEventSubscriptions();
    AddWindowBehaviour<WindowBehaviour>();
    backgroundColor = {0.1f, 0.1f, 0.15f, 1.0f};
  }


  void Application::InitEventSubscriptions() {
    eventManager.Subscribe<KeyPressEvent>(KeyPressEvent::GetStaticType(), [this](const KeyPressEvent& e) {
      for (auto& winBeh : windowBehaviours)
        winBeh->OnKeyPress(e);
      this->OnKeyPress(e);
    });
    eventManager.Subscribe<KeyReleaseEvent>(KeyReleaseEvent::GetStaticType(), [this](const KeyReleaseEvent& e) {
      for (auto& winBeh : windowBehaviours)
        winBeh->OnKeyRelease(e);
    });
    eventManager.Subscribe<MouseEvent>(MouseEvent::GetStaticType(), [this](const MouseEvent& e) {
      for (auto& winBeh : windowBehaviours)
        winBeh->OnMouse(e);
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


    // // Konfiguracja wersji OpenGL (np. Core Profile 3.3)
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Bobert Engine - Test", nullptr, nullptr);
    if (!window) {
        Logger::Error("Failed to create a GLFW window");
        glfwTerminate();
        Logger::Info("Terminated GLFW");
        Logger::Info("Engine is closing");
        return;
    }
    Logger::Info("Created a GLFW window");
    glfwSetWindowUserPointer(window, this);

    glfwMakeContextCurrent(window);

    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
        Logger::Error("Failed to initialize GLAD");
        ShutDown(window);
        Logger::Info("Engine is closing");
        return;
    }

    Logger::Info("Initialization GLAD succseful");

    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    while (!windowShouldClose && !glfwWindowShouldClose(window)) {
        glClearColor(backgroundColor[0], backgroundColor[1], backgroundColor[2], backgroundColor[3]);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwPollEvents();
        glfwSwapBuffers(window);
        Update();
    }

    ShutDown(window);
  }


  void Application::Update() {
    for (auto& windowBeh : windowBehaviours) {
      if (!windowBeh->handled) {
        backgroundColor = windowBeh->backgroundColor;
        windowBeh->handled = true;
      }
    }
  }


  // void Application::window_should_close_callback()


  void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));

    if (action == GLFW_RELEASE)
      app->eventManager.TriggerEvent(KeyReleaseEvent(key));
    else
      app->eventManager.TriggerEvent(KeyPressEvent(key, action == GLFW_REPEAT));
  }


  void Application::mouse_button_callback(GLFWwindow* window, int button, int action, int mode) {
    if (action != GLFW_PRESS) 
      return;
    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    app->eventManager.TriggerEvent(MouseEvent(button));
  }


  void Application::OnKeyPress(const KeyPressEvent& e) {
    if (e.GetKey() == 256)
      windowShouldClose = true;
  }


  void Application::ShutDown(GLFWwindow* window) {
    Logger::Info("Engine is closing");
    glfwDestroyWindow(window);
    Logger::Info("Destroyed window");
    glfwTerminate();
    Logger::Info("Terminated GLFW");
    Logger::Shutdown();
  }
};

