#pragma once

namespace Bobert {

    enum EventTypeEnum {
        None = 0,
        KeyInput, KeyPressInput, KeyReleaseInput,
        MouseInput,
        Count
    };

    class Bobert_API Event 
    {
        public:
            virtual const EventTypeEnum GetEventType() const = 0;
        protected:
            bool handled {false};
        
    };
};