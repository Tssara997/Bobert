#include <Bobert.h>

class SandBoxApp : public Bobert::Application {
public:
    SandBoxApp() {}
    ~SandBoxApp() {}

};

Bobert::Application* Bobert::CreateApplication() {
    return new SandBoxApp();
}