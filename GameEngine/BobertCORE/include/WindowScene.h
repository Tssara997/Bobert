#pragma once

#include "Event/EventManager.h"
#include "Behaviours/DefaultWindowBehaviour.h"
#include "Behaviours/RenderBehaviour.h"
#include "Event/EventManager.h"
#include "Window.h"

namespace Bobert {
  class Bobert_API WindowScene {
    public:
      WindowScene();
      ~WindowScene();

      void InitEventSubscriptions();

      bool CreateWindow(int width, int height, std::string title);
      void ShutDown();

      void SetAsCurrent();
      void Update();
      void PollEvents();
      void SwapBuffers();

      void Render(Render* render);

      bool ShouldClose();

      template <typename B>
      void AddBehaviour() {
        auto behaviour = std::make_unique<B>();
        if constexpr (std::is_base_of_v<WindowBehaviour, B>) {
          behaviour->SetWindow(*m_window.get());
        }
        m_behaviours.push_back(std::move(behaviour));
      }

      template <typename EventType>
      void Subscribe(void (Behaviour::*memberFunc)(const EventType&));

    private:
      std::vector<std::unique_ptr<Behaviour>> m_behaviours;
      std::unique_ptr<Window> m_window;
      EventManager m_eventManager;
  };
};