#pragma once
#include "Core.h"
#include "Logger.h"
#include "WindowBehaviour.h"
#include "Event/EventManager.h"
#include "Event/KeyEvent.h"
#include "Event/MouseEvent.h"
#include "Window.h"

namespace Bobert {
  class Bobert_API Application {
    public:
    
      Application();
      virtual ~Application();

      template <typename B>
      B* AddWindowBehaviour() {
        auto behaviour = std::make_unique<B>();
        B* raw_ptr = behaviour.get();
        m_windowBehaviours.push_back(std::move(behaviour));
        return raw_ptr;
      }

      void Run();
    
    protected:
      std::vector<std::unique_ptr<WindowBehaviour>> m_windowBehaviours; // behaviours
      EventManager m_eventManager;
      
    private:
      Window m_window;

      void InitEventSubscriptions();
      void Update();

      void ShutDown();
  };
  Application* CreateApplication();
};