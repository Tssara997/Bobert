#include <Bobert.h>
#include <iostream>

class Window : public Bobert::RenderBehaviour {
  public:
    void OnKeyPress(const Bobert::KeyPressEvent& e) override {
      if (e.GetKey() == 67) {
        SetVertices(empty);
        return;
      }
      SetVertices(square);
    }

    void OnKeyRelease(const Bobert::KeyReleaseEvent& e) override {
      if (e.GetKey() != 67)
        SetVertices(triangle);
    }

    void OnMousePress(const Bobert::MousePressEvent& e) override {
      SetBackgroundColor(0.0f, 0.87f, 0.04f, 1.0f);
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

  std::vector<float> empty = {};
};


class WindowColor : public Bobert::RenderBehaviour {
  public:
    void OnMouseRelease(const Bobert::MouseReleaseEvent& e) override {
      SetBackgroundColor(defBackgroundColor);
    }
};

class ToolsApp : public Bobert::Application {
  public:
    ToolsApp() {}

    void Start() override {
      Bobert::WindowScene* main = CreateNewWindowScene(800, 600, "MAIN");
      main->AddBehaviour<Window>();
      main->AddBehaviour<WindowColor>();
    }

    ~ToolsApp() {}
};

Bobert::Application* Bobert::CreateApplication() {
  return new ToolsApp();
}