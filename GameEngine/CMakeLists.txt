cmake_minimum_required(VERSION 3.10)
project(Bobert)

set(CMAKE_CXX_STANDARD 17)

add_library(Bobert SHARED src/Test.cpp)

install(TARGETS Bobert DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)

target_include_directories(Bobert PUBLIC include)

set_target_properties(Bobert PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>"
)