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

    // 1. Inicjalizacja GLFW
    if (!glfwInit()) {
        std::cerr << "Nie udalo sie zainicjalizowac GLFW!" << std::endl;
        return;
    }

    // Konfiguracja wersji OpenGL (np. Core Profile 3.3)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 2. Tworzenie okna
    GLFWwindow* window = glfwCreateWindow(800, 600, "Bobert Engine - Test", nullptr, nullptr);
    if (!window) {
        std::cerr << "Nie udalo sie utworzyc okna GLFW!" << std::endl;
        glfwTerminate();
        return;
    }

    // Ustawienie kontekstu OpenGL dla okna
    glfwMakeContextCurrent(window);

    // 3. Inicjalizacja GLAD (musi być po utworzeniu kontekstu GLFW)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Nie udalo sie zainicjalizowac GLAD!" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return;
    }

    std::cout << "Sukces! OpenGL initialized. Wersja: " << glGetString(GL_VERSION) << std::endl;

    // 4. Główna pętla aplikacji
    while (!glfwWindowShouldClose(window)) {
        // Czyszczenie ekranu (np. na ładny ciemny kolor)
        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Obsługa zdarzeń (klawiatura, mysz itp.) i wymiana buforów
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    // 5. Sprzątanie po zamknięciu okna
    glfwDestroyWindow(window);
    glfwTerminate();

    log.Info("Engine is closing");
  }
}