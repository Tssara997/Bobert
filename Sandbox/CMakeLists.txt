cmake_minimum_required(VERSION 3.10)
project(Sandbox)

set(CMAKE_CXX_STANDARD 17)

add_executable(Sandbox src/Application.cpp)

target_link_libraries(Sandbox PRIVATE Bobert)

# set_target_properties(Sandbox PROPERTIES
#     RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>"
# )

add_custom_command(TARGET Sandbox POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:Bobert>
    $<TARGET_FILE_DIR:Sandbox>
)