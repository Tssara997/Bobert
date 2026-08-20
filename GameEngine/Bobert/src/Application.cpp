#include "include/Application.h"

// std::array<float, 4> Bobert::Application::backgroundColor = {0.1f, 0.1f, 0.15f, 1.0f};
bool Bobert::Application::windowShouldClose = Bobert::Application::defWindowShouldClose;

namespace Bobert {
  Application::Application() : eventManager{} {
    log.Init();
    windowBehaviour = new WindowBehaviour();
    Subscriptions();
  }

  void Application::Subscriptions() {
    eventManager.Subscribe<KeyEvent>(KeyEvent::GetStaticType(), [this](const KeyEvent& e) {
      windowBehaviour->OnKeyInput(e); 
    });
    eventManager.Subscribe<MouseEvent>(MouseEvent::GetStaticType(), [this](const MouseEvent& e) {
      windowBehaviour->OnMouseInput(e);
    });
  }

  void Application::SetWindowBehaviour(WindowBehaviour* newBehaviour) {
    delete windowBehaviour;
    windowBehaviour = newBehaviour;
  }

  Application::~Application() {
    // Destruktor klasy Application
    delete windowBehaviour;
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
        glClearColor(windowBehaviour->backgroundColor[0], windowBehaviour->backgroundColor[1], windowBehaviour->backgroundColor[2], windowBehaviour->backgroundColor[3]);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    ShutDown(window);
    log.Info("Engine is closing");
  }

  void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
      windowShouldClose = true;
    }
    if (action != GLFW_PRESS)
      return;
    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    app->eventManager.TriggerEvent(KeyEvent(key));
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
}

