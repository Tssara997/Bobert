#include <Bobert.h>
#include <iostream>

class Window : public Bobert::RenderBehaviour {
  public:
    void OnKeyPress(const Bobert::KeyPressEvent& e) override {
      SetBackgroundColor(0.3f, 0.1f, 0.5f, 1.0f);
    }

    void OnKeyRelease(const Bobert::KeyReleaseEvent& e) override {
      SetBackgroundColor(defBackgroundColor[0], defBackgroundColor[1], defBackgroundColor[2], defBackgroundColor[3]);
    }

    void OnWindowResize(const Bobert::WindowResizingEvent& e) override {
      std::cout << "Resize" << std::endl;
    }
};

class ToolsApp : public Bobert::Application {
  public:
    ToolsApp() {}

    void Start() override {
      Bobert::WindowScene* main = CreateNewWindowScene(800, 600, "MAIN");
      main->AddBehaviour<Window>();
    }

    ~ToolsApp() {}
};

Bobert::Application* Bobert::CreateApplication() {
  return new ToolsApp();
}