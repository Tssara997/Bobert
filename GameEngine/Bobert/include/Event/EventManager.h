#pragma once
#include "include\Core.h"
#include "Event.h"

namespace Bobert {
    template <typename EventType>
    using EventHandler = std::function<void(const EventType& e)>;

    class IEventManagerWrapper 
    {
        public:
            virtual ~IEventManagerWrapper() = default;
            virtual void Execute(const Event& event) = 0;
    };

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

    class Bobert_API EventManager
    {
        public:
            EventManager() : subs{} { subs.resize(static_cast<int>(EventTypeEnum::Count)); }

            void TriggerEvent(const Event& event) {
                const auto& func = subs[event.GetEventType()];
                if (func.size() == 0)
                    return;

                for (const auto& subcriber : func) {
                    subcriber->Execute(event);
                }
            }
            template <typename EventType>
            void Subscribe(const EventTypeEnum& eventTypeEnum, const EventHandler<EventType>& handler) {
                std::cout << int(eventTypeEnum) << std::endl;
                subs[eventTypeEnum].push_back(std::make_unique<EventManagerWrapper<EventType>>(handler));
            }

        private:
            std::queue<Event> eventQueue;
            // std::unordered_map<EventTypeEnum, std::vector<std::unique_ptr<IEventManagerWrapper>>> subs;
            std::vector<std::vector<std::unique_ptr<IEventManagerWrapper>>> subs;
    };
};