#pragma once
#include "Event.h"

namespace Bobert {
  /// @brief Child of Bobert::Event, represents an event of a key input. Base class, not callable, used as a base for all key input events.
  class KeyEvent : public UserEvent
    {
        public:
            const EventTypeEnum GetEventType() const override {return EventTypeEnum::KeyInput;}
            static const EventTypeEnum GetStaticType() {return EventTypeEnum::KeyInput;}

            /// @brief Returns the key code associated with the event.
            /// @return Key code (GLFW key code as int).
            const int GetKey() const {return m_key;}

        protected:
            KeyEvent(int key, Window& window) : UserEvent(window), m_key{key} {}
            int m_key; ///< A GLFW key code as int, of a key that caused an event.

    };

  /// @brief Child of Bobert::KeyEvent, represents an event of a key press input.
  class KeyPressEvent : public KeyEvent
    {
      public:
        KeyPressEvent(int key, bool isRepeat, Window& window) : KeyEvent(key, window), m_isRepeat{isRepeat} {}

        const EventTypeEnum GetEventType() const override {return EventTypeEnum::KeyPressInput;}
        static const EventTypeEnum GetStaticType() {return EventTypeEnum::KeyPressInput;}

        /// @brief Returns a true or false statment, is the key associated with the event held down or not.
        /// @return A bool value, is the key is held down.
        const bool IsRepeat() const {return m_isRepeat;}
      private:
        bool m_isRepeat; ///< A bool value, is the key is held down.
    };

  /// @brief Child of Bobert::KeyEvent, represents an event of a key release input.
  class KeyReleaseEvent : public KeyEvent
  {
    public:
      KeyReleaseEvent(int key, Window& window) : KeyEvent(key, window) {}

      const EventTypeEnum GetEventType() const override {return EventTypeEnum::KeyReleaseInput;}
      static const EventTypeEnum GetStaticType() {return EventTypeEnum::KeyReleaseInput;}
  };
};

