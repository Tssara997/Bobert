#pragma once

#include "Shader.h"

namespace Bobert {

  class Bobert_API Render {
    public:
      Render();
      ~Render();

      bool Init();
      void ShutDown();

      void BeginFrame();
      void EndFrame();

      void TempDrawing();

      void SetBackgroundColor(std::array<float, 4> backgroundColor) noexcept;
      void SetVertices(const std::vector<float>& vertices) noexcept;

    private:
      void SetBuffers();

      inline static const std::array<float, 4> defBackgroundColor = {0.1f, 0.1f, 0.15f, 1.0f};
      std::array<float, 4> m_backgroundColor;
      bool m_initalized = false;

      std::vector<float> m_vertices;
      unsigned int m_VBO;
      unsigned int m_VAO;
      std::unique_ptr<Shader> m_shader;
      
  };

};