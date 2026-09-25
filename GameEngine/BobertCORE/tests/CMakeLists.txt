cmake_minimum_required(VERSION 3.14)

project(tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.8.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)

add_executable(tests
  test_behaviour/test_behaviour.cpp
  test_behaviour/test_windowBehaviour.cpp
  test_behaviour/test_defaultWindowBehaviour.cpp
)

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain BobertCORE)

add_custom_command(TARGET tests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:BobertCORE>
        $<TARGET_FILE_DIR:tests>
)

include(Catch)
catch_discover_tests(tests)