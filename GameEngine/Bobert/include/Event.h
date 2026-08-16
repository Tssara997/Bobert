#pragma once

namespace Bobert {
    class Bobert_API Event 
    {
        public:
            virtual const std::string GetEventType() const = 0;
        private:
            bool handled {false};
        
    };

    class KeyEvent : public Event 
    {
        public:
            KeyEvent(int key) : key{key} {}
            const std::string GetEventType() const override {return "5645366";}
            static const std::string GetStaticType() {return "5645366";}
        public:
            int key;

    };

    class MouseEvent : public Event
    {
        public:
            MouseEvent(int button) : button{button} {}
            const std::string GetEventType() const override {return "94835793";}
            static const std::string GetStaticType() {return "94835793";}
        public:
            int button;
    };
};