#pragma once
#include "Core.h"
#include "Logger.h"
#include "WindowBehaviour.h"
#include "Event/EventManager.h"
#include "Event/KeyEvent.h"
#include "Event/MouseEvent.h"

namespace Bobert {
  class Bobert_API Application {
    public:
    
      Application();
      virtual ~Application();

      template <typename B>
      B* AddWindowBehaviour() {
        auto behaviour = std::make_unique<B>();
        B* raw_ptr = behaviour.get();
        windowBehaviours.push_back(std::move(behaviour));
        return raw_ptr;
      }

      void Run();
    
    protected:
      std::vector<std::unique_ptr<WindowBehaviour>> windowBehaviours;
      EventManager eventManager;
      
    private:
      static constexpr bool defWindowShouldClose = false;
      static bool windowShouldClose;
      std::array<float, 4> backgroundColor;

      void InitEventSubscriptions();
      void Update();
      void OnKeyPress(const KeyPressEvent& e);
      static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods); // TEMP
      static void mouse_button_callback(GLFWwindow* window, int button, int action, int mode); // TEMP
      // static void window_should_close_callback(); // TEMP

      void ShutDown(GLFWwindow* window);
  };

  // To be defined in CLIENT
  Application* CreateApplication();
};