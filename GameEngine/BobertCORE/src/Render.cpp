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

    // shaderss
    m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(m_vertexShader, 1, &m_vertexShaderSource, NULL);
    glCompileShader(m_vertexShader);

    int  success;
    char* infoLog;
    glGetShaderiv(m_vertexShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(m_vertexShader, 512, NULL, infoLog);
        std::string msg = "Shader vertex error ";
        msg += infoLog;
        Logger::Error(msg);
        return false;
    } else {
      Logger::Info("Intizalization of vertex shader");
    }

    m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(m_fragmentShader, 1, &m_fragmentShaderSource, NULL);
    glCompileShader(m_fragmentShader);

    glGetShaderiv(m_fragmentShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(m_fragmentShader, 512, NULL, infoLog);
        std::string msg = "Shader fragment error ";
        msg += infoLog;
        Logger::Error(msg);
        return false;
    } else {
      Logger::Info("Intizalization of fradment shader");
    }

    m_shaderProgram = glCreateProgram();
    glAttachShader(m_shaderProgram, m_vertexShader);
    glAttachShader(m_shaderProgram, m_fragmentShader);
    glLinkProgram(m_shaderProgram);

    glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(m_shaderProgram, 512, NULL, infoLog);
        std::string msg = "Shader program failed ";
        msg += infoLog;
        Logger::Error(msg);
        return false;
    } else {
      Logger::Info("Intizalization of shader program");
    }

    glUseProgram(m_shaderProgram);

    glDeleteShader(m_vertexShader);
    glDeleteShader(m_fragmentShader);

    return true;
  }


  void Render::BeginFrame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }


  void Render::TempDrawing() {
    glUseProgram(m_shaderProgram);
    glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, m_vertices.size() / 3);
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


  void Render::SetBuffers() {
    float vertices[m_vertices.size()] {};

    for (size_t i{}; i < m_vertices.size(); ++i) {
      vertices[i] = m_vertices.at(i);
    }

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
  }
};