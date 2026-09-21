#pragma once
#include "Core.h"

namespace Bobert {
    /// @brief Type of every event that exists in the engine. Used in Bobert::EventManager::TriggerEvent for subsription recognition.
    enum EventTypeEnum {
        None = 0,
        KeyInput, KeyPressInput, KeyReleaseInput,
        MouseEnterInput, MousePositionInput, MouseInput, MousePressInput, MouseReleaseInput,
        WindowInput, WindowResizingInput, WindowClosingInput, WindowFocusInput,
        Count
    };

    /// @brief Represents an event in engine. Its an abstract class used as a base for every other event. Cannot be triggered.
    class Bobert_API Event 
    {
        public:
            /// @brief Returns an event type.
            /// @return Object Bobert::EventTypeEnum
            virtual const EventTypeEnum GetEventType() const = 0;
        protected:
            bool m_handled {false};
        
    };
};