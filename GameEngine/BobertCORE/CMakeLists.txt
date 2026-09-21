project(BobertCORE)

set(CMAKE_CXX_STANDARD 20)

add_library(BobertCORE SHARED
    src/Application.cpp
    src/Logger.cpp
    src/Window.cpp
    src/WindowScene.cpp
    src/Render.cpp
)

target_include_directories(BobertCORE PUBLIC include)
target_link_libraries(BobertCORE PUBLIC glfw Glad OpenGL::GL)

target_precompile_headers(BobertCORE PRIVATE include/pch.h)

install(TARGETS BobertCORE DESTINATION lib)
install(FILES Bobert.h DESTINATION include)

target_include_directories(BobertCORE PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/BobertCORE
)

target_compile_definitions(BobertCORE PUBLIC BB_BUILD_DLL)

if (WIN32)
    target_compile_definitions(BobertCORE PUBLIC BB_PLATFORM_WINDOWS)
elseif (UNIX AND NOT APPLE)
    target_compile_definitions(BobertCORE PUBLIC BB_PLATFORM_LINUX)
endif()

set_target_properties(BobertCORE PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/aaaa
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

