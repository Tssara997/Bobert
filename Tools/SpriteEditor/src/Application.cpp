#include <Bobert.h>
#include <iostream>

class Window : public Bobert::WindowBehaviour {
  public:
    void OnKeyPress(const Bobert::KeyPressEvent& e) override {
      ChangeBackgroundColor(0.0f, 0.5f, 0.0f, 1.0f);
    }

    void OnKeyRelease(const Bobert::KeyReleaseEvent& e) override {
      ChangeBackgroundColor(defBackgroundColor[0], defBackgroundColor[1], defBackgroundColor[2], defBackgroundColor[3]);
    }
};

class ToolsApp : public Bobert::Application {
  public:
    ToolsApp() {}

    void Start() override {
      Bobert::Window* mainWindow = GetWindow();
      AddBehaviour<Window>()->SetWindow(*mainWindow);
    }

    ~ToolsApp() {}
};

Bobert::Application* Bobert::CreateApplication() {
  return new ToolsApp();
}