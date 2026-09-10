#include <Bobert.h>
#include <iostream>

class WindowColorGreen : public Bobert::WindowBehaviour {
    public:
    void OnKeyPress(const Bobert::KeyPressEvent& e) override {
        ChangeBackgroundColor(0.0f, 0.5f, 0.0f, 1.0f);
    }

    void OnMousePosition(const Bobert::MousePositionEvent& e) override {

    }

    void OnMouseEnter(const Bobert::MouseEnterEvent& e) override {
        if (e.IsEnter())
            std::cout << "Yey you are back :)" << std::endl;
        else
            std::cout << "Noooo, come back. Pretty please :(" << std::endl;
    }
};

class WindowColorRed : public Bobert::WindowBehaviour {
    public:
    void OnKeyPress(const Bobert::KeyPressEvent& e) override {
        ChangeBackgroundColor(1.0f, 0.5f, 0.0f, 1.0f);
    }
};

class Window : public Bobert::WindowBehaviour {
    public:
        void OnKeyRelease(const Bobert::KeyReleaseEvent& e) override {
            ChangeBackgroundColor(defBackgroundColor[0], defBackgroundColor[1], defBackgroundColor[2], defBackgroundColor[3]);
        }
};

class SandBoxApp : public Bobert::Application {
public:
    SandBoxApp() {
    }

    void Start() override {
        Bobert::Window* mainWindow = GetWindow();
        AddBehaviour<WindowColorGreen>()->SetWindow(*mainWindow);
        AddBehaviour<Window>()->SetWindow(*mainWindow);

        CreateNewWindow(800, 600, "Red window");
        Bobert::Window* secondWindow = GetWindow();
        if (secondWindow){
            AddBehaviour<WindowColorRed>()->SetWindow(*secondWindow);
            AddBehaviour<Window>()->SetWindow(*secondWindow);
        }
    }

    ~SandBoxApp() {}

private:

};

Bobert::Application* Bobert::CreateApplication() {
    return new SandBoxApp();
}