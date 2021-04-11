#ifndef EVENTDISPATCHER_HPP
#define EVENTDISPATCHER_HPP

#include <algorithm>
#include <memory>
#include <vector>

#include "Event.hpp"
#include "EventReceiver.hpp"

#include <iostream>
class EventDispatcher
{
    public:
        EventDispatcher() = default;
        virtual ~EventDispatcher() = default;

        void addReceiver(EventReceiver* _receiver)
        {
            m_receivers.push_back(_receiver);
        }

        void removeReceiver(EventReceiver* _receiver)
        {
            std::remove(
                m_receivers.begin(),
                m_receivers.end(),
                _receiver
            );
        }

    protected:
        template <class T>
        void notify(T event)
        {
            std::cout << "Dispatching event to " << m_receivers.size() << " receivers...\n";
            for(auto &receiver : m_receivers)
            {
                std::cout << "\tDispatch!\n";
                receiver->onNotify(event);
            }
        }

    private:
        std::vector<EventReceiver*> m_receivers; 
};

#endif // EVENTDISPATCHER_HPP
