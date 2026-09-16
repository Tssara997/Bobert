#pragma once

#include "Event/EventManager.h"
#include "Behaviours/DefaultWindowBehaviour.h"

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

      template <typename EventType>
      void Subscribe(void (Behaviour::*memberFunc)(const EventType&));

      Window* GetWindow();
      Window* CreateNewWindow(int width, int height, const char* title);

      void Run();
    
    private:
      EventManager m_eventManager;
      std::vector<std::unique_ptr<Window>> m_windows;
      std::vector<std::unique_ptr<Behaviour>> m_behaviours;

      void InitEventSubscriptions();
      void Update();
      void ShutDown();

      const bool AppShouldClose() const;
  };
  Application* CreateApplication();
};