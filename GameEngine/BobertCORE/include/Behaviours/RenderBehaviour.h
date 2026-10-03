#pragma once

#include "Behaviour.h"
#include "Render.h"

namespace Bobert {

  class Bobert_API RenderBehaviour : public Behaviour {
    public:
      RenderBehaviour() : m_backgroundColor(defBackgroundColor) {}

      void SetBackgroundColor(const float& r, const float& g, const float& b, const float& a) {
        m_backgroundColor = {r, g, b, a};
      }

      void Render(Render* render) {
        if (!m_handeled) {
          render->SetVertices(m_vertices);
        }
        // render->SetBackgroundColor(m_backgroundColor);
      }

      void SetVertices(std::vector<float> vertices) {
        if (m_vertices == vertices) return;
        m_vertices = vertices;
        m_handeled = false;
      }

      const std::array<float, 4> defBackgroundColor = {0.1f, 0.1f, 0.15f, 1.0f};
    private:
      std::vector<float> m_vertices{};
      std::array<float, 4> m_backgroundColor;
      bool m_handeled = true;
  };

};