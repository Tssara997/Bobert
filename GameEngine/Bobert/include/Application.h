#pragma once
#include "Core.h"
#include "Logger.h"
#include "WindowBehaviour.h"
#include "EventManager.h"
#include "Event.h"

namespace Bobert {
  class Bobert_API Application {
    public:
    
      Application();
      virtual ~Application();

      void SetWindowBehaviour(WindowBehaviour* newBehaviour);

      void Run();
    
    protected:
      WindowBehaviour* windowBehaviour;
      EventManager eventManager;
      Logger log;
      
    private:
      static constexpr bool defWindowShouldClose = false;
      static bool windowShouldClose;

      static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods); // TEMP
      static void mouse_button_callback(GLFWwindow* window, int button, int action, int mode); // TEMP

      void ShutDown(GLFWwindow* window);
  };

  // To be defined in CLIENT
  Application* CreateApplication();
};