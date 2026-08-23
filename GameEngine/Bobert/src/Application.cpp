#include "include/Application.h"

// std::array<float, 4> Bobert::Application::backgroundColor = {0.1f, 0.1f, 0.15f, 1.0f};
bool Bobert::Application::windowShouldClose = Bobert::Application::defWindowShouldClose;

namespace Bobert {
  Application::Application() : eventManager{} {
    log.Init();
    InitEventSubscriptions();
    AddWindowBehaviour<WindowBehaviour>();
    backgroundColor = {0.1f, 0.1f, 0.15f, 1.0f};
  }

  void Application::InitEventSubscriptions() {
    eventManager.Subscribe<KeyPressEvent>(KeyPressEvent::GetStaticType(), [this](const KeyPressEvent& e) {
      for (auto& winBeh : windowBehaviours)
        winBeh->OnKeyPress(e);
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

    log.Info("Engine is working");
    log.Info("Logger is working");

    if (!glfwInit()) {
        log.Error("Failed to initialize GLFW");
        log.Info("Engine is closing");
        return;
    }

    log.Info("Initialization GLFW succsefull");


    // // Konfiguracja wersji OpenGL (np. Core Profile 3.3)
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Bobert Engine - Test", nullptr, nullptr);
    if (!window) {
        log.Error("Failed to create a GLFW window");
        glfwTerminate();
        log.Info("Terminated GLFW");
        log.Info("Engine is closing");
        return;
    }
    log.Info("Created a GLFW window");
    glfwSetWindowUserPointer(window, this);

    glfwMakeContextCurrent(window);

    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
        log.Error("Failed to initialize GLAD");
        ShutDown(window);
        log.Info("Engine is closing");
        return;
    }

    log.Info("Initialization GLAD succsefull");

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
    log.Info("Engine is closing");
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

  void Application::ShutDown(GLFWwindow* window) {
    glfwDestroyWindow(window);
    log.Info("Destroyed window");
    glfwTerminate();
    log.Info("Terminated GLFW");
  }
};

