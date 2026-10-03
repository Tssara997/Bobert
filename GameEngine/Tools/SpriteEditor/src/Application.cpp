#include <Bobert.h>
#include <iostream>

class Window : public Bobert::RenderBehaviour {
  public:
    void OnKeyPress(const Bobert::KeyPressEvent& e) override {
      if (e.GetKey() == 67) {
        SetVertices({});
        return;
      }
      SetVertices(triangle);
    }

    void OnKeyRelease(const Bobert::KeyReleaseEvent& e) override {
      if (e.GetKey() != 67)
        SetVertices(square);
    }

  private:
  std::vector<float> triangle = {
      -0.5f, -0.5f, 0.0f,
      0.5f, -0.5f, 0.0f,
      0.0f,  0.5f, 0.0f
  };

  std::vector<float> square = {
    -0.5f,  -0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f,
    0.5f, 0.5f, 0.0f,
    0.5f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f
  };
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