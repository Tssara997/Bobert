#include <catch2/catch_all.hpp>
#include "Application.h"

SCENARIO("Creating a new window scene in applcation", "[application][new window scene]") {
  GIVEN("New initilized Application object") {
    Bobert::Application test_application;

    THEN("Creating new window scene should not throw") {
      REQUIRE(test_application.CreateNewWindowScene(400, 400, "Test windowScene"));
    }

    THEN("Creatind new window scene should return pointer to new window scene") {
      auto newWindowScene = test_application.CreateNewWindowScene(400, 400, "Test windowScene");
      REQUIRE(typeid(newWindowScene) == typeid(new Bobert::WindowScene()));
    }
  }
}