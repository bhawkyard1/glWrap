#include <iostream>
#include <math.h>

#include "Camera.hpp"
#include "FragmentShader.hpp"
#include "GLInit.hpp"
#include "Mesh.hpp"
#include "ReadFile.hpp"
#include "SDLEventLoop.hpp"
#include "SDLEventReceiver.hpp"
#include "SDLInputHandler.hpp"
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
    Window win (640, 480);
    initGL(4, 5);

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
    bunny.generateBuffers();

    Mesh plane;
    plane.loadObj({
        "v -1 -1 0",
        "v 1 -1 0",
        "v -1 1 0",
        "v -1 1 0",
        "v 1 -1 0",
        "v 1 1 0",
        "vt 0 0",
        "vt 1 0",
        "vt 0 1",
        "vt 0 1",
        "vt 1 0",
        "vt 1 1",
        "vn 0 0 -1",
        "vn 0 0 -1",
        "vn 0 0 -1"
        "vn 0 0 -1"
        "vn 0 0 -1"
        "vn 0 0 -1"
    });
    plane.generateBuffers();

    Transform root;
    Transform geoTransform;
    geoTransform.setScale(1, -1, 1);
    root.addChild(geoTransform);

    Camera camera (
        win.getWidth() / win.getHeight(),
        30.0,
        0.001,
        32.0
    );
    Transform cameraTransform;
    // cameraTransform.setTranslation(glm::vec3(0.0, 0.0, -1000));
    root.addChild(cameraTransform);

    SDLEventLoop loop = SDLEventLoop();
    SDLEventReceiver watcher = SDLEventReceiver();
    SDLInputHandler inputHandler = SDLInputHandler();
    loop.addReceiver(&watcher);
    loop.addReceiver(&inputHandler);

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
            geoTransform.getMatrix(WORLD)
        );
        sp.setUniform(
            "MVP",
            MVP
        );

        bunny.bind();
        glDrawArraysEXT(GL_TRIANGLES, 0, bunny.size());
        bunny.unbind();

        plane.bind();
        glDrawArraysEXT(GL_TRIANGLES, 0, plane.size());
        plane.unbind();

        win.swap();

        cameraTransform.setTranslation(0.0, 0.0, sin(t) * 0.5 - 1);
        geoTransform.setRotation(0, t, 0);

        t+=0.025;
        if(t > M_PI)
        {
            t=-M_PI;
        }
    }

    SDL_Quit();
    return 0;
}
