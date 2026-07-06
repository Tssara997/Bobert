#pragma once

#ifdef BB_PLATFORM_WINDOWS

extern Bobert::Application* Bobert::CreateApplication();

int main(int argc, char** argv) {
    auto app = Bobert::CreateApplication();
    app->Run();
    delete app;
}

#endif