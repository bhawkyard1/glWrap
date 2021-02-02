#include <iostream>
#include <math.h>

#include "Camera.hpp"
#include "FragmentShader.hpp"
#include "Mesh.hpp"
#include "ReadFile.hpp"
#include "SDLEventLoop.hpp"
#include "SDLEventReceiver.hpp"
#include "ShaderProgram.hpp"
#include "Transform.hpp"
#include "VertexShader.hpp"
#include "Window.hpp"

#include "glm/gtx/string_cast.hpp"

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
    initSDL();

    Window win (640, 480, 4, 5);

    ShaderProgram sp;
    VertexShader vs (
        readFile("shaders/basicMVP.vs")
    );
    vs.compile();
    FragmentShader fs (
        readFile("shaders/basic.fs")
    );
    fs.compile();

    sp.attachShader(vs);
    sp.attachShader(fs);
    sp.linkProgram();

    Mesh bunny;
    bunny.loadObj(
        readFileToVector("resources/bunny.obj")
    );
    // bunny.loadObj({
    //     "v -1 -1 0",
    //     "v 1 -1 0",
    //     "v -1 1 0",
    //     "v -1 1 0",
    //     "v 1 -1 0",
    //     "v 1 1 0",
    //     "vt 0 0",
    //     "vt 1 0",
    //     "vt 0 1",
    //     "vt 0 1",
    //     "vt 1 0",
    //     "vt 1 1",
    //     "vn 0 0 -1",
    //     "vn 0 0 -1",
    //     "vn 0 0 -1"
    //     "vn 0 0 -1"
    //     "vn 0 0 -1"
    //     "vn 0 0 -1"
    // });
    bunny.generateBuffers();

    Transform root;
    Transform bunnyTransform;
    bunnyTransform.setTranslation(glm::vec3(0.0, 0.0, 0.0));
    root.addChild(bunnyTransform);

    Camera camera (
        win.getWidth() / win.getHeight(),
        30.0,
        0.001,
        32.0
    );
    Transform cameraTransform;
    cameraTransform.setTranslation(glm::vec3(0.0, 0.0, -5));
    root.addChild(cameraTransform);

    SDLEventLoop loop = SDLEventLoop();
    SDLEventReceiver watcher = SDLEventReceiver();
    loop.addReceiver(&watcher);

    double t = 0.0;
    while(!watcher.isFinished())
    {
        //std::cout << "Listening for events..." << std::endl;
        loop.getEvents();

        win.clear();
        sp.bind();
        glm::mat4 MVP = (
            camera.getProjectMatrix() * 
            cameraTransform.getMatrix(WORLD) *
            bunnyTransform.getMatrix(WORLD)
        );
        sp.setUniform(
            "MVP",
            MVP
        );

        bunny.bind();
        //std::cout << "MVP" << glm::to_string(MVP) << "\n";
        glDrawArraysEXT(GL_TRIANGLES, 0, bunny.size());
        bunny.unbind();

        win.swap();

        cameraTransform.setTranslation(glm::vec3(0.0, 0.0, sin(t) * 0.5 - 0.55));
        t+=0.025;
        if(t > 2.0*M_PI)
        {
            t=0;
        }
    }

    SDL_Quit();
    return 0;
}
