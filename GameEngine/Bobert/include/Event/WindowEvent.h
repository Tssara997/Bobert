#pragma once

#include "Event.h"

namespace Bobert {

  class Bobert_API WindowResizingEvent : public UserEvent {
    public:
      WindowResizingEvent(int x, int y, Window& window) : UserEvent(window), m_x(x), m_y(y) {}

      const EventTypeEnum GetEventType() const override {return EventTypeEnum::WindowResizingInput;}
      static const EventTypeEnum GetStaticType() {return EventTypeEnum::WindowResizingInput;}

      const int GetX() const {return m_x;}
      const int GetY() const {return m_y;}

    private:
      int m_x;
      int m_y;
  };


  class Bobert_API WindowCloseEvent : public UserEvent {
    public:
      WindowCloseEvent(Window& window) : UserEvent(window){}

      const EventTypeEnum GetEventType() const override {return EventTypeEnum::WindowClosingInput;}
      static const EventTypeEnum GetStaticType() {return EventTypeEnum::WindowClosingInput;}
  };


  class Bobert_API WindowFocusEvent : public UserEvent {
    public:
      WindowFocusEvent(Window& window) : UserEvent(window){}

      const EventTypeEnum GetEventType() const override {return EventTypeEnum::WindowFocusInput;}
      static const EventTypeEnum GetStaticType() {return EventTypeEnum::WindowFocusInput;}
  };
};