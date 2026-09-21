#include <Bobert.h>
#include <iostream>

class Window : public Bobert::WindowBehaviour {
  public:
    void OnKeyPress(const Bobert::KeyPressEvent& e) override {
      std::cout << e.GetKey() << std::endl;
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