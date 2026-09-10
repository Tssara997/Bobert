cmake_minimum_required(VERSION 3.14)
project(Bobert)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw
    Git_TAG 3.5
)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_TESTS OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(glfw)

add_library(Glad STATIC deps/glad/src/glad.c)
target_include_directories(Glad PUBLIC deps/glad/include)

add_library(Bobert SHARED
    Bobert/src/Application.cpp
    Bobert/src/Logger.cpp
    Bobert/src/Window.cpp
)

target_link_libraries(Bobert PUBLIC glfw Glad)

target_precompile_headers(Bobert PRIVATE Bobert/include/pch.h)

install(TARGETS Bobert DESTINATION lib)
install(FILES Bobert/Bobert.h DESTINATION include)

target_include_directories(Bobert PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/Bobert
)

target_compile_definitions(Bobert PUBLIC BB_BUILD_DLL)

if (WIN32)
    target_compile_definitions(Bobert PUBLIC BB_PLATFORM_WINDOWS)
elseif (UNIX AND NOT APPLE)
    target_compile_definitions(Bobert PUBLIC BB_PLATFORM_LINUX)
endif()

set_target_properties(Bobert PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/aaaa
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

