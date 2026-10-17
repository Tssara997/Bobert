#pragma once

#include <pch.h>
#include <nlohmann/json.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Logger.h"


namespace Bobert {

  using json = nlohmann::json

  struct EntityConfig
  {
    std::string id;
    std::string modelPath;
    glm::vec3 position;
  };


  class Bobert_API FileReader {
    public:
      static bool LoadScene(const std::string& filePath, std::vector<EntityConfig>& outEntities) {
        std::ifstream file(filePath);

        if (!file.is_open()) {
          std::string msg = "Cannot open file: " + filePath;
          Logger::Error(msg);
          return false;
        }

        try {
          json data = json::parse(file);

          if (data.contains("scene_name")) {
            std::string sceneName = data["scene_name"];
          }

          if (data.contains("entities") && data["entities"].is_array()) {
            for (const auto& item : data["entities"]) {
              EntityConfig entity;
              entity.id = item.value("id", "unknown");
              entity.modelPath = item.value("model", "");

              if (item.contains("position") && item["position"].is_array()) {
                auto posArray = item["position"];
                entity.position = glm::vec3(posArray[0], posArray[1], posArray[2]);
              }

              outEntities.push_back(entity);
            }
          }
        }

        catch (const json::parse_error& e) {
          std::cerr << "Bledny format JSON w pliku " << filePath << ": " << e.what() << std::endl;
          return false;
        }

        return true;
      }

    private:

  };

};
