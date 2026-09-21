#pragma once

#include "Logger.h"

namespace Bobert {

  class Render {
    public:
      Render();
      ~Render();

      bool Init();
      void ShutDown();

      void BeginFrame();
      void EndFrame();

      void SetBackgroundColor(const float& r, const float& g, const float& b, const float& a);

    private:
      inline static const std::array<float, 4> defBackgroundColor = {0.1f, 0.1f, 0.15f, 1.0f};
      std::array<float, 4> m_backgroundColor;
      bool m_initalized = false;
  };

};