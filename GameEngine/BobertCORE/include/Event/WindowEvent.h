#pragma once

#include "Event.h"

namespace Bobert {
  /// @brief Child of Bobert::Event, represents a window resizing event.
  class Bobert_API WindowResizingEvent : public Event {
    public:
      WindowResizingEvent(int width, int height) : m_width(width), m_height(height) {}

      EventTypeEnum GetEventType() const noexcept override {return EventTypeEnum::WindowResizingInput;}
      static EventTypeEnum GetStaticType() noexcept {return EventTypeEnum::WindowResizingInput;}

      /// @brief Returns a new client area width.
      /// @return Width of a client area in screen coordinates.
      int GetWidth() const noexcept {return m_width;}

      /// @brief Returns a new client area height.
      /// @return Height of a client area in screen coordinates.
      int GetHeight() const noexcept {return m_height;}

    private:
      int m_width; ///< Width of a client area in screen coordinates.
      int m_height; ///< Height of a client area in screen coordinates.
  };


  /// @brief Child of Bobert::Event, represents a window closing event.
  class Bobert_API WindowCloseEvent : public Event {
    public:
      WindowCloseEvent() {}

      EventTypeEnum GetEventType() const noexcept override {return EventTypeEnum::WindowClosingInput;}
      static EventTypeEnum GetStaticType() noexcept {return EventTypeEnum::WindowClosingInput;}
  };


  /// @brief Child of Bobert::Event, represents a window focus event.
  class Bobert_API WindowFocusEvent : public Event {
    public:
      WindowFocusEvent() {}

      EventTypeEnum GetEventType() const noexcept override {return EventTypeEnum::WindowFocusInput;}
      static EventTypeEnum GetStaticType() noexcept {return EventTypeEnum::WindowFocusInput;}
  };
};