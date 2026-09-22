#pragma once

#include "Event.h"

namespace Bobert {
  /// @brief Child of Bobert::Event, represents a resizing a window event.
  class Bobert_API WindowResizingEvent : public Event {
    public:
      WindowResizingEvent(int width, int height) : m_width(width), m_height(height) {}

      const EventTypeEnum GetEventType() const override {return EventTypeEnum::WindowResizingInput;}
      static const EventTypeEnum GetStaticType() {return EventTypeEnum::WindowResizingInput;}

      /// @brief Returns a new client area width.
      /// @return Width of a client area in screen coordinates.
      const int GetWidth() const {return m_width;}
      /// @brief Returns a new client area height.
      /// @return Height of a client area in screen coordinates.
      const int GetHeight() const {return m_height;}

    private:
      int m_width; ///< Width of a client area in screen coordinates.
      int m_height; ///< Height of a client area in screen coordinates.
  };


  /// @brief Child of Bobert::Event, represents a closing a window event.
  class Bobert_API WindowCloseEvent : public Event {
    public:
      WindowCloseEvent() {}

      const EventTypeEnum GetEventType() const override {return EventTypeEnum::WindowClosingInput;}
      static const EventTypeEnum GetStaticType() {return EventTypeEnum::WindowClosingInput;}
  };


  /// @brief Child of Bobert::Event, represents a focusing on the window event.
  class Bobert_API WindowFocusEvent : public Event {
    public:
      WindowFocusEvent() {}

      const EventTypeEnum GetEventType() const override {return EventTypeEnum::WindowFocusInput;}
      static const EventTypeEnum GetStaticType() {return EventTypeEnum::WindowFocusInput;}
  };
};