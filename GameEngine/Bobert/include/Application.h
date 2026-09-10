#pragma once
#include "Core.h"
#include "pch.h"
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

      virtual void Start() {};

      template <typename B>
      B* AddBehaviour() {
        auto behaviour = std::make_unique<B>();
        B* raw_ptr = behaviour.get();
        m_behaviours.push_back(std::move(behaviour));
        return raw_ptr;
      }

      Window* GetWindow();
      Window* CreateNewWindow(int width, int height, const char* title);

      void Run();
    
    private:
      EventManager m_eventManager;
      Window m_currentWindow;
      std::vector<Window> m_windows;
      std::vector<std::unique_ptr<WindowBehaviour>> m_behaviours;

      void InitEventSubscriptions();
      void Update();
      void ShutDown();

      void OnMouseEnter(const MouseEnterEvent& e);

      const bool AppShouldClose() const;
  };
  Application* CreateApplication();
};