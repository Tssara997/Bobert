cmake_minimum_required(VERSION 3.14)
project(Bobert)

set(CMAKE_CXX_STANDARD 20)


# OpenGL
find_package(OpenGL REQUIRED)

# glfw
include(FetchContent)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw
    Git_TAG 3.5
)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_TESTS OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(glfw)

# glad
add_library(Glad STATIC deps/glad/src/glad.c)
target_include_directories(Glad PUBLIC deps/glad/include)


add_subdirectory(BobertCORE)
add_subdirectory(Modules/BobertUI)
add_subdirectory(Tools)