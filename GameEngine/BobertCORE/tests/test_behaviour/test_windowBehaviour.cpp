#include <catch2/catch_all.hpp>
#include <Behaviours/WindowBehaviour.h>

SCENARIO("WindowBehaviour creation and default state", "[behaviour][window behaviour][creation]") {
  GIVEN("New WindowBehaviour object") {
    Bobert::WindowBehaviour test_windowBehaviour;

    THEN("It should not have any window attached") {
      REQUIRE(test_windowBehaviour.GetWindow() == nullptr);
    }

  }
}

SCENARIO("Adding a window to WindowBehaviour", "[behaviour][window behaviour][set window]") {
  GIVEN("New WindowBehaviour object") {
    Bobert::WindowBehaviour test_windowBehaviour;

    WHEN("Setting a window") {
      Bobert::EventManager eventManager;
      Bobert::Window window(400, 400, "title", &eventManager);
      test_windowBehaviour.SetWindow(window);

      THEN("WindowBehaviour should hold the exact assigned window instance") {
        REQUIRE(test_windowBehaviour.GetWindow() != nullptr);
        REQUIRE(test_windowBehaviour.GetWindow() == &window);
      }

    }

  }
}