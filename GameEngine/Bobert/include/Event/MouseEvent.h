#pragma once 
#include "Event.h"

namespace Bobert {
  class MouseEvent : public Event
    {
        public:
            MouseEvent(int button) : button{button} {}
            const EventTypeEnum GetEventType() const override {return EventTypeEnum::MouseInput;}
            static const EventTypeEnum GetStaticType() {return EventTypeEnum::MouseInput;}

            const int GetButton() const {return button;}
        public:
            int button;
    };
};