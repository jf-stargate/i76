# Initial application framework

The base C++20 headless runtime is extended by a portable application shell, and now has an explicit synthetic level/resource lifecycle. See [LEVEL_LOADING.md](LEVEL_LOADING.md) for resource providers, staged level loading and unloading, and [SHELL.md](SHELL.md) for execution, terminal and optional SDL3 window setup, menu navigation and debugger commands. The shell does not load original game resources or implement retail `i76shell.dll`.

The original headless runtime and command dispatcher remain available. Runtime state is explicitly initialized, simulated ticks are advanced by manual commands or injected host time, and scene/audio/diagnostic outputs support null or recording sinks. The shell is an independent frontend state machine that shares these contracts. No window, sound card, terminal UI library, or retail assets are required for the default build.

## Linux build and tests

```sh
cmake -S reconstruction -B build/i76-debug -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build/i76-debug --parallel
ctest --test-dir build/i76-debug --output-on-failure
build/i76-debug/i76 --shell
build/i76-debug/i76 --headless --command 'step 3' --command status
```

For memory checks on Linux (Valgrind installed):

```sh
python3 reconstruction/tools/valgrind_ctest.py --build-dir build/i76-debug --tool memcheck
```

Unit tests exercise the runtime's lifecycle/clock/outputs and shell state transitions; functional tests invoke the real CLI. The reconstruction CI workflow runs GCC, Clang, MSVC, sanitizers, coverage, and Memcheck on submitted reconstruction changes. Helgrind remains conditional on the introduction of threaded tests.

The portable application now owns a separate generation-checked world-object registry, with a shell-accessible inspector and synthetic fixture objects. See [WORLD.md](WORLD.md) for handle lifetimes, debug commands and tests.
