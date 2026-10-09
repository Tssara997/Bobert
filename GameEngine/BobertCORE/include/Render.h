#pragma once

#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Bobert {

  struct Bobert_API Asset {
    std::vector<float> vertices;
    unsigned int VAO;
    glm::vec3 pos();
  };


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
      void AddModel(const Asset& model);
      void SetModelBuffers(Asset model);

    private:
      void SetBuffers();

      inline static const std::array<float, 4> defBackgroundColor = {0.1f, 0.1f, 0.15f, 1.0f};
      std::array<float, 4> m_backgroundColor;
      bool m_initalized = false;

      std::vector<float> m_vertices;
      std::vector<Asset> m_models;
      unsigned int m_VBO;
      unsigned int m_VAO;
      std::unique_ptr<Shader> m_shader;

      std::filesystem::path m_vShaderPath;
      std::filesystem::path m_fShaderPath;
      
  };
};