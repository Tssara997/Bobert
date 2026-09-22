#pragma once
#include "Core.h"

namespace Bobert {
    /// @brief Type of every event that exists in the engine. Used in Bobert::EventManager for subscription recognition.
    enum EventTypeEnum {
        None = 0,
        KeyInput, KeyPressInput, KeyReleaseInput,
        MouseEnterInput, MousePositionInput, MouseInput, MousePressInput, MouseReleaseInput,
        WindowInput, WindowResizingInput, WindowClosingInput, WindowFocusInput,
        Count
    };

    /// @brief Represents an event in engine. It's an abstract class used as a base for every other event.
    class Bobert_API Event 
    {
        public:
            /// @brief Returns the type of an event.
            /// @return An object Bobert::EventTypeEnum.
            virtual const EventTypeEnum GetEventType() const = 0;
        protected:
            bool m_handled {false};
        
    };
};