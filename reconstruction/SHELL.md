# Application shell baseline (v0.2)

This is an independently authored application host for the Interstate '76 reconstruction. It is **not** the original `i76shell.dll`, a copy of its menus, a mission loader, or a playable game. The `Start test session` entry exercises a synthetic fixed-step runtime with no retail resources.

## Run on Linux

Configure/build the default, fully device-free application:

```sh
cmake -S reconstruction -B build/i76-debug -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build/i76-debug --parallel
ctest --test-dir build/i76-debug --output-on-failure
build/i76-debug/i76 --shell
```

The terminal shell prints a main menu with **Start test session**, **Options**, **About**, and **Exit**. Choose a numbered entry or type its command. Within a test session, `status`, `step <count>`, `pause`, `resume`, `object <action>`, `menu`, and `exit` use the same underlying runtime as `--headless`. `Options` and `About` are placeholders, not wired to original game assets or persistent settings.

A completely noninteractive shell integration test is available:

```sh
build/i76-debug/i76 --shell --command play --command 'step 3' --command status --command menu
```

No terminal UI library is assumed. `--shell` uses line-mode stdin/stdout; Notcurses can be added later as an alternative frontend for the same `i76_shell_view` and `i76_shell_execute` interfaces. The previous headless CLI remains supported:

```sh
build/i76-debug/i76 --headless --command 'step 3' --command status
```

## Optional SDL3 window shell

On Debian sid, install the SDL3 development package, then enable the backend explicitly:

```sh
sudo apt install libsdl3-dev
cmake -S reconstruction -B build/i76-sdl -G Ninja -DCMAKE_BUILD_TYPE=Debug -DI76_ENABLE_SDL3=ON
cmake --build build/i76-sdl --parallel
build/i76-sdl/i76 --shell=sdl
```

Use **Up/Down** to select, **Enter** to activate, **1–8** for direct choices, and **Escape** to return or exit. The window uses SDL3's minimal built-in debug text renderer; this is an early engineering UI, not a final game renderer. It requires only SDL3 video, not SDL_GPU, SDL_ttf, or original assets. When disabled, `--shell=sdl` reports an actionable error; standard headless builds never call SDL.

For display-independent automation of the SDL frontend when SDL3 is available:

```sh
SDL_VIDEODRIVER=dummy SDL_RENDER_DRIVER=software build/i76-sdl/i76 --shell=sdl --shell-frames 2
```

The optional `functional_sdl_dummy` CTest uses that mode. A real Wayland/X11 or Windows window still needs a manual smoke test; dummy-driver coverage is not equivalent to actual display testing.

## Architecture and debug entry points

The shell's entire state is in `i76_shell_state`; its renderer-independent menu is `i76_shell_view`. The terminal frontend receives `std::istream`/`std::ostream` references for test capture and scripting; the SDL frontend depends on SDL3 in a single translation unit. Both dispatch through `i76_shell_execute`/`i76_shell_select`, which forward session commands to the existing engine `i76_execute_command` implementation.

No project namespaces, implicit lifetime management, or native window handles leak into the core. All state fields are value-initialized, with explicit shell and runtime initialize/shutdown. Simulation output still uses the existing null or recording diagnostic, scene, and audio sinks. SDL window creation happens only when explicitly requested.

Suggested GDB/TUI session:

```sh
gdb -tui --args build/i76-debug/i76 --shell
(gdb) break i76_shell_execute
(gdb) run
(gdb) print shell
(gdb) print game.state
```

The shell/test session is deliberately single-threaded; Helgrind is not applicable until threaded behavior is added. The portable shell and terminal tests run under CTest, ASan/UBSan, the repository's line-coverage gate and Valgrind Memcheck. SDL3 is optional and absent from the default CI configuration.

## World-object inspection

The synthetic test session now starts with two debug objects. Use `object list`, `object inspect <slot:generation>`, `object spawn <vehicle|scenery|marker> <name>`, `object destroy <slot:generation>`, and `object clear`. Returning to the main menu clears session objects while preserving handle-generation history. See [WORLD.md](WORLD.md).

## Synthetic level and resource operations (milestone 1)

The `play` menu entry now loads the built-in `demo.level` manifest through the real resource
store and prepared-level lifecycle rather than constructing example objects directly. Returning
to the menu unloads the active level and releases its asset references.

The terminal and headless command services also support `resource list`,
`resource mount <directory>`, `level inspect <name>`, `level prepare <name>`, `level activate`,
`level load <name>`, `level discard`, `level status`, `level unload`, and `asset stats`.
See [LEVEL_LOADING.md](LEVEL_LOADING.md) for usage, limits and the intentionally synthetic file
format. Original `.MSN` and game-archive decoding are not implemented yet.

## Read-only original mission section inspection

The mounted-directory resource provider can now inspect BWD2 chunk inventories
from user-supplied `.MSN`, `.SPC`, or `.LVL` files (`level inspect M06.MSN`),
including uppercase legacy filenames on Linux. `level sections <name>` forces
BWD2 structural inspection without attempting to load a mission. See
[BWD2.md](BWD2.md). Original mission activation remains unimplemented.
