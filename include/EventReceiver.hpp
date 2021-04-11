#ifndef EVENTRECEIVER_HPP
#define EVENTRECEIVER_HPP

#include "Event.hpp"

class EventReceiver
{
    public:
        EventReceiver() = default;
        virtual ~EventReceiver() = default;
        virtual void onNotify(MouseButtonEvent event) {};
        virtual void onNotify(QuitEvent event) {};
        virtual void onNotify(ScrollEvent event) {};

    protected:

    private:
};

#endif // EVENTRECEIVER_HPP
