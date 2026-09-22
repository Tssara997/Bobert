#pragma once

#include "Event.h"
#include "Logger.h"

#include <functional>

namespace Bobert {

    /// @brief Helper namespace. Stores a function that takes in refrence to a constant value to an event that is an object of EventType class.
    /// @tparam EventType Type of an event used in the function.
    template <typename EventType>
    using EventHandler = std::function<void(const EventType& e)>;


    /// @brief Abstract interface class for event manager wrapper.
    class IEventManagerWrapper 
    {
        public:
            virtual ~IEventManagerWrapper() = default;
            virtual void Execute(const Event& event) = 0;
    };


    /// @brief Child class of Bobert::IEventManagerWrapper. Used for storing, and calling subscriber functions.
    /// @tparam EventType A type of event used in Bobert::EventHandler function.
    template <typename EventType> 
    class EventManagerWrapper : public IEventManagerWrapper
    {
        public:
            EventManagerWrapper(const EventHandler<EventType>& handler) : handler{handler} {};
            void Execute(const Event& event) override {
                handler(static_cast<const EventType&>(event));
            }
        private:
            EventHandler<EventType> handler;
            // const std::string handlerType;
    };


    /// @brief Class managing the pipline of events. Responsible for reciving an event and then destributing it to the right observers that declared their intrest in the specific event/events.
    class Bobert_API EventManager
    {
        public:
            EventManager() : subs(static_cast<size_t>(EventTypeEnum::Count)) {
                Logger::Info("Initialization Event system successful");
            }

            /// @brief Informs the event manager that an event happend in the engine, which calls the corrensponding (to the event) functions of the subscribers.
            /// @param event A reference to event that happend.
            void TriggerEvent(const Event& event) {
                const auto& func = subs[event.GetEventType()];
                if (func.size() == 0)
                    return;

                for (const auto& subscriber : func) {
                    subscriber->Execute(event);
                }
            }

            /// @brief Subscribes to a specific event, by giving a function that is going to be called when the event happens.
            /// @tparam EventType Type of event used in callable function.
            /// @param eventTypeEnum A refrence to an enum value assing to the event.
            /// @param handler A refrence to a callable function that takes in refrence to a constant value of an event of an EventType class.
            template <typename EventType>
            void Subscribe(const EventTypeEnum& eventTypeEnum, const EventHandler<EventType>& handler) {
                std::string text = "Subscription of an event of id:";
                auto id = int(eventTypeEnum);
                std::string msg = std::vformat("{} {}", std::make_format_args(text, id));
                Logger::Info(msg);
                subs[eventTypeEnum].push_back(std::make_unique<EventManagerWrapper<EventType>>(handler));
            }

        private:
            std::queue<Event> eventQueue;
            std::vector<std::vector<std::unique_ptr<IEventManagerWrapper>>> subs;
    };
};