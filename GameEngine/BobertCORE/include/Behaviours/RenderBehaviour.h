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
        render->SetBackgroundColor(m_backgroundColor);
      }

      const std::array<float, 4> defBackgroundColor = {0.1f, 0.1f, 0.15f, 1.0f};
    private:
      std::array<float, 4> m_backgroundColor;
  };

};