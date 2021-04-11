#include <iostream>

#include "Event.hpp"
#include "SDLEventLoop.hpp"

SDLEventLoop::SDLEventLoop()
{
    //ctor
}

SDLEventLoop::~SDLEventLoop()
{
    //dtor
}

void SDLEventLoop::getEvents()
{
    SDL_Event e;
    while(SDL_PollEvent(&e) != 0)
    {
        std::cout << "Event loop run!" << std::endl;

        if(e.type == SDL_QUIT)
        {
            std::cout << "Dispatching QuitEvent!" << std::endl;
            QuitEvent event;
            notify(event);
        }
        else if(e.type == SDL_MOUSEBUTTONDOWN)
        {
            MouseButtonEvent outEvent;
            outEvent.button = MouseButton::LEFT;
            outEvent.direction = EventDirection::DOWN;
            notify(outEvent);
        }
        else if(e.type == SDL_MOUSEBUTTONUP)
        {
            MouseButtonEvent outEvent;
            outEvent.button = MouseButton::LEFT;
            outEvent.direction = EventDirection::UP;
            notify(outEvent);
        }
        else if(e.type == SDL_MOUSEWHEEL)
        {
            ScrollEvent outEvent;
            outEvent.direction == e.y;
            notify(outEvent);
        }
    }
}
