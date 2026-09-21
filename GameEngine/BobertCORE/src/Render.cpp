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
    return true;
  }


  void Render::BeginFrame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }


  void Render::EndFrame() {
    glClearColor(m_backgroundColor[0], m_backgroundColor[1], m_backgroundColor[2], m_backgroundColor[3]);
  }


  void Render::ShutDown() {

  }


  void Render::SetBackgroundColor(std::array<float, 4> backgroundColor) {
    m_backgroundColor = backgroundColor;
  }
};