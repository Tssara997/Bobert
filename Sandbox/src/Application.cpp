#include <Bobert.h>
#include <iostream>

class WindowColorGreen : public Bobert::WindowBehaviour {
    public:
    void OnKeyPress(const Bobert::KeyPressEvent& e) override {

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
    // void OnMousePress(const Bobert::MousePressEvent& e) override {
    //     std::cout << "MOUSE" << std::endl;
    //     ChangeBackgroundColor(1.0f, 0.5f, 0.0f, 1.0f);
    // }

    void OnKeyPress(const Bobert::KeyPressEvent& e) override {
    }
};

class WindowColorYellow : public Bobert::WindowBehaviour {
    public:
    void OnMousePress(const Bobert::MousePressEvent& e) override {
        std::cout << "MOUSE" << std::endl;
    }

    void OnKeyPress(const Bobert::KeyPressEvent& e) override {
    }
};

class SandBoxApp : public Bobert::Application {
public:
    SandBoxApp() {
    }

    void Start() override {
        Bobert::WindowScene* main = CreateNewWindowScene(800, 600, "Green window");
        if (main) {
            main->AddBehaviour<WindowColorGreen>();
        }
        std::cout << "Crazy" << std::endl;
        Bobert::WindowScene* second = CreateNewWindowScene(800, 600, "Red window");;
        if (second) {
            std::cout << "YEY" << std::endl;
            second->AddBehaviour<WindowColorRed>();
        }

        Bobert::WindowScene* third = CreateNewWindowScene(800, 600, "Yello window");;
        if (third) {
            third->AddBehaviour<WindowColorYellow>();
        }
    }

    ~SandBoxApp() {}

private:

};

Bobert::Application* Bobert::CreateApplication() {
    return new SandBoxApp();
}