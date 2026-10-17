#pragma once

#include "Behaviour.h"
#include "Render.h"

namespace Bobert {

  class Bobert_API RenderBehaviour : public Behaviour {
    public:
      RenderBehaviour() {}

      void SetBackgroundColor(const float& r, const float& g, const float& b, const float& a) {
        m_tasks.push([r, g, b, a](Render* render) {
          render->SetBackgroundColor({r, g, b, a});
        });
      }

      void SetBackgroundColor(const std::array<float, 4> color) {
        m_tasks.push([color](Render* render) {
          render->SetBackgroundColor(color);
        });
      }

      void GiveToRender(Render* render) {
        if (!render)
          return;

        while(!m_tasks.empty()) {
          auto& task = m_tasks.front();
          task(render);
          m_tasks.pop();
        }
      }

      void SetVertices(const std::vector<float>& vertices) {
        m_tasks.push([vertices](Render* render) {
          render->SetVertices(vertices);
        });
      }


      void AddModel(const Asset& model) {
        m_tasks.push([model](Render* render) {
          render->AddModel(model);
        });
      }

      const std::array<float, 4> defBackgroundColor = {0.1f, 0.1f, 0.15f, 1.0f};
    private:
      std::queue<std::function<void(Render*)>> m_tasks;
  };

};