#pragma once 
#include "Event.h"

namespace Bobert {
    /// @brief Child of Bobert::Event, responsible for storing coordinates of a cursor position.
    class MousePositionEvent : public Event {
        public:
            MousePositionEvent(double xpos, double ypos) : m_xpos{xpos}, m_ypos{ypos} {}

            const EventTypeEnum GetEventType() const override {return EventTypeEnum::MousePositionInput;}
            static const EventTypeEnum GetStaticType() {return EventTypeEnum::MousePositionInput;}

            /// @brief Returns the x position of a cursor.
            /// @return Double value representing x coordinates.
            const double GetXpos() const {return m_xpos;}
            /// @brief Returns the y position of a cursor.
            /// @return Double value representing y coordinates.
            const double GetYpos() const {return m_ypos;}

        private:
            double m_xpos; ///< Horizontal position of the cursor in window coordinates.
            double m_ypos; ///< Vertical position of the cursor in window coordinates.
    };


    /// @brief Child of Bobert::Event, represents an event of mouse entering or leaving a window.
    class MouseEnterEvent : public Event {
        public:
            MouseEnterEvent(bool isEnter) : m_isEnter(isEnter) {}

            const EventTypeEnum GetEventType() const override {return EventTypeEnum::MouseEnterInput;}
            static const EventTypeEnum GetStaticType() {return EventTypeEnum::MouseEnterInput;}

            /// @brief Checks whether the mouse is entering or leaving the window.
            /// @return True if the mouse is entering a window, false if it left.
            const bool IsEnter() const {return m_isEnter;}
        private:
            bool m_isEnter; ///< True if the mouse is entering a window, false if it left.
    };


    /// @brief Base class for mouse button events.
    class MouseInputEvent : public Event
    {
        public:
            const EventTypeEnum GetEventType() const override {return EventTypeEnum::MouseInput;}
            static const EventTypeEnum GetStaticType() {return EventTypeEnum::MouseInput;}

            /// @brief Returns the mouse button code associated with the event.
            /// @return GLFW mouse button code as int.
            const int GetButton() const {return m_button;}
        protected:
            MouseInputEvent(int button) : m_button{button} {}
            int m_button; ///< A GLFW mouse button code that triggered an event.
    };


    /// @brief Child of Bobert::MouseInputEvent, represents an event of a mouse button press event.
    class MousePressEvent : public MouseInputEvent {
        public:
            MousePressEvent(int button, bool isRepeat) : MouseInputEvent(button), m_isRepeat{isRepeat} {}

            const EventTypeEnum GetEventType() const override {return EventTypeEnum::MousePressInput;}
            static const EventTypeEnum GetStaticType() {return EventTypeEnum::MousePressInput;}

            /// @brief Checks if the mouse button event is repeated.
            /// @return True if the mouse button is held down.
            const bool IsRepeat() const {return m_isRepeat;}
        private:
            bool m_isRepeat; ///< True if the key is held down.
    };


    /// @brief Child of Bobert::MouseInputEvent, represents an event of a mouse button release event.
    class MouseReleaseEvent : public MouseInputEvent {
        public:
            MouseReleaseEvent(int button) : MouseInputEvent(button) {}

            const EventTypeEnum GetEventType() const override {return EventTypeEnum::MouseReleaseInput;}
            static const EventTypeEnum GetStaticType() {return EventTypeEnum::MouseReleaseInput;}
    };
};