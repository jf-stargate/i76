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

add_library(i76_world STATIC src/world.cpp)
add_library(i76_assets STATIC src/resource.cpp src/resource_directory.cpp)
target_include_directories(i76_assets PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
add_library(i76_bwd2 STATIC src/bwd2.cpp)
target_include_directories(i76_bwd2 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(i76_bwd2 PUBLIC i76_assets)
add_library(i76_level STATIC src/level.cpp)
target_include_directories(i76_level PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(i76_level PUBLIC i76_assets i76_world)
target_include_directories(i76_world PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
add_library(i76_core STATIC src/runtime.cpp src/command.cpp src/shell.cpp)
target_include_directories(i76_core PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(i76_core PUBLIC i76_bwd2 i76_level i76_assets i76_world)
foreach(i76_target IN ITEMS i76_core i76_world i76_assets i76_level i76_bwd2)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(${i76_target} PUBLIC
            $<$<CONFIG:Debug>:-O0>
            $<$<CONFIG:Debug>:-fno-omit-frame-pointer>
        )
    endif()
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_compile_options(${i76_target} PUBLIC $<$<CONFIG:Debug>:-ggdb3>)
    endif()
    if(MSVC)
        target_compile_options(${i76_target} PRIVATE /W4 /permissive-)
    else()
        target_compile_options(${i76_target} PRIVATE -Wall -Wextra -Wpedantic -Wshadow)
    endif()
endforeach()

add_library(i76_terminal_input STATIC src/line_editor.cpp src/terminal_line.cpp)
target_include_directories(i76_terminal_input PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
if(MSVC)
    target_compile_options(i76_terminal_input PRIVATE /W4 /permissive-)
else()
    target_compile_options(i76_terminal_input PRIVATE -Wall -Wextra -Wpedantic -Wshadow)
endif()

add_executable(i76 src/main.cpp src/shell_terminal.cpp)
target_link_libraries(i76 PRIVATE i76_core i76_terminal_input)

if(I76_ENABLE_SDL3)
    find_package(SDL3 3.2 CONFIG REQUIRED)
    target_sources(i76 PRIVATE src/shell_sdl.cpp)
    target_link_libraries(i76 PRIVATE SDL3::SDL3)
    target_compile_definitions(i76 PRIVATE I76_ENABLE_SDL3=1)
endif()

foreach(i76_target IN ITEMS i76_core i76_world i76_assets i76_level i76_bwd2 i76_terminal_input)
    if(I76_ENABLE_SANITIZERS)
        target_compile_options(${i76_target} PUBLIC -fsanitize=address,undefined -fno-omit-frame-pointer)
        target_link_options(${i76_target} PUBLIC -fsanitize=address,undefined)
    endif()
    if(I76_ENABLE_COVERAGE)
        target_compile_options(${i76_target} PUBLIC --coverage -O0)
        target_link_options(${i76_target} PUBLIC --coverage)
    endif()
endforeach()

if(I76_BUILD_TESTS)
    enable_testing()
    add_executable(i76_unit_bwd2 tests/test_bwd2.cpp)
    target_link_libraries(i76_unit_bwd2 PRIVATE i76_bwd2)
    add_test(NAME unit_bwd2 COMMAND i76_unit_bwd2)
    set_tests_properties(unit_bwd2 PROPERTIES LABELS "unit;memcheck")

    add_executable(i76_unit_bwd2_commands tests/test_bwd2_commands.cpp)
    target_link_libraries(i76_unit_bwd2_commands PRIVATE i76_core)
    add_test(NAME unit_bwd2_commands COMMAND i76_unit_bwd2_commands)
    set_tests_properties(unit_bwd2_commands PROPERTIES LABELS "unit;memcheck")

    # The source-built fixture is a tiny synthetic BWD2 stream. It is created in
    # the build tree; no binary game resources or generated files are committed.
    add_test(NAME functional_bwd2_fixture_setup COMMAND i76_unit_bwd2_commands
        --make-fixture "${CMAKE_CURRENT_BINARY_DIR}/bwd2-fixture")
    set_tests_properties(functional_bwd2_fixture_setup PROPERTIES
        LABELS "functional" FIXTURES_SETUP bwd2_fixture)
    add_test(NAME functional_bwd2_directory COMMAND i76 --headless
        --command "resource mount ${CMAKE_CURRENT_BINARY_DIR}/bwd2-fixture"
        --command "level inspect miss16/m06.msn" --command "asset stats")
    set_tests_properties(functional_bwd2_directory PROPERTIES
        LABELS "functional" FIXTURES_REQUIRED bwd2_fixture
        PASS_REGULAR_EXPRESSION "BWD2 miss16/m06.msn bytes=")
    add_test(NAME functional_bwd2_shell COMMAND i76 --shell
        --command "resource mount ${CMAKE_CURRENT_BINARY_DIR}/bwd2-fixture"
        --command "level inspect miss16/m06.msn")
    set_tests_properties(functional_bwd2_shell PROPERTIES
        LABELS "functional" FIXTURES_REQUIRED bwd2_fixture
        PASS_REGULAR_EXPRESSION "BWD2 miss16/m06.msn bytes=")
    add_test(NAME functional_bwd2_missing COMMAND i76 --headless
        --command "level sections nonexistent.msn")
    set_tests_properties(functional_bwd2_missing PROPERTIES LABELS "functional" WILL_FAIL TRUE)

    add_executable(i76_unit_level_commands tests/test_level_commands.cpp)
    target_link_libraries(i76_unit_level_commands PRIVATE i76_core)
    add_test(NAME unit_level_commands COMMAND i76_unit_level_commands)
    set_tests_properties(unit_level_commands PROPERTIES LABELS "unit;memcheck")

    add_executable(i76_unit_line_editor tests/test_line_editor.cpp)
    target_link_libraries(i76_unit_line_editor PRIVATE i76_terminal_input)
    add_test(NAME unit_line_editor COMMAND i76_unit_line_editor)
    set_tests_properties(unit_line_editor PROPERTIES LABELS "unit;memcheck")

    if(UNIX)
        find_package(Python3 COMPONENTS Interpreter QUIET)
        if(Python3_Interpreter_FOUND)
            add_test(NAME functional_terminal_keys
                COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_SOURCE_DIR}/tests/test_terminal_pty.py"
                    "$<TARGET_FILE:i76>")
            set_tests_properties(functional_terminal_keys PROPERTIES
                LABELS "functional" TIMEOUT 20)
        endif()
    endif()

    add_executable(i76_unit_resources tests/test_resources.cpp)
    target_link_libraries(i76_unit_resources PRIVATE i76_assets)
    add_test(NAME unit_resources COMMAND i76_unit_resources)
    set_tests_properties(unit_resources PROPERTIES LABELS "unit;memcheck")

    add_executable(i76_unit_level tests/test_level.cpp)
    target_link_libraries(i76_unit_level PRIVATE i76_core)
    add_test(NAME unit_level COMMAND i76_unit_level)
    set_tests_properties(unit_level PROPERTIES LABELS "unit;memcheck")

    add_test(NAME functional_level_lifecycle COMMAND i76 --headless
        --command "level prepare demo.level" --command "level status"
        --command "level activate" --command "object list"
        --command "asset stats" --command "level unload" --command "asset stats")
    set_tests_properties(functional_level_lifecycle PROPERTIES
        LABELS "functional;memcheck" PASS_REGULAR_EXPRESSION "level unloaded")
    add_test(NAME functional_level_shell COMMAND i76 --shell
        --command "level inspect demo.level" --command "level load demo.level"
        --command "object list" --command "level unload" --command "level status")
    set_tests_properties(functional_level_shell PROPERTIES
        LABELS "functional;memcheck" PASS_REGULAR_EXPRESSION "level loaded=none")
    add_test(NAME functional_level_missing COMMAND i76 --headless
        --command "level load nonexisting.level")
    set_tests_properties(functional_level_missing PROPERTIES LABELS "functional" WILL_FAIL TRUE)

    add_executable(i76_unit_world tests/test_world.cpp)
    target_link_libraries(i76_unit_world PRIVATE i76_world)
    add_test(NAME unit_world COMMAND i76_unit_world)
    set_tests_properties(unit_world PROPERTIES LABELS "unit;memcheck")

    add_executable(i76_unit_world_commands tests/test_world_commands.cpp)
    target_link_libraries(i76_unit_world_commands PRIVATE i76_core)
    add_test(NAME unit_world_commands COMMAND i76_unit_world_commands)
    set_tests_properties(unit_world_commands PROPERTIES LABELS "unit;memcheck")

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
    target_link_libraries(i76_unit_terminal PRIVATE i76_core i76_terminal_input)
    add_test(NAME unit_terminal COMMAND i76_unit_terminal)
    set_tests_properties(unit_terminal PROPERTIES LABELS "unit;memcheck")

    add_test(NAME functional_world_commands COMMAND i76 --headless
        --command "object spawn vehicle scout" --command "object spawn marker checkpoint"
        --command "object list" --command "object inspect 1:1")
    set_tests_properties(functional_world_commands PROPERTIES
        LABELS "functional;memcheck" PASS_REGULAR_EXPRESSION "object handle=1:1 kind=vehicle name=scout")
    add_test(NAME functional_world_session COMMAND i76 --shell --command play
        --command "object list" --command "object spawn scenery road" --command "object inspect 3:3"
        --command menu --command play --command "object list")
    set_tests_properties(functional_world_session PROPERTIES
        LABELS "functional;memcheck" PASS_REGULAR_EXPRESSION "objects=2")
    add_test(NAME functional_world_invalid COMMAND i76 --headless --command "object inspect 0:0")
    set_tests_properties(functional_world_invalid PROPERTIES LABELS "functional" WILL_FAIL TRUE)

    add_test(NAME functional_resource_mounts COMMAND i76 --headless
        --command "resource list" --command "resource cache" --command "resource unmount 1"
        --command "resource list" --command "asset stats")
    set_tests_properties(functional_resource_mounts PROPERTIES
        LABELS "functional;memcheck" PASS_REGULAR_EXPRESSION "resource mounts=0")
    add_test(NAME functional_resource_busy COMMAND i76 --headless
        --command "level prepare demo.level" --command "resource unmount 1")
    set_tests_properties(functional_resource_busy PROPERTIES
        LABELS "functional" WILL_FAIL TRUE)

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
