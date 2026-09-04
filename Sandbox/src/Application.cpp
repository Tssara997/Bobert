#include <Bobert.h>
#include <iostream>

class WindowColor : public Bobert::WindowBehaviour {
    public:
    void OnKeyPress(const Bobert::KeyPressEvent& e) override {
        if (e.GetKey() == 71) {
            ChangeBackgroundColor(0.0f, 0.5f, 0.0f, 1.0f);
        }
    }
};

class Window : public Bobert::WindowBehaviour {
    public:
        void OnKeyRelease(const Bobert::KeyReleaseEvent& e) override {
            if (e.GetKey() == 71) {
                ChangeBackgroundColor(defBackgroundColor[0], defBackgroundColor[1], defBackgroundColor[2], defBackgroundColor[3]);
            }
        }
};

class SandBoxApp : public Bobert::Application {
public:
    SandBoxApp() {
        Bobert::Window& mainWindow = GetWindow();
        AddBehaviour<WindowColor>()->SetWindow(&mainWindow);
        AddBehaviour<Window>()->SetWindow(&mainWindow);

    }
    ~SandBoxApp() {}

private:

};

Bobert::Application* Bobert::CreateApplication() {
    return new SandBoxApp();
}