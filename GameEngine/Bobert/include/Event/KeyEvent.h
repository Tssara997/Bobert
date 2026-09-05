#pragma once
#include "Event.h"

namespace Bobert {
  class KeyEvent : public Event 
    {
        public:
            const EventTypeEnum GetEventType() const override {return EventTypeEnum::KeyInput;}
            static const EventTypeEnum GetStaticType() {return EventTypeEnum::KeyInput;}

            const int GetKey() const {return m_key;}

        protected:
            KeyEvent(int key) : m_key{key} {}
            int m_key;

    };

  class KeyPressEvent : public KeyEvent
    {
      public:
        KeyPressEvent(int key, bool isRepeat) : KeyEvent(key), m_isRepeat{isRepeat} {}

        const EventTypeEnum GetEventType() const override {return EventTypeEnum::KeyPressInput;}
        static const EventTypeEnum GetStaticType() {return EventTypeEnum::KeyPressInput;}

        const bool IsRepeat() const {return m_isRepeat;}
      private:
        bool m_isRepeat;
    };

  class KeyReleaseEvent : public KeyEvent
  {
    public:
      KeyReleaseEvent(int key) : KeyEvent(key) {}

      const EventTypeEnum GetEventType() const override {return EventTypeEnum::KeyReleaseInput;}
      static const EventTypeEnum GetStaticType() {return EventTypeEnum::KeyReleaseInput;}
  };
};

