# Runtime world-object registry — first implementation

This is a deliberately small, independent, **synthetic** world registry. Its `i76_world_handle`
identities and `i76_world_kind` values are not the original Interstate '76 object layout, class
codes, mission actor table, or serialized resource IDs. Original world and FSM behavior will be
integrated from accepted reconstruction research in later milestones.

## Contracts

- The registry is owned by `i76_runtime`, initialized and shut down explicitly, and compiled as
  the separate `i76_world` static library. It has no SDL, terminal, clock, filesystem, or audio
  dependency. The default build remains fully headless.
- Every newly created object and local state is value initialized (`{}`). Numeric positions are
  initially `(0,0,0)` and are only placeholders; there is no physics or rendering transform yet.
- An object handle has a **one-based 32-bit slot number** and a **64-bit generation**. All-zero
  means invalid. Slots are reusable, but generation numbers rise monotonically for the lifetime
  of a registry instance and survive its `clear` / `shutdown` / `initialize` cycle. A failed
  creation returns a zero handle; no other state is modified by invalid input.
- Active objects are enumerated in **creation order**, not slot order. List/lookup operations do
  not mutate the registry or advance simulation. Pointers returned by `i76_world_lookup` are
  borrowed for immediate use only and invalidated by **any registry mutation**, including
  vector growth. Store a handle across frames, not a pointer.
- Capacity is initially 4,096 live objects, with printable ASCII names of 1–64 bytes. Invalid
  kinds, control bytes, zero handles and generation overflow are rejected. The upper bound is
  intentional until allocation profiling and real content establish resource requirements.
- `i76_world_clear` destroys session objects but retains slot storage for reuse, and
  `i76_world_shutdown` releases that storage. Both invalidate all current handles; generation
  history prevents stale aliases on reuse of the **same** registry instance. Handles are not
  designed for persistence across process launches or copying/reconstructing registry values.
- Changes are currently single-threaded and applied synchronously at the shell/console command
  boundary. Threaded mutation and mission/FSM actor references are future work.

## Console inspector

Build from the repository root:

```sh
cmake -S reconstruction -B build/i76-debug -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build/i76-debug --parallel
ctest --test-dir build/i76-debug --output-on-failure
build/i76-debug/i76 --shell
```

Choose **Start test session**. It creates `demo_car` (`vehicle`) and `demo_checkpoint`
(`marker`) without using any retail resources. Then enter:

```text
object list
object inspect 1:1
object spawn scenery bridge
object inspect 3:3
object destroy 3:3
object clear
menu
```

The numeric generations in the example presume a fresh application process. After returning
from a session and starting again, generations advance, e.g. `1:4` rather than `1:1`. Use the
exact handle printed by `object list`; an old handle returns `object handle not found`. `object
list` shows the first 32 entries and counts any remaining entries to bound console output.

The same commands are available in device-free batch mode:

```sh
build/i76-debug/i76 --headless --command 'object spawn vehicle scout' \
    --command 'object list' --command 'object inspect 1:1'
```

The SDL3 shell's **List world objects** menu item uses the same command service; the optional
window also displays the first five object names/handles as diagnostic text. The graphical
frontend remains a basic debug UI, not the game renderer.

For GDB/TUI:

```sh
gdb -tui --args build/i76-debug/i76 --shell
(gdb) break i76_world_create
(gdb) break i76_world_destroy
(gdb) run
(gdb) print game.world.slots
(gdb) print game.world.creation_order
```

## Tests and limitations

`unit_world` covers zero initialization, invalid operations, generation/slot reuse, ordering,
capacity, and reinitialize. `unit_world_commands` covers strict parser validation, real console
inspection, recording diagnostics, and shell session clearing. Process-level functional tests
run the actual executable. CI exercises GCC/Clang, MSVC, ASan/UBSan, coverage, and Valgrind
Memcheck under accepted protocol 1.0.5. Helgrind has no threaded test cases yet.

**Not implemented:** loading original assets or mission object descriptors, full actor/FSM
binding, stable transform updates, game physics, or distributed/multithreaded registries.
