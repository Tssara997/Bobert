cmake_minimum_required(VERSION 3.14)
project(SpriteEditor)

set(CMAKE_CXX_STANDARD 20)

add_executable(SpriteEditor src/Application.cpp)


target_link_libraries(SpriteEditor PRIVATE Bobert)


if (WIN$32)
    set_target_properties(Sandbox PROPERTIES
      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Tools/SpriteEditor"
    )
elseif (UNIX AND NOT APPLE)
    set_target_properties(Sandbox PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Tools/SpriteEditor"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Tools/SpriteEditor"
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/lib"
    )
endif()

add_custom_command(TARGET SpriteEditor POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Bobert>
        $<TARGET_FILE_DIR:SpriteEditor>
    COMMENT "Kopiowanie Bobert.dll do folderu tools..."
)