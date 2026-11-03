cmake_minimum_required(VERSION 3.20)
project(i76_reconstruction VERSION 0.1.0 LANGUAGES CXX)

option(I76_BUILD_TESTS "Build unit and functional tests" ON)
option(I76_ENABLE_SANITIZERS "Enable ASan and UBSan" OFF)
option(I76_ENABLE_COVERAGE "Enable GCC/Clang coverage instrumentation" OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(I76_ENABLE_SANITIZERS AND I76_ENABLE_COVERAGE)
    message(FATAL_ERROR "Sanitizers and coverage use distinct build directories")
endif()
if((I76_ENABLE_SANITIZERS OR I76_ENABLE_COVERAGE) AND MSVC)
    message(FATAL_ERROR "These sanitizer/coverage settings require GCC or Clang")
endif()

add_library(i76_core STATIC src/runtime.cpp src/command.cpp)
target_include_directories(i76_core PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
# Keep the default Debug build suitable for GDB/TUI on Linux.
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

add_executable(i76 src/main.cpp)
target_link_libraries(i76 PRIVATE i76_core)

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

    add_test(NAME functional_headless COMMAND i76 --headless --command "step 3" --command status)
    set_tests_properties(functional_headless PROPERTIES
        LABELS "functional;memcheck" PASS_REGULAR_EXPRESSION "ticks=3 paused=false")
    add_test(NAME functional_help COMMAND i76 --help)
    set_tests_properties(functional_help PROPERTIES
        LABELS "functional;memcheck" PASS_REGULAR_EXPRESSION "usage: i76")
    add_test(NAME functional_bad_input COMMAND i76 --command "step -1")
    set_tests_properties(functional_bad_input PROPERTIES LABELS "functional" WILL_FAIL TRUE)
endif()
