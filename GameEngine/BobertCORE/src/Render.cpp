#include "Render.h"

namespace Bobert {

  Render::Render() : m_backgroundColor(defBackgroundColor) {}


  Render::~Render() {}


  bool Render::Init() {
    if (m_initalized)
      return true;

    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
        Logger::Error("Failed to initialize GLAD");
        Logger::Info("Engine is closing");
        return false;
    }
    Logger::Info("Initialization GLAD succseful");

    m_initalized = true;
    // return true;

    glGenBuffers(1, &m_VBO);
    glGenVertexArrays(1, &m_VAO);

    // shaders
    m_vShaderPath = Logger::m_working_directory; 
    m_vShaderPath += std::filesystem::path("/build/bin/Debug/shaders/vertexShader.glsl"); //TEMP
    m_fShaderPath = Logger::m_working_directory;
    m_fShaderPath += std::filesystem::path("/build/bin/Debug/shaders/fragmentShader.glsl"); //TEMP
    m_shader = std::make_unique<Shader>(m_vShaderPath.string().c_str(), m_fShaderPath.string().c_str());
    return true;
  }


  void Render::BeginFrame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }


  void Render::TempDrawing() {
    if (!m_shader)
      return;
    m_shader->use();
    // ourShader.setFloat("someUniform", 1.0f);
    glBindVertexArray(m_VAO);
    for (size_t i{}; i < m_models.size(); ++i) {
      // private VAO bound to the asset
      glBindVertexArray(m_models.at(i).VAO);
      glDrawArraysInstanced(GL_TRIANGLES, 0, 3, m_models.size());
    }
    // glDrawArrays(GL_TRIANGLES, 0, m_vertices.size() / 6);
  }


  void Render::EndFrame() {
    glClearColor(m_backgroundColor[0], m_backgroundColor[1], m_backgroundColor[2], m_backgroundColor[3]);
  }


  void Render::ShutDown() {

  }


  void Render::SetBackgroundColor(std::array<float, 4> backgroundColor) noexcept {
    if (backgroundColor.empty() || m_backgroundColor == backgroundColor)
      return;
    m_backgroundColor = backgroundColor;
  }


  void Render::SetVertices(const std::vector<float>& vertices) noexcept{
    if (m_vertices == vertices)
      return;
    m_vertices = vertices;

    SetBuffers();
  }


  void Render::AddModel(const Asset& model) {
    m_models.push_back(model);
    SetModelBuffers(m_models.back());
  }


  void Render::SetModelBuffers(Asset model) {
    glGenVertexArrays(model.VAO, &model.VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribDivisor(2, 1);
  }


  void Render::SetBuffers() {
    glBindVertexArray(m_VAO); // Temp

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float), m_vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // glVertexAttribDivisor(2, 1);
    // glVertexAttribDivisor(1, 1);
  }
};