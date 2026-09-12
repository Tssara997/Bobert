#pragma once
#include "include/Core.h"

namespace Bobert {

    enum EventTypeEnum {
        None = 0,
        UserInput,
        KeyInput, KeyPressInput, KeyReleaseInput,
        MouseEnterInput, MousePositionInput, MouseInput, MousePressInput, MouseReleaseInput,
        Count
    };


    class Bobert_API Event 
    {
        public:
            virtual const EventTypeEnum GetEventType() const = 0;
        protected:
            bool m_handled {false};
        
    };


    class Window;


    class Bobert_API UserEvent : public Event
    {
        public:
            const EventTypeEnum GetEventType() const override {return EventTypeEnum::UserInput;}
            static const EventTypeEnum GetStaticType() {return EventTypeEnum::UserInput;}

            const Window& GetWindow() const;
        protected:
            UserEvent(Window& window);
            Window* m_window;
    };
};