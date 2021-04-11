#include "SDLEventReceiver.hpp"
#include <iostream>
SDLEventReceiver::SDLEventReceiver()
{
    //ctor
}

SDLEventReceiver::~SDLEventReceiver()
{
    //dtor
}

void SDLEventReceiver::onNotify(MouseButtonEvent event)
{
	std::cout << "MouseButtonEvent event received!" << std::endl;
}

void SDLEventReceiver::onNotify(QuitEvent event)
{
	std::cout << "QuitEvent received!" << std::endl;
    m_finished = true;
    std::cout << "m_finished: "<< m_finished << std::endl;
}
