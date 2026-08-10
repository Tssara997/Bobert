#pragma once

#if defined(BB_PLATFORM_WINDOWS) || defined(BB_PLATFORM_LINUX)

extern Bobert::Application* Bobert::CreateApplication();

int main(int argc, char** argv) {
    auto app = Bobert::CreateApplication();
    app->Run();
    delete app;
    return 0;
}

#endif