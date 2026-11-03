# Initial application framework (candidate implementation)

This is an independently authored I76 **application skeleton**, not yet a game, renderer, mission loader, or implementation of the original binary. It reads no retail assets and has no SDL/window/terminal-library dependency.

The initial executable supports `--help`, `--version`, `--headless`, repeated `--command "..."` and `--interactive` (line-mode stdin). Commands: `help`, `status`, `pause`, `resume`, `step <count>`, and `quit`. All simulation steps use an explicitly injected time accumulator or manual step count; no wall clock is read by the portable core. A scene frame is emitted each tick through a null or recording sink. Synthetic audio and diagnostics can also be emitted through independently substitutable ports.

Every framework struct and temporary aggregate starts value-initialized (`{}`); new state receives its nonzero values explicitly at validated initialization. A nontrivial C++ object such as `std::string` is **empty**, not forcibly memset to binary zero. The `runtime` and `runtime_state` fields are directly accessible in GDB/TUI.

## Build and debug on Linux

```sh
cmake -S reconstruction -B build/i76-debug -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build/i76-debug --parallel
ctest --test-dir build/i76-debug --output-on-failure
build/i76-debug/i76 --headless --command "step 3" --command status

gdb -tui --args build/i76-debug/i76 --headless --interactive
```

No display or audio device is required. To run diagnostics on a Linux system with Valgrind and Python3 installed:

```sh
python3 reconstruction/tools/valgrind_ctest.py --build-dir build/i76-debug --tool memcheck
python3 reconstruction/tools/valgrind_ctest.py --build-dir build/i76-debug --tool helgrind
```

Helgrind reports **not applicable** until a real threaded test is added; it does not falsely certify concurrency. Memcheck fails clearly if Valgrind is unavailable. The runner uses CTest's machine-readable test discovery and preserves working directories, timeout and exit statuses. Build separate sanitized or coverage variants:

```sh
cmake -S reconstruction -B build/i76-asan -G Ninja -DCMAKE_BUILD_TYPE=Debug -DI76_ENABLE_SANITIZERS=ON
cmake --build build/i76-asan --parallel
ctest --test-dir build/i76-asan --output-on-failure

cmake -S reconstruction -B build/i76-coverage -G Ninja -DCMAKE_BUILD_TYPE=Debug -DI76_ENABLE_COVERAGE=ON
cmake --build build/i76-coverage --parallel
ctest --test-dir build/i76-coverage --output-on-failure
```

Unit tests cover zero initialization, partial initialization failure, repeated lifecycle, null/recording outputs, fixed-step clock, pause/manual stepping, bounds/overflow, typed command parsing, and malformed command handling. Functional CTest tests invoke the actual headless executable. All fixtures are synthetic.

**CI status:** Existing repository `integrity` is not a C++ build/test job. A separately reviewed `.github/` workflow is still needed to activate Linux/Windows/ASan/coverage/Valgrind PR gates. No such gate is claimed to be active here.
