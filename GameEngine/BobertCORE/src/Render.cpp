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

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_instanceVBO);

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
    // glBindVertexArray(m_VAO);
    // glDrawArrays(GL_TRIANGLES, 0, m_vertices.size() / 6);

    glBindVertexArray(m_VAO);

    // Rysujemy wierzchołki geometrii w liczbie podanych instancji
    unsigned int vertexCount = m_vertices.size() / 6; // Każdy wierzchołek ma 6 floatów (pos + color)
    glDrawArraysInstanced(GL_TRIANGLES, 0, vertexCount, static_cast<GLsizei>(m_instancePositions.size()));

    glBindVertexArray(0);
  }


  void Render::EndFrame() {
    glClearColor(m_backgroundColor[0], m_backgroundColor[1], m_backgroundColor[2], m_backgroundColor[3]);
  }


  void Render::ShutDown() {
    if (m_VAO) glDeleteVertexArrays(1, &m_VAO);
    if (m_VBO) glDeleteBuffers(1, &m_VBO);
    if (m_instanceVBO) glDeleteBuffers(1, &m_instanceVBO);
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

    glBindVertexArray(m_VAO); // Temp

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float), m_vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, m_instanceVBO);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(2);

    glVertexAttribDivisor(2, 1);

    glBindVertexArray(0);
  }


  void Render::AddModel(const Asset& model) {
    m_instancePositions.push_back(model.pos);
    SetModelBuffers();
  }


  void Render::SetModelBuffers() {
    glBindBuffer(GL_ARRAY_BUFFER, m_instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, m_instancePositions.size() * sizeof(glm::vec3), m_instancePositions.data(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }


  void Render::SetBuffers() {
    glGenVertexArrays(1, &m_VAO);
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