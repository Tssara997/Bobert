#pragma once

#include "WindowScene.h"

namespace Bobert {
  class Bobert_API Application {
    public:
    
      Application();
      virtual ~Application();

      virtual void Start() {};

      WindowScene* CreateNewWindowScene(int width, int height, std::string title);

      void Run();
    
    private:
      std::vector<std::unique_ptr<WindowScene>> m_windowScenes;

      void Update();
      void ShutDown();

      const bool AppShouldClose() const;
  };
  Application* CreateApplication();
};