cmake_minimum_required(VERSION 3.7...3.19)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(
    glWrap VERSION 0.1
    DESCRIPTION "Gl testing"
    LANGUAGES CXX
)

#GLM
include_directories(third_party/glm)

# SDL
find_package(SDL2 REQUIRED)
include_directories(glWrap ${SDL2_INCLUDE_DIRS})

# GLEW
find_package(GLEW REQUIRED)
include_directories(glWrap ${GLEW_INCLUDE_DIRS})

# OpenGL
find_package(OpenGL REQUIRED)
include_directories(glWrap ${OPENGL_INCLUDE_DIRS})

# Executable
include_directories(glWrap include)
add_executable(glWrap main.cpp)
add_subdirectory(src)

# Linking
target_link_libraries(glWrap ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})