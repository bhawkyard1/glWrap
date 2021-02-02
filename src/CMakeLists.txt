# SDL
find_package(SDL2 REQUIRED)
include_directories(glWrap ${SDL2_INCLUDE_DIRS})

# GLEW
find_package(GLEW REQUIRED)
include_directories(glWrap ${GLEW_INCLUDE_DIRS})

target_sources(glWrap
    PUBLIC
        BufferObject.cpp
        Camera.cpp
        EventDispatcher.cpp
        EventReceiver.cpp
        FragmentShader.cpp
        GLBindable.cpp
        GLInit.cpp
        IndexBufferObject.cpp
        Mesh.cpp
        ReadFile.cpp
        SDLEventLoop.cpp
        SDLEventReceiver.cpp
        Shader.cpp
        ShaderProgram.cpp
        Transform.cpp
        VertexArrayObject.cpp
        VertexBufferObject.cpp
        VertexShader.cpp
        Window.cpp
)