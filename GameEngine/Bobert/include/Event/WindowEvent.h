#pragma once

#include "Event.h"

namespace Bobert {

  class Bobert_API WindowResizingEvent : public Event {
    public:
      WindowResizingEvent(int width, int height) : m_width(width), m_height(height) {}

      const EventTypeEnum GetEventType() const override {return EventTypeEnum::WindowResizingInput;}
      static const EventTypeEnum GetStaticType() {return EventTypeEnum::WindowResizingInput;}

      const int GetWidth() const {return m_width;}
      const int GetHeight() const {return m_height;}

    private:
      int m_width;
      int m_height;
  };


  class Bobert_API WindowCloseEvent : public Event {
    public:
      WindowCloseEvent() {}

      const EventTypeEnum GetEventType() const override {return EventTypeEnum::WindowClosingInput;}
      static const EventTypeEnum GetStaticType() {return EventTypeEnum::WindowClosingInput;}
  };


  class Bobert_API WindowFocusEvent : public Event {
    public:
      WindowFocusEvent() {}

      const EventTypeEnum GetEventType() const override {return EventTypeEnum::WindowFocusInput;}
      static const EventTypeEnum GetStaticType() {return EventTypeEnum::WindowFocusInput;}
  };
};