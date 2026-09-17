#include <Bobert.h>
#include <iostream>

class WindowColorGreen : public Bobert::WindowBehaviour {
    public:
    void OnKeyPress(const Bobert::KeyPressEvent& e) override {

        ChangeBackgroundColor(0.0f, 0.5f, 0.0f, 1.0f);
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
        ChangeBackgroundColor(1.0f, 0.0f, 0.0f, 1.0f);
    }
};

class WindowColorYellow : public Bobert::WindowBehaviour {
    public:
    void OnMousePress(const Bobert::MousePressEvent& e) override {
        std::cout << "MOUSE" << std::endl;
        ChangeBackgroundColor(1.0f, 0.5f, 0.0f, 1.0f);
    }

    void OnKeyPress(const Bobert::KeyPressEvent& e) override {
        ChangeBackgroundColor(1.0f, 1.0f, 0.0f, 1.0f);
    }
};

class Window : public Bobert::WindowBehaviour {
    public:
        void OnKeyRelease(const Bobert::KeyReleaseEvent& e) override {
            ChangeBackgroundColor(defBackgroundColor[0], defBackgroundColor[1], defBackgroundColor[2], defBackgroundColor[3]);
        }

        void OnMouseRelease(const Bobert::MouseReleaseEvent& e) override {
           ChangeBackgroundColor(defBackgroundColor[0], defBackgroundColor[1], defBackgroundColor[2], defBackgroundColor[3]);
        }

        void OnWindowClose(const Bobert::WindowCloseEvent& e) override {
            std::cout << "Close" << std::endl;
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
            main->AddBehaviour<Window>();
        }
        std::cout << "Crazy" << std::endl;
        Bobert::WindowScene* second = CreateNewWindowScene(800, 600, "Red window");;
        if (second) {
            std::cout << "YEY" << std::endl;
            second->AddBehaviour<WindowColorRed>();
            second->AddBehaviour<Window>();
        }

        Bobert::WindowScene* third = CreateNewWindowScene(800, 600, "Yello window");;
        if (third) {
            third->AddBehaviour<WindowColorYellow>();
            third->AddBehaviour<Window>();
        }
    }

    ~SandBoxApp() {}

private:

};

Bobert::Application* Bobert::CreateApplication() {
    return new SandBoxApp();
}