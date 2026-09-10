#pragma once 
#include "Event.h"
#include "include/Window.h"

namespace Bobert {
    class MousePositionEvent : public Event {
        public:
            MousePositionEvent(double xpos, double ypos) : m_xpos{xpos}, m_ypos{ypos} {}

            const EventTypeEnum GetEventType() const override {return EventTypeEnum::MousePositionInput;}
            static const EventTypeEnum GetStaticType() {return EventTypeEnum::MousePositionInput;}

            const double GetXpos() const {return m_xpos;}
            const double GetYpos() const {return m_ypos;}

        private:
            double m_xpos;
            double m_ypos;
    };


    class MouseEnterEvent : public Event {
        public:
            MouseEnterEvent(bool isEnter, Window& window) : m_isEnter{isEnter}, m_window{window} {}

            const EventTypeEnum GetEventType() const override {return EventTypeEnum::MouseEnterInput;}
            static const EventTypeEnum GetStaticType() {return EventTypeEnum::MouseEnterInput;}

            const bool IsEnter() const {return m_isEnter;}
            const Window& GetWindow() const {return m_window;}
        private:
            bool m_isEnter;
            Window m_window;
    };


    class MouseInputEvent : public Event
    {
        public:
            const EventTypeEnum GetEventType() const override {return EventTypeEnum::MouseInput;}
            static const EventTypeEnum GetStaticType() {return EventTypeEnum::MouseInput;}

            const int GetButton() const {return m_button;}
        protected:
            MouseInputEvent(int button) : m_button{button} {}
            int m_button;
    };


    class MousePressEvent : public MouseInputEvent {
        public:
            MousePressEvent(int button, bool isRepeat) : MouseInputEvent(button), m_isRepeat{isRepeat} {}

            const EventTypeEnum GetEventType() const override {return EventTypeEnum::MousePressInput;}
            static const EventTypeEnum GetStaticType() {return EventTypeEnum::MousePressInput;}

            const bool IsRepeated() const {return m_isRepeat;}
        private:
            bool m_isRepeat;
    };


    class MouseReleaseEvent : public MouseInputEvent {
        public:
            MouseReleaseEvent(int button) : MouseInputEvent(button) {}

            const EventTypeEnum GetEventType() const override {return EventTypeEnum::MouseReleaseInput;}
            static const EventTypeEnum GetStaticType() {return EventTypeEnum::MouseReleaseInput;}
    };
};