/**
 * @file EntryPoint.h
 * @brief Main entry point for applications built with the Bobert Engine.
 */

#pragma once

#if defined(BB_PLATFORM_WINDOWS) || defined(BB_PLATFORM_LINUX)

/// @brief Factory function to be defined by the client application to create its custom Application instance.
/// @return Pointer to the created Bobert::Application.
extern Bobert::Application* Bobert::CreateApplication();

/// @brief Main function executing the lifecycle of the engine application.
int main(int argc, char** argv) {
    auto app = Bobert::CreateApplication();
    app->Run();
    delete app;
    return 0;
}

#endif