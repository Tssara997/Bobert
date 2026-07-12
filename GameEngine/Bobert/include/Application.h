#pragma once
#include "Core.h"
#include "Logger.h"

namespace Bobert {
  class Bobert_API Application {
    private:
      Logger log;
    public:
    
      Application();
      virtual ~Application();

      void Run();
  };

  // To be defined in CLIENT
  Application* CreateApplication();
};