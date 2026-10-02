#include <catch2/catch_all.hpp>
#include "Event/KeyEvent.h"
#include "Event/MouseEvent.h"
#include "Event/WindowEvent.h"

// Event
class TestableEvent : public Bobert::Event {
  Bobert::EventTypeEnum GetEventType() const noexcept {return Bobert::EventTypeEnum(0);}
};

SCENARIO("Event creation and default state", "[events][event][creation]") {
  GIVEN("New Event object") {
    TestableEvent test_event;

    THEN("Attribute m_handled should be false") {
      REQUIRE(test_event.IsHandled() == false);
    }

  }
}

// Key Events
class TestableKeyInputEvent : public Bobert::KeyInputEvent {
  public:
    TestableKeyInputEvent(int key) : Bobert::KeyInputEvent(key) {}
};

SCENARIO("KeyInputEvent creation and default state", "[events][key event][key input event][creation]") {
  GIVEN("New KeyInputEvent object") {
    int key = 30;
    TestableKeyInputEvent test_keyInputEvent(key);

    THEN("Attribute m_key should be equal to key") {
      REQUIRE(test_keyInputEvent.GetKey() == key);
    }

    THEN("EventType should be equal to KeyInput") {
      Bobert::EventTypeEnum type = Bobert::EventTypeEnum::KeyInput;
      REQUIRE(test_keyInputEvent.GetEventType() == type);
      REQUIRE(test_keyInputEvent.GetStaticType() == type);
    }
  }
}

SCENARIO("KeyPressEvent creation and default state", "[events][key event][key press event][creation]") {
  GIVEN("New KeyPressEvent object") {
    int key = 30;
    bool isRepeat = false;
    Bobert::KeyPressEvent test_keyPressEvent(key, isRepeat);

    THEN("Attribute m_key should be equal to key") {
      REQUIRE(test_keyPressEvent.GetKey() == key);
    }

    THEN("Attribute m_isRepeat should be equal to isRepeat") {
      REQUIRE(test_keyPressEvent.IsRepeat() == isRepeat);
    }

    THEN("EventType should be equal to KeyPressInput") {
      Bobert::EventTypeEnum type = Bobert::EventTypeEnum::KeyPressInput;
      REQUIRE(test_keyPressEvent.GetEventType() == type);
      REQUIRE(test_keyPressEvent.GetStaticType() == type);
    }
  }
}

SCENARIO("KeyReleaseEvent creation and default state", "[events][key event][key release event][creation]") {
  GIVEN("New KeyReleaseEvent object") {
    int key = 30;
    Bobert::KeyReleaseEvent test_keyReleaseEvent(key);

    THEN("Attribute m_key should be equal to key") {
      REQUIRE(test_keyReleaseEvent.GetKey() == key);
    }

    THEN("EventType should be equal to KeyReleaseInput") {
      Bobert::EventTypeEnum type = Bobert::EventTypeEnum::KeyReleaseInput;
      REQUIRE(test_keyReleaseEvent.GetEventType() == type);
      REQUIRE(test_keyReleaseEvent.GetStaticType() == type);
    }
  }
}

// Mouse Events
SCENARIO("MousePositionEvent creation and default state", "[events][mouse event][mouse position event][creation]") {
  GIVEN("New MousePositionEvent object") {
    double xpos = 1.2;
    double ypos = 1.3;
    Bobert::MousePositionEvent test_mousePositionEvent(xpos, ypos);

    THEN("Attribute m_xpos should be equal to xpos") {
      REQUIRE(test_mousePositionEvent.GetXpos() == xpos);
    }

    THEN("Attribute m_ypos should be equal to ypos") {
      REQUIRE(test_mousePositionEvent.GetYpos() == ypos);
    }

    THEN("EventType should be equal to MousePositionInput") {
      Bobert::EventTypeEnum type = Bobert::EventTypeEnum::MousePositionInput;
      REQUIRE(test_mousePositionEvent.GetEventType() == type);
      REQUIRE(test_mousePositionEvent.GetStaticType() == type);
    }
  }
}

SCENARIO("MouseEnterEvent creation and default state", "[events][mouse event][mouse enter event][creation]") {
  GIVEN("New MouseEnterEvent object") {
    bool isEnter = false;
    Bobert::MouseEnterEvent test_mouseEnterEvent(isEnter);

    THEN("Attribute m_isEnter should be equal to isEnter") {
      REQUIRE(test_mouseEnterEvent.IsEnter() == isEnter);
    }

    THEN("EventType should be equal to MouseEnterInput") {
      Bobert::EventTypeEnum type = Bobert::EventTypeEnum::MouseEnterInput;
      REQUIRE(test_mouseEnterEvent.GetEventType() == type);
      REQUIRE(test_mouseEnterEvent.GetStaticType() == type);
    }
  }
}

class TestableMouseInputEvent : public Bobert::MouseInputEvent {
  public:
    TestableMouseInputEvent(int button) : MouseInputEvent(button) {}
};

SCENARIO("MouseInputEvent creation and default state", "[events][mouse event][mouse input event][creation]") {
  GIVEN("New MouseInputEvent object") {
    int button = 30;
    TestableMouseInputEvent test_mouseInputEvent(button);

    THEN("Attribute m_button should be equal to button") {
      REQUIRE(test_mouseInputEvent.GetButton() == button);
    }

    THEN("EventType should be equal to MouseInput") {
      Bobert::EventTypeEnum type = Bobert::EventTypeEnum::MouseInput;
      REQUIRE(test_mouseInputEvent.GetEventType() == type);
      REQUIRE(test_mouseInputEvent.GetStaticType() == type);
    }
  }
}

SCENARIO("MousePressEvent creation and default state", "[events][mouse event][mouse press event][creation]") {
  GIVEN("New MousePressEvent object") {
    int button = 30;
    bool isRepeat = false;
    Bobert::MousePressEvent test_mousePressEvent(button, isRepeat);

    THEN("Attribute m_button should be equal to button") {
      REQUIRE(test_mousePressEvent.GetButton() == button);
    }

    THEN("Attribute m_isRepeat should be equal to isRepeat") {
      REQUIRE(test_mousePressEvent.IsRepeat() == isRepeat);
    }

    THEN("EventType should be equal to MousePressInput") {
      Bobert::EventTypeEnum type = Bobert::EventTypeEnum::MousePressInput;
      REQUIRE(test_mousePressEvent.GetEventType() == type);
      REQUIRE(test_mousePressEvent.GetStaticType() == type);
    }
  }
}

SCENARIO("MouseReleaseEvent creation and default state", "[events][mouse event][mouse release event][creation]") {
  GIVEN("New MouseReleaseEvent object") {
    int button = 30;
    Bobert::MouseReleaseEvent test_mouseReleaseEvent(button);

    THEN("Attribute m_button should be equal to button") {
      REQUIRE(test_mouseReleaseEvent.GetButton() == button);
    }

    THEN("EventType should be equal to MouseReleaseInput") {
      Bobert::EventTypeEnum type = Bobert::EventTypeEnum::MouseReleaseInput;
      REQUIRE(test_mouseReleaseEvent.GetEventType() == type);
      REQUIRE(test_mouseReleaseEvent.GetStaticType() == type);
    }
  }
}

// Window Events
SCENARIO("WindowResizingEvent creation and default state", "[events][window event][window resizing event][creation]") {
  GIVEN("New WindowResizingEvent object") {
    int width = 30;
    int height = 20;
    Bobert::WindowResizingEvent test_windowResizingEvent(width, height);

    THEN("Attribute m_width should be equal to width") {
      REQUIRE(test_windowResizingEvent.GetWidth() == width);
    }

    THEN("Attribute m_height should be equal to height") {
      REQUIRE(test_windowResizingEvent.GetHeight() == height);
    }

    THEN("EventType should be equal to WindowResizingInput") {
      Bobert::EventTypeEnum type = Bobert::EventTypeEnum::WindowResizingInput;
      REQUIRE(test_windowResizingEvent.GetEventType() == type);
      REQUIRE(test_windowResizingEvent.GetStaticType() == type);
    }
  }
}

SCENARIO("WindowCloseEvent creation and default state", "[events][window event][window close event][creation]") {
  GIVEN("New WindowCloseEvent object") {
    Bobert::WindowCloseEvent test_windowCloseEvent;

    THEN("EventType should be equal to WindowCloseInput") {
      Bobert::EventTypeEnum type = Bobert::EventTypeEnum::WindowCloseInput;
      REQUIRE(test_windowCloseEvent.GetEventType() == type);
      REQUIRE(test_windowCloseEvent.GetStaticType() == type);
    }
  }
}

SCENARIO("WindowFocusEvent creation and default state", "[events][window event][window focus event][creation]") {
  GIVEN("New WindowFocusEvent object") {
    Bobert::WindowFocusEvent test_windowFocusEvent;

    THEN("EventType should be equal to WindowFocusInput") {
      Bobert::EventTypeEnum type = Bobert::EventTypeEnum::WindowFocusInput;
      REQUIRE(test_windowFocusEvent.GetEventType() == type);
      REQUIRE(test_windowFocusEvent.GetStaticType() == type);
    }
  }
}
