
#include "SDLInputHandler.hpp"

SDLInputHandler::SDLInputHandler() :
	m_curMousePos(0, 0),
	m_prevMousePos(0, 0)
{

}

void SDLInputHandler::onNotify(MouseMoveEvent _event)
{
	m_prevMousePos.first = m_curMousePos.first;
	m_prevMousePos.second = m_curMousePos.second;
	
	int x = 0;
	int y = 0;
	SDL_GetMouseState(&x, &y);
	m_curMousePos.first = x;
	m_curMousePos.second = y;
}