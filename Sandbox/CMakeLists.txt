cmake_minimum_required(VERSION 3.10)
project(Sandbox)

set(CMAKE_CXX_STANDARD 17)

add_executable(Sandbox src/Application.cpp)

if (USE_CUSTOM_LIBS)
    target_link_libraries(Sandbox PRIVATE Bobert)
endif()

set_target_properties(Sandbox PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)