#pragma once
#include "Core.h"
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
        private:
            std::queue<Event> eventQueue;
            std::unordered_map<std::string, std::vector<std::unique_ptr<IEventManagerWrapper>>> subs;

        public:
            void TriggerEvent(const Event& event) {
                auto it = subs.find(event.GetEventType());
                if (it == subs.end())
                    return;

                for (const auto& subcriber : it->second) {
                    subcriber->Execute(event);
                }
            }
            template <typename EventType>
            void Subscribe(const std::string& eventTypeStr, const EventHandler<EventType>& handler) {
                std::cout << eventTypeStr << std::endl;
                subs[eventTypeStr].push_back(std::make_unique<EventManagerWrapper<EventType>>(handler));
            }


    };
};