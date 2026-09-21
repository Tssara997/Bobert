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
    glClearColor(m_backgroundColor[0], m_backgroundColor[1], m_backgroundColor[2], m_backgroundColor[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }


  void Render::EndFrame() {

  }


  void Render::ShutDown() {

  }


  void Render::SetBackgroundColor(const float& r, const float& g, const float& b, const float& a) {
    m_backgroundColor = {r, g, b, a};
  }
};