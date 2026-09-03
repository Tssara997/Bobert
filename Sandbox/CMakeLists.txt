cmake_minimum_required(VERSION 3.14)
project(Sandbox)

set(CMAKE_CXX_STANDARD 20)

add_executable(Sandbox src/Application.cpp)

if (USE_CUSTOM_LIBS)
    target_link_libraries(Sandbox PRIVATE Bobert)
endif()

if (WIN$32)
    set_target_properties(Sandbox PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    )
elseif (UNIX AND NOT APPLE)
    set_target_properties(Sandbox PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Sandbox"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Sandbox"
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/lib"
    )
endif()

add_custom_command(TARGET Sandbox POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Bobert>
        $<TARGET_FILE_DIR:Sandbox>
    COMMENT "Kopiowanie Bobert.dll do folderu gry..."
)