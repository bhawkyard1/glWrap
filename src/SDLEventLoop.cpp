#include <iostream>

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
        //std::cout << "Event loop run!" << std::endl;

        if(e.type == SDL_QUIT)
        {
            notify(Event::QUIT);
        }
    }
}
