#include <iostream>
#include "Window.hpp"

Window::Window(size_t _width, size_t _height, int _glMajorVersion, int _glMinorVersion) :
    m_width(_width),
    m_height(_height),
    m_window(
        SDL_CreateWindow(
            "SDL Tutorial",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            _width,
            _height,
            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
        ),
        SDL_DestroyWindow
    )
{
    if(m_window == NULL)
    {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
    }

    m_glContext = SDL_GL_CreateContext(m_window.get());
    if(m_glContext == NULL)
    {
        std::cout << "OpenGL context could not be created! SDL Error: " << SDL_GetError() << std::endl;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, _glMajorVersion);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, _glMinorVersion);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    //Initialize GLEW
    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();
    if(glewError != GLEW_OK)
    {
        std::cout << "Error initializing GLEW! " << glewGetErrorString(glewError) << std::endl;
    }

    //Use Vsync
    if( SDL_GL_SetSwapInterval( 1 ) < 0 )
    {
        std::cout << "Warning: Unable to set VSync! SDL Error: " << SDL_GetError() << std::endl;
    }

    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
}

Window::~Window()
{
    //SDL_FreeSurface(m_surface.get());
    //SDL_DestroyWindow(m_window.get());
}

void Window::clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::swap()
{
    SDL_GL_SwapWindow(m_window.get());
}
