#include <catch2/catch_all.hpp>
#include <Behaviours/DefaultWindowBehaviour.h>

SCENARIO("DefaultWindowBehaviour creation and default state", "[behaviour][default window behaviour][creation]") {
  GIVEN("New DefaultWindowBehaviour object") {
    Bobert::DefaultWindowBehaviour test_defaultWindowBehaviour;

    THEN("It should not have any window attached") {
      REQUIRE(test_defaultWindowBehaviour.GetWindow() == nullptr);
    }

  }
}

SCENARIO("Closing the window connected to the DefaultWindowBehaviour on user input", "[behaviour][default window behaviour][user input]") {
  GIVEN("DefaultWindowBehaviour object") {
    Bobert::DefaultWindowBehaviour test_defaultWindowBehaviour;

    WHEN("Key press event is triggered, with key code assign to enter but there is no window loaded") {
      test_defaultWindowBehaviour.OnKeyPress(Bobert::KeyPressEvent(256, false));
      THEN("Nothing should happen") {
        REQUIRE(test_defaultWindowBehaviour.GetWindow() == nullptr);
      }
    }

    Bobert::EventManager eventManager;
    Bobert::Window window(400, 400, "close", &eventManager);
    test_defaultWindowBehaviour.SetWindow(window);

    REQUIRE(test_defaultWindowBehaviour.GetWindow() == &window);
    REQUIRE(window.WindowShouldClose() == false);

    WHEN("Key press event is triggered, with key code assign to enter") {
      test_defaultWindowBehaviour.OnKeyPress(Bobert::KeyPressEvent(256, false)); // TODO: magic number

      THEN("Window assigned to behaviour should close") {
        REQUIRE(test_defaultWindowBehaviour.GetWindow()->WindowShouldClose() == true);
        REQUIRE(window.WindowShouldClose() == true);
      }

      WHEN("Event is called again") {
        test_defaultWindowBehaviour.OnKeyPress(Bobert::KeyPressEvent(256, true)); // TODO: magic number

        THEN("Nothing should change") {
          REQUIRE(test_defaultWindowBehaviour.GetWindow()->WindowShouldClose() == true);
        }

      }
    }
  }

}

SCENARIO("Key press is triggered but not key code assign to enter", "[behaviour][default window behaviour][user input]") {
  GIVEN("DefaultWindowBehaviour object with loaded window") {
    Bobert::DefaultWindowBehaviour test_defaultWindowBehaviour;
    Bobert::EventManager eventManager;
    Bobert::Window window(400, 400, "close", &eventManager);
    test_defaultWindowBehaviour.SetWindow(window);

    WHEN("Event is called, but key is diffrent then escape") {
      test_defaultWindowBehaviour.OnKeyPress(Bobert::KeyPressEvent(49, false)); // TODO: magic number

      THEN("Nothing should happen") {
        REQUIRE(test_defaultWindowBehaviour.GetWindow()->WindowShouldClose() == false);
      }

    }

  }
}