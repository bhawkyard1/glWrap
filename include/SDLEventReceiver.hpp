#ifndef SDLEVENTRECEIVER_HPP
#define SDLEVENTRECEIVER_HPP

#include "Event.hpp"
#include "EventReceiver.hpp"

class SDLEventReceiver : public EventReceiver
{
    public:
        SDLEventReceiver();
        virtual ~SDLEventReceiver();

        bool isFinished() const {return m_finished;}

        void onNotify(MouseButtonEvent event);
        void onNotify(QuitEvent event);

    private:
        bool m_finished;
};

#endif // SDLEVENTRECEIVER_HPP
