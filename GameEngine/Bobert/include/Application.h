#pragma once
#include "Core.h"
#include "Logger.h"

namespace Bobert {
  class Bobert_API Application {
    private:
      Logger log;

      static void key_callback(GLFWwindow*, int key, int scancode, int action, int mods);
    public:
    
      Application();
      virtual ~Application();

      void Run();
  };

  // To be defined in CLIENT
  Application* CreateApplication();
};