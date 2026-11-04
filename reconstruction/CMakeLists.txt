cmake_minimum_required(VERSION 3.20)
project(i76_reconstruction VERSION 0.2.0 LANGUAGES CXX)

option(I76_BUILD_TESTS "Build unit and functional tests" ON)
option(I76_ENABLE_SANITIZERS "Enable ASan and UBSan" OFF)
option(I76_ENABLE_COVERAGE "Enable GCC/Clang coverage instrumentation" OFF)
option(I76_ENABLE_SDL3 "Build optional SDL3 window shell frontend" OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(I76_ENABLE_SANITIZERS AND I76_ENABLE_COVERAGE)
    message(FATAL_ERROR "Sanitizers and coverage use distinct build directories")
endif()
if((I76_ENABLE_SANITIZERS OR I76_ENABLE_COVERAGE) AND MSVC)
    message(FATAL_ERROR "These sanitizer/coverage settings require GCC or Clang")
endif()

add_library(i76_core STATIC src/runtime.cpp src/command.cpp src/shell.cpp)
target_include_directories(i76_core PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(i76_core PUBLIC
        $<$<CONFIG:Debug>:-O0>
        $<$<CONFIG:Debug>:-fno-omit-frame-pointer>
    )
endif()
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(i76_core PUBLIC $<$<CONFIG:Debug>:-ggdb3>)
endif()
if(MSVC)
    target_compile_options(i76_core PRIVATE /W4 /permissive-)
else()
    target_compile_options(i76_core PRIVATE -Wall -Wextra -Wpedantic -Wshadow)
endif()

add_executable(i76 src/main.cpp src/shell_terminal.cpp)
target_link_libraries(i76 PRIVATE i76_core)

if(I76_ENABLE_SDL3)
    find_package(SDL3 3.2 CONFIG REQUIRED)
    target_sources(i76 PRIVATE src/shell_sdl.cpp)
    target_link_libraries(i76 PRIVATE SDL3::SDL3)
    target_compile_definitions(i76 PRIVATE I76_ENABLE_SDL3=1)
endif()

if(I76_ENABLE_SANITIZERS)
    target_compile_options(i76_core PUBLIC -fsanitize=address,undefined -fno-omit-frame-pointer)
    target_link_options(i76_core PUBLIC -fsanitize=address,undefined)
endif()
if(I76_ENABLE_COVERAGE)
    target_compile_options(i76_core PUBLIC --coverage -O0)
    target_link_options(i76_core PUBLIC --coverage)
endif()

if(I76_BUILD_TESTS)
    enable_testing()
    add_executable(i76_unit_runtime tests/test_runtime.cpp)
    target_link_libraries(i76_unit_runtime PRIVATE i76_core)
    add_test(NAME unit_runtime COMMAND i76_unit_runtime)
    set_tests_properties(unit_runtime PROPERTIES LABELS "unit;memcheck")

    add_executable(i76_unit_commands tests/test_commands.cpp)
    target_link_libraries(i76_unit_commands PRIVATE i76_core)
    add_test(NAME unit_commands COMMAND i76_unit_commands)
    set_tests_properties(unit_commands PROPERTIES LABELS "unit;memcheck")

    add_executable(i76_unit_shell tests/test_shell.cpp)
    target_link_libraries(i76_unit_shell PRIVATE i76_core)
    add_test(NAME unit_shell COMMAND i76_unit_shell)
    set_tests_properties(unit_shell PROPERTIES LABELS "unit;memcheck")

    add_executable(i76_unit_terminal tests/test_shell_terminal.cpp src/shell_terminal.cpp)
    target_link_libraries(i76_unit_terminal PRIVATE i76_core)
    add_test(NAME unit_terminal COMMAND i76_unit_terminal)
    set_tests_properties(unit_terminal PROPERTIES LABELS "unit;memcheck")

    add_test(NAME functional_headless COMMAND i76 --headless --command "step 3" --command status)
    set_tests_properties(functional_headless PROPERTIES
        LABELS "functional;memcheck" PASS_REGULAR_EXPRESSION "ticks=3 paused=false")
    add_test(NAME functional_help COMMAND i76 --help)
    set_tests_properties(functional_help PROPERTIES
        LABELS "functional;memcheck" PASS_REGULAR_EXPRESSION "usage: i76")
    add_test(NAME functional_bad_input COMMAND i76 --command "step -1")
    set_tests_properties(functional_bad_input PROPERTIES LABELS "functional" WILL_FAIL TRUE)

    add_test(NAME functional_shell COMMAND i76 --shell --command play --command "step 3" --command status --command menu)
    set_tests_properties(functional_shell PROPERTIES
        LABELS "functional;memcheck" PASS_REGULAR_EXPRESSION "ticks=3 paused=false")
    add_test(NAME functional_shell_menu COMMAND i76 --shell --command options --command back --command about --command back --command exit)
    set_tests_properties(functional_shell_menu PROPERTIES
        LABELS "functional;memcheck" PASS_REGULAR_EXPRESSION "exit requested")
    add_test(NAME functional_shell_invalid COMMAND i76 --shell --command "step 3")
    set_tests_properties(functional_shell_invalid PROPERTIES LABELS "functional" WILL_FAIL TRUE)
    add_test(NAME functional_shell_help COMMAND i76 --shell --command help)
    set_tests_properties(functional_shell_help PROPERTIES
        LABELS "functional;memcheck" PASS_REGULAR_EXPRESSION "select 1-8")
    add_test(NAME functional_version COMMAND i76 --version)
    set_tests_properties(functional_version PROPERTIES
        LABELS "functional;memcheck" PASS_REGULAR_EXPRESSION "framework 0.2.0")
    add_test(NAME functional_unknown_argument COMMAND i76 --not-an-option)
    set_tests_properties(functional_unknown_argument PROPERTIES LABELS "functional" WILL_FAIL TRUE)
    add_test(NAME functional_invalid_frame_count COMMAND i76 --shell=sdl --shell-frames invalid)
    set_tests_properties(functional_invalid_frame_count PROPERTIES LABELS "functional" WILL_FAIL TRUE)
    add_test(NAME functional_frames_require_sdl COMMAND i76 --shell-frames 2)
    set_tests_properties(functional_frames_require_sdl PROPERTIES LABELS "functional" WILL_FAIL TRUE)
    add_test(NAME functional_sdl_conflicting_commands COMMAND i76 --shell=sdl --command exit)
    set_tests_properties(functional_sdl_conflicting_commands PROPERTIES
        LABELS "functional" WILL_FAIL TRUE)
    if(NOT I76_ENABLE_SDL3)
        add_test(NAME functional_sdl_disabled COMMAND i76 --shell=sdl)
        set_tests_properties(functional_sdl_disabled PROPERTIES
            LABELS "functional" WILL_FAIL TRUE)
    endif()
    if(I76_ENABLE_SDL3)
        add_test(NAME functional_sdl_dummy COMMAND i76 --shell=sdl --shell-frames 2)
        set_tests_properties(functional_sdl_dummy PROPERTIES
            LABELS "functional;sdl" ENVIRONMENT "SDL_VIDEODRIVER=dummy;SDL_RENDER_DRIVER=software"
            TIMEOUT 10)
    endif()
endif()
