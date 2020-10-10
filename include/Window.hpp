#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <cstddef>
#include <functional>
#include <memory>
#include <SDL2/SDL.h>
#include "GLHeaders.hpp"

class Window
{
    public:
        Window(size_t, size_t, int, int);
        ~Window();

        void clear();

        size_t getWidth() { return m_width; }
        void setWidth(size_t val) { m_width = val; }

        size_t getHeight() { return m_height; }
        void setHeight(size_t val) { m_height = val; }

        void swap();

    protected:

    private:
        SDL_GLContext m_glContext;
        std::size_t m_height;
        std::size_t m_width;
        std::unique_ptr<SDL_Window, std::function<void(SDL_Window*)>> m_window;
        //std::unique_ptr<SDL_Surface> m_surface;
};

#endif // WINDOW_
