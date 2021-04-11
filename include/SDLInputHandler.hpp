#ifndef SDLINPUTHANDLER_HPP
#define SDLINPUTHANDLER_HPP

#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_keysym.h>

#include "EventReceiver.hpp"

class SDLInputHandler : public EventReceiver {
	public:
		SDLInputHandler();
		void onNotify(MouseButtonEvent event);
        void onNotify(QuitEvent event);
        void onNotify(ScrollEvent event);
	private:
		std::map<SDLKey, bool> m_keymap;
		std::map<Uint8, bool> m_mousemap;
		std::pair<int, int> m_curMousePos;
		std::pair<int, int> m_prevMousePos;
		int m_prevScroll;
		int m_curScroll;
};

#endif