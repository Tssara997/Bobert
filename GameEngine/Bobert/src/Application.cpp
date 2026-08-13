#include "include/Application.h"

namespace Bobert {
  Application::Application() {
    log.Init();
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

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        log.Error("Failed to initialize GLAD");
        glfwDestroyWindow(window);
        log.Info("Detroyed window");
        glfwTerminate();
        log.Info("Terminated GLFW");
        log.Info("Engine is closing");
        return;
    }

    log.Info("Initialization GLAD succsefull")

    glfwSetKeyCallback(window, key_callback);

    while (!glfwWindowShouldClose(window) &&  glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS) {
        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    log.Info("Destroyed window");
    glfwTerminate();
    log.Info("Terminated GLFW");

    log.Info("Engine is closing");
  }

  void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
      std::cout << "PRESSED Q" << std::endl;
    }
  }
}

