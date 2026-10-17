cmake_minimum_required(VERSION 3.14)
project(Bobert)

set(CMAKE_CXX_STANDARD 20)


# OpenGL
find_package(OpenGL REQUIRED)

# nlohmann/json
include(FetchContent)

FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json
    GIT_TAG v3.12.0
)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_TESTS OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(nlohmann_json)

#glm
include(FetchContent)

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG        1.0.1 # or desired version/tag
)
FetchContent_MakeAvailable(glm)

# glfw
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw
    Git_TAG 3.5
)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_TESTS OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(glfw)

# glad
add_library(Glad STATIC deps/glad/src/gl.c)

target_include_directories(Glad PUBLIC deps/glad/include)
set_target_properties(Glad PROPERTIES POSITION_INDEPENDENT_CODE ON)

add_subdirectory(BobertCORE)
add_subdirectory(Modules/BobertUI)
add_subdirectory(Tools)