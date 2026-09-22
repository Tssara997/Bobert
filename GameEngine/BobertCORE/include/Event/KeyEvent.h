#pragma once
#include "Event.h"

namespace Bobert {
  /// @brief Base class for all key events.
  class KeyEvent : public Event
    {
        public:
            const EventTypeEnum GetEventType() const override {return EventTypeEnum::KeyInput;}
            static const EventTypeEnum GetStaticType() {return EventTypeEnum::KeyInput;}

            /// @brief Returns the key code associated with the event.
            /// @return GLFW key code as int.
            const int GetKey() const {return m_key;}

        protected:
            KeyEvent(int key) : m_key{key} {}
            int m_key; ///< A GLFW key code as int, of a key that triggered an event.

    };

  /// @brief Child of Bobert::KeyEvent, represents a key press event.
  class KeyPressEvent : public KeyEvent
    {
      public:
        KeyPressEvent(int key, bool isRepeat) : KeyEvent(key), m_isRepeat{isRepeat} {}

        const EventTypeEnum GetEventType() const override {return EventTypeEnum::KeyPressInput;}
        static const EventTypeEnum GetStaticType() {return EventTypeEnum::KeyPressInput;}

        /// @brief Checks if the key event is repeated.
        /// @return True if the key is held down, else false.
        const bool IsRepeat() const {return m_isRepeat;}
      private:
        bool m_isRepeat; ///< True if the key is held down, else false.
    };

  /// @brief Child of Bobert::KeyEvent, represents a key release event.
  class KeyReleaseEvent : public KeyEvent
  {
    public:
      KeyReleaseEvent(int key) : KeyEvent(key) {}

      const EventTypeEnum GetEventType() const override {return EventTypeEnum::KeyReleaseInput;}
      static const EventTypeEnum GetStaticType() {return EventTypeEnum::KeyReleaseInput;}
  };
};

