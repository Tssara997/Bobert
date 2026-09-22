#pragma once
#include "Event.h"

namespace Bobert {
  /// @brief Base class for all key events.
  class KeyEvent : public Event
    {
        public:
            EventTypeEnum GetEventType() const noexcept override {return EventTypeEnum::KeyInput;}
            static EventTypeEnum GetStaticType() noexcept {return EventTypeEnum::KeyInput;}

            /// @brief Returns the key code associated with the event.
            /// @return GLFW key code as int.
            int GetKey() const noexcept {return m_key;}

        protected:
            KeyEvent(int key) : m_key{key} {}
            int m_key; ///< A GLFW key code as int, of a key that triggered an event.

    };

  /// @brief Child of Bobert::KeyEvent, represents a key press event.
  class KeyPressEvent : public KeyEvent
    {
      public:
        KeyPressEvent(int key, bool isRepeat) : KeyEvent(key), m_isRepeat{isRepeat} {}

        EventTypeEnum GetEventType() const noexcept override {return EventTypeEnum::KeyPressInput;}
        static EventTypeEnum GetStaticType() noexcept {return EventTypeEnum::KeyPressInput;}

        /// @brief Checks if the key event is repeated.
        /// @return True if the key is held down, else false.
        bool IsRepeat() const noexcept {return m_isRepeat;}
      private:
        bool m_isRepeat; ///< True if the key is held down, else false.
    };

  /// @brief Child of Bobert::KeyEvent, represents a key release event.
  class KeyReleaseEvent : public KeyEvent
  {
    public:
      KeyReleaseEvent(int key) : KeyEvent(key) {}

      EventTypeEnum GetEventType() const noexcept override {return EventTypeEnum::KeyReleaseInput;}
      static EventTypeEnum GetStaticType() noexcept {return EventTypeEnum::KeyReleaseInput;}
  };
};

