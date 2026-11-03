# Interstate '76 reconstruction — portable runtime architecture

**Status:** Proposed architecture for maintainer discussion and acceptance. This document describes the target design, **not** functionality currently implemented. See [CODING_STANDARDS.md](CODING_STANDARDS.md), [STYLE_GUIDE.md](STYLE_GUIDE.md), and [TESTING.md](TESTING.md).

## Objectives and non-objectives

- One portable executable with a separately testable core library and backend targets. Linux (GCC/Clang, GDB/TUI, Valgrind/Helgrind) is first-class; Windows build/test is continuous; other platforms can be added without rewriting the core.
- Logical gameplay reimplementation using **user-supplied original resources**. Preserve resource and mission/FSM behavior as required, not original process/module boundaries or retail memory allocation.
- Operation without a desktop, GPU, sound card, input hardware, terminal, network, or licensed assets for synthetic tests. GUI, line-mode CLI, terminal/TUI and batch/headless execution are **host choices**, not properties of the simulation.
- Every output channel has a usable **null/discard sink** and **recording/mock sink**, in addition to optional concrete devices or external endpoints. The null backend is a permanent supported operating mode, not a temporary stub.
- Modular **compile/link boundaries**; no dynamic plugin system until a concrete use case requires it. Platform library handles never leak into simulation headers.
- No single all-purpose Platform abstraction or overengineered interface hierarchy. Ports correspond to actual effects, not a speculative service catalogue.

## Dependency direction

    app / executable
      |
      +-- host: batch/headless | cli | tui/notcurses | gui/sdl
      |     +-- input provider: scripted | terminal | SDL input
      |     +-- real-time clock provider
      |     +-- resource/file providers
      |     +-- output sinks: scene | audio | diagnostic | telemetry | persistence | net
      |
      +-- portable engine core
            +-- resource decoders and canonical asset definitions
            +-- world-object registry and stable generation-checked handles
            +-- mission FSM interpreter and host commands
            +-- vehicle physics, AI, combat and gameplay state
            +-- fixed-step clock, deterministic RNG, command dispatcher
            +-- semantic scene frames, audio events, debug draw, state snapshots

Backends may depend on the portable core's small **data-contract** headers. The core MUST NOT import backend, SDL, terminal, native window or graphics API headers. A frontend MUST NOT mutate the world directly: it submits validated commands at defined simulation boundaries.

## Separate concerns: host, frontend, platform services, backend

**Host:** Owns application lifetime, command-line mode, initialization/shutdown, pumps events and decides whether presentation is attached. A noninteractive host is fully supported. The core can outlive any single frontend or output sink.

**Frontend:** Owns interaction and presentation policy, not simulation truth. A graphical UI, terminal UI (e.g. Notcurses), line-mode console, or scripted test client may attach to the same command and inspection services. No frontend is mandatory.

**Input ports:** Normalize raw keyboard, joystick, command line, terminal and scripted input into timestamped/ordered typed commands and controls. The simulation sees logical actions (throttle, steering, pause, etc.), not SDL scancodes or terminal escape sequences.

**Clock port:** Supplies monotonic host time. The app accumulates elapsed real time and requests zero or more **fixed simulation steps**, while rendering/audio presentation may operate at a separate rate. A headless test supplies time explicitly; deterministic simulation code never reads the wall clock.

**Resource/file ports:** Supply streams/bytes for asset reading, installation discovery and user data. In-memory providers enable synthetic fixtures. Persistent saves use an explicitly owned **write output port** with null/recording implementations; don't silently discard user saves in normal interactive mode.

**Output sinks:** Consume published immutable-for-frame data/events without mutating the simulation. They have separate initialize/shutdown boundaries and report failures to the host. Sink failure must not corrupt game state; a meaningful mandatory save/network failure is surfaced as an operation failure, not silently ignored.

## Every output has a null and recording alternative

| Channel | Null/discard behavior | Recording/mock behavior | Later concrete backend |
| --- | --- | --- | --- |
| Scene/render | Consume/discard scene frames; no GPU or window | Store typed camera/object/material/debug submissions | SDL_GPU (Vulkan/D3D12/Metal) or future renderer |
| Debug draw | Discard geometry/text annotations | Record lines, boxes, labels by tick | Graphics overlay, terminal visualization |
| Audio | Consume/discard sound events | Store ordered sound IDs, positions, gain and timestamps | SDL3 audio or OpenAL Soft |
| Diagnostics/logging | Filter/discard after optional fatal emergency stderr | Capture structured levels, codes, source/tick | Stderr, file, TUI panel |
| Telemetry/tracing | Discard events without extra dependencies | Capture stable per-tick trace snapshots | CLI dump, debug UI, external inspect tool |
| Persistence writes | Reject or intentionally discard in explicitly selected test mode | Capture writes and verify path/payload | Filesystem atomic writes |
| Network outgoing | Discard only in explicit offline/test mode | Capture ordered payloads and destinations | UDP/session backend when implemented |
| UI-facing state | Consume/discard display snapshots | Capture menus/status/object inspector data | Notcurses, line-mode CLI, SDL window |

**Semantics:** “Null” means no physical output, not that an otherwise successful save or network send should be falsely reported as durable. Host-level policy decides whether a particular channel is required for a requested operation. Recording sinks must expose the same sequence of submitted events as device sinks; tests validate their contents and order.

A null *input* source, scripted input, in-memory file provider and manual clock are similarly required for device-free tests even though they are sources rather than sinks.

## Windowless and terminal operation

Window and presentation surface are optional runtime attachments. Do not call `SDL_Init(SDL_INIT_VIDEO)`, create a window, query a display server, or initialize a GPU device merely to construct a world, load a mission, run the FSM, or access the developer console.

The **line-mode CLI** can run interactively on a terminal or noninteractively from stdin/scripts, and can produce machine-readable state traces.

A **TUI frontend** may use Notcurses or another terminal library. It consumes the same status/object/mission snapshots and command service as the GUI. It may optionally visualize projected maps or debug geometry using glyphs/pixels where terminal capabilities permit. It is **not** required to reproduce the full 3D renderer or depend on a window. Avoid equating terminal UI presentation with the GPU render backend.

The **graphical frontend** can use SDL3 for window/input and initially SDL_GPU for graphics, but the engine does not see SDL types. Initialize SDL subsystems only when the selected backend needs them; do not make SDL globally mandatory for headless execution.

## C++20 contracts: plain data and narrow calls

The maintainer's hand-written `i69` example already has a useful data-flow pattern: input commands/controls into the core, and camera/render/audio/debug packets out. Keep that structure but make timing and output routing explicit:

    host reads input/clock -> input_frame and ordered command batch
      -> runtime_step(runtime_state, fixed_step_input, frame_output)
      -> update world and mission FSM
      -> emit scene_frame, audio_events, debug_draw, diagnostics, snapshots
      -> host sends frames/events to selected sinks

These are conceptual function and type names, not yet compiled source. Separate event queues from frame snapshots: some effects (e.g. gunfire sound or a one-off save) must not repeat on redisplay of a frame. Use explicit event IDs or tick/sequence values where needed.

Data contracts should use `lower_snake_case` structs and fixed-width fields for IDs and serialized data. Dynamic lists can use `std::vector`, text `std::string`, and borrowed views `std::span`/`std::string_view`. Stable generation-checked handles are object identities. Backend pointers, native windows, files and GPU handles are private to backend state.

Avoid a virtual function per world object or per geometry primitive. A small backend interface (free-function callbacks, a cohesive backend class, or an explicit function table) is appropriate **only at subsystem boundaries**. Do not prescribe a dispatch mechanism until a concrete first backend is implemented and measured/debugged.

## Lifecycle and threading

1. Construct the host and select providers/sinks from CLI/config; headless defaults to null device sinks.
2. Initialize required providers/sinks independently; failures unwind only successfully initialized dependencies, reporting the error to the host.
3. Initialize core application state; load/unload sessions explicitly; retain the app and registered developer commands across mission changes.
4. For each host iteration collect ordered inputs, accumulate real time, run zero or more fixed simulation steps, and publish new frames/events to attached sinks at their own cadence.
5. At shutdown, close the session, flush required external operations, explicitly shut down sinks/providers, then destroy core/host resources. Validate repeat startup/shutdown under Memcheck.

Initially single-thread the simulation and command application. Any UI/resource/network worker must communicate via immutable batches or explicit queues; commands are consumed at a fixed simulation boundary. Helgrind and TSan exercise queues, shutdown, resource handoff and backend interactions once threading exists.

## Module boundary and build targets

Proposed as separate static libraries/targets, with target creation as needed rather than empty scaffolding:

- `i76_core`: types, handles, deterministic time and commands, error/diagnostic contracts.
- `i76_assets`: original archive/resource readers, normalized internal resources and file-provider interface.
- `i76_world` and `i76_mission`: world/actor registry, mission FSM, host action dispatch.
- `i76_simulation`: vehicles, physics, damage, AI, fixed-step updates.
- `i76_presentation`: renderer-neutral scene state, debug geometry, audio and UI snapshots.
- `i76_host`: application loop, mode selection, explicit lifecycle and sink/provider wiring.
- Backend targets: `i76_backend_null`, `i76_backend_recording`, later `i76_backend_sdl3` and optional `i76_frontend_notcurses`.
- `i76`: final launcher executable. Core libraries remain linkable by CTest integration/functional test binaries.

Modules must not turn into separate processes merely to enforce layering. Compile/link portability and testing are the immediate objective, not binary/plugin ABI stability.

## Testability acceptance gates

1. The core initializes/steps/shuts down with **no window, display server, terminal, audio device, GPU or retail assets**.
2. Each output channel's null and recording sink is exercised in unit tests, including initialization, failure, repeated teardown, and event/content equivalence where applicable.
3. A deterministic synthetic scenario produces identical world/FSM state and ordered events under null versus recording/real adapters. The null sink must not change gameplay; recording sinks retain observable output for assertions.
4. CLI and scripted tests can create/destroy the core and enumerate its diagnostic state without SDL video initialized.
5. Portable tests compile and pass on Linux and Windows. Linux sanitizer, Memcheck and conditional Helgrind coverage follow [TESTING.md](TESTING.md).
6. A terminal frontend can be added without modifying world/mission/simulation logic or introducing any unconditional window dependency.

**Initial framework scope:** core lifecycle, injected time, typed commands, no-window headless host, null and capture sinks for the output types it introduces, and synthetic functional tests. Full SDL renderer, Notcurses interface, audio hardware and networking come later behind the already-tested contracts.
