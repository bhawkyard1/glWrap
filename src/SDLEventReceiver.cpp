#include "SDLEventReceiver.hpp"

SDLEventReceiver::SDLEventReceiver()
{
    //ctor
}

SDLEventReceiver::~SDLEventReceiver()
{
    //dtor
}

void SDLEventReceiver::onNotify(Event event)
{
    if(event == Event::QUIT)
    {
        m_finished = true;
    }
}
