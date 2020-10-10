#include <iostream>

#include "FragmentShader.hpp"
#include "ReadFile.hpp"
#include "SDLEventLoop.hpp"
#include "SDLEventReceiver.hpp"
#include "ShaderProgram.hpp"
#include "VertexArrayObject.hpp"
#include "VertexBufferObject.hpp"
#include "VertexShader.hpp"
#include "Window.hpp"

void initSDL()
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
    }
    else
    {
        std::cout << "SDL initialized successfully!" << std::endl;
    }
}

int main(int argc, char *argv[])
{
    std::cout << "Hello world!" << std::endl;

    initSDL();

    Window win (640, 480, 4, 5);
    std::cout << "Created a window with size " << win.getWidth() << "x" << win.getHeight() << std::endl;
    std::cout << "glGetString" << glGetString(GL_VERSION) << std::endl;

    ShaderProgram sp;
    VertexShader vs (
        readFile("D:/Docs/programming/terrain/shaders/basic.vs.glsl")
    );
    vs.compile();
    FragmentShader fs (
        readFile("D:/Docs/programming/terrain/shaders/basic.fs.glsl")
    );
    fs.compile();

    sp.attachShader(vs);
    sp.attachShader(fs);
    sp.linkProgram();

    VertexBufferObject vbo;
    VertexArrayObject vao;

    std::vector<GLfloat> vertexData {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f
    };
    vbo.bind();
    vbo.bufferData(vertexData);

    vao.bind();
    vao.enableVertexAttribArray(0);
    vao.vertexAttribPointer(2, GL_FLOAT);
    vbo.unbind();
    vao.unbind();

    SDLEventLoop loop = SDLEventLoop();
    SDLEventReceiver watcher = SDLEventReceiver();
    loop.addReceiver(&watcher);

    while(!watcher.isFinished())
    {
        //std::cout << "Listening for events..." << std::endl;
        loop.getEvents();

        win.clear();
        sp.bind();

        vao.bind();
        glDrawArraysEXT(GL_TRIANGLE_FAN, 0, 4);
        vao.unbind();

        win.swap();
    }

    SDL_Quit();
    return 0;
}
