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

      void TempDrawing();

      void SetBackgroundColor(std::array<float, 4> backgroundColor);
      void SetVertices(std::vector<float> vertices);

    private:
      void SetBuffers();

      inline static const std::array<float, 4> defBackgroundColor = {0.1f, 0.1f, 0.15f, 1.0f};
      std::array<float, 4> m_backgroundColor;
      bool m_initalized = false;

      std::vector<float> m_vertices;
      // unsigned int m_verticesSize;
      unsigned int m_VBO;
      unsigned int m_VAO;
      unsigned int m_vertexShader;
      unsigned int m_fragmentShader;
      int m_shaderProgram;

      const char* m_vertexShaderSource = "#version 330 core\n"
      "layout (location = 0) in vec3 aPos;\n"
      "void main()\n"
      "{\n"
      "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
      "}\0";

      const char* m_fragmentShaderSource = "#version 330 core\n"
      "out vec4 FragColor;\n"
      "void main()\n"
      "{\n"
         " FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
      "}\0";
  };

};