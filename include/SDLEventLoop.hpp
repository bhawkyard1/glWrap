#ifndef EVENTLOOP_HPP
#define EVENTLOOP_HPP

#include <SDL2/SDL.h>
#include "EventDispatcher.hpp"

class SDLEventLoop : public EventDispatcher
{
    public:
        SDLEventLoop();
        virtual ~SDLEventLoop();

        void getEvents();

    protected:

    private:
};

#endif // EVENTLOOP_HPP
