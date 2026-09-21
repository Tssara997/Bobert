#include "WindowScene.h"

namespace Bobert {

  WindowScene::WindowScene() : m_eventManager() {
    InitEventSubscriptions();
  }


  WindowScene::~WindowScene() {
    ShutDown();
  }


  bool WindowScene::CreateWindow(int width, int height, std::string title) {
    if (m_window)
      return false;
    m_window = std::make_unique<Window>(width, height, title, &m_eventManager);

    if (!m_window->Init()) {
      m_window = nullptr;
      return false;
    }

    AddBehaviour<DefaultWindowBehaviour>();
    return true;
  }


  void WindowScene::Update() {
    m_window->Update();
    if (m_window->WindowShouldClose())
      ShutDown();
  }


  void WindowScene::SetAsCurrent() {
    if (m_window)
    {
      m_window->SetAsCurrent();
    }
  }


  void WindowScene::PollEvents() {
    if (m_window)
    {
      m_window->PollEvents();
    }
  }


  void WindowScene::SwapBuffers() {
    if (m_window) {
      m_window->SwapBuffers();
    }
  }


  void WindowScene::InitEventSubscriptions() {
    Subscribe<KeyPressEvent>(&Behaviour::OnKeyPress);
    Subscribe<KeyReleaseEvent>(&Behaviour::OnKeyRelease);
    Subscribe<MousePressEvent>(&Behaviour::OnMousePress);
    Subscribe<MouseReleaseEvent>(&Behaviour::OnMouseRelease);
    Subscribe<MousePositionEvent>(&Behaviour::OnMousePosition);
    Subscribe<MouseEnterEvent>(&Behaviour::OnMouseEnter);
    Subscribe<WindowCloseEvent>(&Behaviour::OnWindowClose);
    Subscribe<WindowFocusEvent>(&Behaviour::OnWindowFocus);
    Subscribe<WindowResizingEvent>(&Behaviour::OnWindowResize);
  }


  template <typename EventType>
  void WindowScene::Subscribe(void (Behaviour::*memberFunc)(const EventType&)) {
    m_eventManager.Subscribe<EventType>(EventType::GetStaticType(), [this, memberFunc](const EventType& e) {
      for (auto& beh : m_behaviours)
        (beh.get()->*memberFunc)(e);
    });
  }


  // template <typename B>
  // void WindowScene::AddBehaviour() {
  //   auto behaviour = std::make_unique<B>();
  //   m_behaviours.push_back(std::move(behaviour));
  // }



  void WindowScene::ShutDown() {
    if (m_window) {
      m_window->ShutDown();
      m_window = nullptr;
    }

    m_behaviours.clear();

    Logger::Info("WindowScene shut down");
  }


  bool WindowScene::ShouldClose() {
    return m_window == nullptr || m_window->WindowShouldClose();
  }
};