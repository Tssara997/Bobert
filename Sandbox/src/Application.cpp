#include <Bobert.h>
#include <iostream>

class Window : public Bobert::WindowBehaviour {
    public:
    void OnKeyInput(const Bobert::KeyEvent& e) override {
        std::cout << e.key << std::endl;
        if (e.key == 71) {
            ChangeBackgroundColor(0.0f, 0.5f, 0.0f, 1.0f);
        }
        if (e.key == 72) {
            ChangeBackgroundColor(.1f, 0.1f, 0.15f, 1.0f);
        }
    }

    void OnMouseInput(const Bobert::MouseEvent& e) override {
        std::cout << e.button << std::endl;
    }
};

class SandBoxApp : public Bobert::Application {
public:
    SandBoxApp() {
        SetWindowBehaviour(new Window());
    } 
    ~SandBoxApp() {}

private:
    Window* window;

};

Bobert::Application* Bobert::CreateApplication() {
    return new SandBoxApp();
}