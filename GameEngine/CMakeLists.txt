cmake_minimum_required(VERSION 3.10)
project(Bobert)

set(CMAKE_CXX_STANDARD 17)

add_library(Bobert SHARED Bobert/src/Application.cpp)

install(TARGETS Bobert DESTINATION lib)
install(FILES Bobert/Bobert.h DESTINATION include)

target_include_directories(Bobert PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/Bobert
)

target_compile_definitions(Bobert PUBLIC BB_BUILD_DLL)

if (WIN32)
    target_compile_definitions(Bobert PUBLIC BB_PLATFORM_WINDOWS)
endif()

set_target_properties(Bobert PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)