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

    while(true);

    log.Info("Engine is closing");
  }
}