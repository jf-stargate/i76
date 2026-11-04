# I76 reconstruction — C++20 coding standards

**Status:** Proposed v0.4.0 for maintainer acceptance. **Scope:** independently authored code under reconstruction/, not original-binary research, historical snapshots, or the agent publication protocol. These are proposed engineering conventions, not claims about the original game's implementation.

**Primary goal:** A playable, maintainable logical reimplementation of Interstate '76 that consumes original game resources supplied by the player. Reproduce observable resource, mission/FSM, vehicle, and gameplay semantics where needed; do not reproduce retail allocation strategies, shell ABI, object layouts, or binary compatibility merely for similarity.

**Interpretation:** MUST is a baseline requirement; SHOULD is a default that needs a documented reason to deviate. A focused PR can propose an exception. Avoid speculative frameworks and favor working, independently testable vertical slices.

## 1. Build and project shape

- Target **C++20**. Avoid C++23-only features, compiler-specific language extensions, modules, coroutines, and reflection-dependent tooling in the initial implementation.
- Build with **CMake** and CTest. Target Linux (GCC/Clang) and Windows (MSVC or Clang). Keep OS-specific code in platform/ or narrow backend adapters.
- Build the game as **one executable** with a statically linked, testable core library. The graphical shell is application UI, not a separate DLL or executable. Support a headless/console mode from the start.
- The core simulation MUST compile without a graphics window, audio device, installed retail assets, or network connection. Tests can supply synthetic resources.
- Suggested initial layout (created incrementally as needed): reconstruction/src/{app,core,assets,world,mission,simulation,console,platform}, reconstruction/include/i76/, reconstruction/tests/, reconstruction/tools/. Renderer/audio/network modules are added when needed, not as empty scaffolding.
- Do not copy licensed retail executables, assets, Ghidra projects, or private datasets into the public repository. The installed game is a user-provided resource source. Source and original-binary evidence remain separate.

## 2. General coding style

- Prefer **plain data structures and ordinary free functions** over deep inheritance, virtual interfaces, elaborate generic frameworks, or an ECS introduced in advance of actual needs.
- **Do not define or use C++ namespaces in first-party code**, including anonymous namespaces or `using namespace` directives. Place functions and data types at global scope; prefix all externally visible identifiers with `i76_` to avoid collisions. File-private functions and constants use `static`/internal linkage. Standard-library qualification (`std::vector`, `std::uint32_t`, etc.) remains necessary and is not a project namespace declaration.
- Filenames: `lower_snake_case.cpp` with `lower_snake_case.h` headers (use `.hpp` only where justified); types, enum types, functions, fields, variables, and constants: `lower_snake_case`. All public types and free functions **MUST** use the `i76_` prefix; file-local helpers may use descriptive unprefixed names with `static` linkage. Macros, when unavoidable: `I76_UPPER_CASE`.
- Prefer inspectable `struct` state with small explicit methods (`init`, `shutdown`, `clear`, `tick`) or ordinary free functions. Both are permitted; do not mandate PascalCase classes or deep interface inheritance. Keep substantive implementation in `.cpp` when this materially improves debugger stepping and rebuild times.
- **Use explicit-width integer types for all first-party application state, parameters, return values, and persistent IDs:** `std::int8_t`, `std::uint8_t`, `std::int16_t`, `std::uint16_t`, `std::int32_t`, `std::uint32_t`, `std::int64_t`, or `std::uint64_t` from `<cstdint>`. Do not use unqualified `short`, `int`, `long`, `long long`, or aliases like `uint` in first-party interfaces or storage. Use the same rule for local integers where practicable.
- **Explicit exceptions:** `std::size_t` for native memory sizes, array sizes and indices; `std::ptrdiff_t` for native pointer/range differences; `std::uintptr_t` only for genuinely pointer-sized diagnostics/interoperability; `bool` for logical state; and the exact types required by standard-library, OS, or third-party APIs (including the C++ `main` return type). Convert at the boundary with bounds checks; never propagate an ambiguous external type into engine interfaces.
- Give enum classes explicit fixed-width underlying types (for example, `enum class MissionState : std::uint8_t`). Resource IDs, game ticks, packet fields, object handles, serialized lengths and bitfields MUST have deliberately chosen documented widths. No implicit assumption that native `size_t` or pointer size equals retail binary data size.
- File-format readers and writers MUST perform explicit bounded integer reads, signedness checks, endianness conversion, and overflow-safe size calculations. Do not `reinterpret_cast` on-disk/network bytes into a native C++ struct, rely on struct padding/alignment, or serialize raw pointers/container layouts.
- For on-disk or protocol floating-point fields, document IEEE-754 precision, bit width and byte order; use `float` only for explicitly 32-bit IEEE-754 binary32 and `double` only for explicitly 64-bit IEEE-754 binary64 on platforms that pass compile-time checks. Do not assume every architecture has identical floating-point arithmetic behavior.
- Tests MUST exercise integer limits, sign-extension, truncation, alignment-sensitive layouts, byte swapping, and conversion failures with synthetic fixtures. Add compile-time assertions for format-specific widths and platform numeric assumptions where applicable.
- **Zero/null initialization is mandatory for every variable, member, state object, pointer, aggregate, and container at creation.** Prefer `type value{};`, `type* pointer{};`, and brace-initialized members such as `std::uint32_t count{};` and `std::string name{};`; no uninitialized locals, fields, array elements, or object storage. Never rely on uninitialized memory, even if a later path is expected to overwrite it.
- When a meaningful value is available immediately, **directly initialize** the variable from that value rather than default-constructing and assigning purely for ceremony (for example, `const std::uint32_t value{parse_result};`). The invariant is **no uninitialized state**, with zero/null/empty as the default, not that every value must temporarily hold numeric zero.
- Use `T object{};` for value-initialized aggregates and `std::vector<T>(count)` for value-initialized elements. A `std::string{}` and an empty `std::vector{}` are logically empty; do **not** `memset` live C++ objects, containers, atomics, mutexes, or other non-trivial types. Use explicit `initialize`/ `reset`/ `shutdown` transitions to assign meaningful nonzero state.
- Tests MUST verify zero/null initialization, partially failed initialization, reset/reinitialization, and shutdown-state clearing for relevant runtime structs.
- Prefer early validation and simple control flow. Keep functions focused. Avoid hidden mutation in getters. Mark side effects in names or documentation when nonobvious.
- Prefer **C-style variable placement**: declare local variables together at the start of a function, or the start of the smallest meaningful control-flow block, before executable statements where practical. Declare the explicit type and initialize every variable to zero/null/empty (`std::uint32_t count = 0;`, `i76_runtime game = {};`, `void* data = nullptr;`) or directly to a known meaningful value. Avoid `auto`, structured bindings, and declaration-heavy expressions in first-party engine code; introduce them only when a concise, reviewed exception demonstrably improves readability. Do not hoist expensive objects or temporary borrowed references across control-flow boundaries merely for appearance.
- Use named functions for simulation math when operator overloads would obscure control flow. Avoid clever expression templates and user-defined implicit conversions.
- No function-like macros for logic, iteration, allocation, object access, or error propagation. Preprocessor use is limited to guards, portability switches, and tightly justified compile-time configuration.
- Each public header MUST include what it uses; never rely on transitive includes. Keep public headers small and implementation details out of interfaces.
- Apply `reconstruction/.clang-format` to new C++ files. Four-space indentation, a hard 80-column limit, and left-attached pointers (`type* value`) reflect the maintained reconstruction style. Keep historical research and snapshots unchanged.
- Treat the maintainer's handwritten `i69` code as **style guidance, not a code dependency or accepted engine implementation**. Keep its plain structs, consistent lower_snake_case, direct state flow, and lifecycle clarity; use the accompanying [STYLE_GUIDE.md](STYLE_GUIDE.md) for specific observations. Do not import the uploaded source or prebuilt binary into the public repository.



### Line width, signatures, and function banners

- Wrap C/C++ source and public-header declarations at **80 columns**,
  including indentation and comments. Do not shorten identifiers or alter
  literal contents merely to satisfy this rule; split adjacent C++ string
  literals at safe word boundaries when necessary.
- When a function's parameter list would exceed the limit, keep the first
  parameter on the declaration line if possible, then put **each remaining
  parameter on its own line**. Align continuation parameters with the first
  when that stays within 80 columns; otherwise use four-space continuation.
  Use the same convention for declarations and definitions.
- Every function definition in maintained C/C++ implementation and test files
  must have an immediately preceding descriptive banner. Use exactly
  80-character dashed rules, a `//` comment description of one or two
  informative sentences, and a closing 80-character dashed rule. Prefer a
  statement of purpose, ownership, validation, or side effects over
  restating the function's name. This includes file-local helpers and tests.
- Keep the banner adjacent to the signature. The formatter does not generate
  banner descriptions: authors must write and maintain them deliberately.

```cpp
// -----------------------------------------------------------------------------
// Install the prepared level only after its world objects are valid.
// -----------------------------------------------------------------------------
i76_level_result i76_level_activate(i76_world_registry& world,
                                    i76_resource_store& store,
                                    i76_prepared_level& prepared,
                                    i76_active_level& active)
{
    // ...
}
```

## 3. Standard-library containers and strings

- **Allowed and preferred:** std::vector for dynamic contiguous storage; std::array for fixed storage; std::span for borrowed ranges; std::string for owned text; std::string_view for borrowed text.
- std::unordered_map is permitted for lookup and caching; std::map is permitted when ordered keyed lookup is genuinely required. Neither container's incidental iteration order may control simulation outcomes. Keep a separate explicit order when order matters.
- Avoid reimplementing vector, map, hash table, or dynamic string infrastructure without a measured requirement. Prefer a clear wrapper or narrow alias only when enforcing a genuine invariant.
- std::vector growth invalidates pointers, references, and iterators to its elements. Never retain those as persistent object identities. Reserve deliberately when the expected size is known.
- Every std::string_view or std::span MUST have an evident backing-store lifetime. Do not retain a view into a temporary string, resized vector, unloaded asset, or reset mission arena.
- For resource names, document normalization and case-folding. Never assume native filesystem case behavior matches the retail resource namespace.
- Use std::filesystem::path only at host filesystem boundaries; preserve and validate resource identifiers independently of host path rules.

## 4. Ownership, resource management, and lifecycle

The project favors **visible, deliberate lifecycle transitions**. C++ standard containers may own their storage and release it through scope-bound deterministic destruction; that is accepted. Destruction of meaningful *engine state* must not be hidden inside an arbitrary object graph.

- Expose explicit operations such as `app_initialize`/`app_shutdown`, `mission_load`/`mission_unload`, `resource_open`/`resource_close`, and `session_start`/`session_stop`. Name the owner of every persistent resource. **Do not make window creation or SDL video initialization a precondition of app initialization.**
- Do not put OS handles, GPU allocations, network sessions, or mission teardown side effects in surprise destructors. Their release MUST occur at explicit and testable shutdown points. A destructor may defensively assert a resource was released or perform trivial local cleanup, but should not quietly implement the application's state machine.
- Prefer value storage and containers for small owned data. std::unique_ptr may be used sparingly for clear single-owner heap objects; do not build the world-object graph out of unique_ptr chains. std::shared_ptr and std::weak_ptr require a specific documented justification and review.
- Avoid raw owning new/delete in gameplay code. Centralize construction in modules/factories with explicit corresponding teardown. Non-owning raw pointers are acceptable for short-lived access when lifetime is obvious.
- Long-lived application resources, mission resources, and per-frame scratch state MUST have distinguishable owners. A mission unload must invalidate mission handles, clear FSM state, and release mission-owned resources without terminating the app.
- Do not allocate, release, or relocate core simulation state unexpectedly during a frame. Preallocate and reserve when practical; any runtime allocation path MUST be observable and documented.
- Never create mutable globals or side-effectful static initialization for registries, configuration, logging, or game state. Pass contexts explicitly.
- Do not conflate deterministic destructor timing with deterministic gameplay. Scheduling, ordering, RNG, and mutation phases are independently specified below.

## 4a. Platform independence and substitutable outputs

The proposed portable architecture is in [ARCHITECTURE.md](ARCHITECTURE.md). The engine, mission VM, and world simulation MUST NOT require SDL, a window, graphics device, audio device, terminal, interactive input, or a particular operating system to initialize and execute.

- Keep input producers, clocks, file/resource providers, and output consumers behind narrow typed ports. Every external **output** (render/scene presentation, audio, debug drawing, telemetry, diagnostics/logging, persistent-file writes, and later network emission) MUST support a null/discard sink and a test capture/mock sink where the channel exists. A null sink must not alter simulation state or demand a device; a capture sink must expose exactly what was emitted.
- A **window is optional**. SDL3 video and SDL3 GPU initialization belong exclusively to the optional graphical host/backend, never the engine core or the headless/terminal host. A terminal frontend such as Notcurses is an optional adapter alongside a line-mode CLI and graphical UI.
- The engine publishes typed, bounded, owned-or-lifetime-documented frame data, events, and inspectable snapshots. Backends do not receive raw pointers into a mutable world as durable identities. Preserve event ordering and object handles across sinks.
- Keep core game time independent of the OS clock: the host supplies elapsed real time, while the runtime advances an explicit fixed-step simulation clock. Never call `std::chrono::steady_clock::now()` within deterministic world/FSM updates.
- Backend changes MUST be testable: run equivalent deterministic scenarios under null and recording sinks and assert identical world state and event sequence. Add cross-platform compile/functional coverage and device-free lifecycle tests.

## 5. World objects and stable identity

- Use a **generation-checked object handle** (index plus generation or equivalent) as the canonical runtime reference; validate handles on every external lookup. A pointer or vector index alone is not a durable object identity.
- Keep source mission IDs, object names, original class identifiers, and other retail provenance as separate metadata. Do not treat retail addresses or research labels as stable runtime keys.
- Distinguish world identity, class-specific vehicle/AI state, scripted actor identity, and resource ownership. Destroying an object invalidates its handle; script references must observe the correct missing-object behavior.
- The world owns objects. Other subsystems refer to objects through handles or temporary borrows. Document the invalidation rules of every accessor.
- Keep iteration order explicit (for example, a stable ordered registry) and separate from lookup acceleration. Do not allow hash-table layout to dictate updates or callbacks.
- The FSM interface must support actor resolution, missing/destroyed actors, and host-command effects independently of the physical memory layout.

## 6. Simulation, threading, and debugging

- Use an explicit **fixed-timestep update** with documented phases and deterministic ordering. Game logic must not infer frame delta from uncontrolled wall-clock reads.
- Keep RNG state in the game/session context, provide explicit seeds, and record the seed in test traces. Simulation behavior must not depend on hash iteration order, unspecified thread scheduling, or UI polling.
- Commands from the GUI, developer console, tests, or remote tools MUST go through the same typed command/service APIs. Queue state mutations and apply them at defined safe points; never mutate the live world from an unrelated UI/network thread.
- Prefer a single authoritative simulation thread initially. Parallelize only after measuring need and specifying ownership and ordering.
- Maintain an inspectable World/Session/Fsm context. Avoid layers of proxies, compile-time indirection, opaque allocators, and gratuitous inline/template-heavy paths that make GDB/TUI stepping difficult.
- The console should support, in stages: session load/start/stop, pause/resume/step, object enumeration/inspection, FSM trace and breakpoints, and validated configuration overrides. Never let console code bypass world invariants.
- Preserve original behavioral distinctions where evidence supports them (e.g. FSM cooperative scheduling, actor invalidation, object status versus vehicle status); this is **not** a requirement to duplicate retail implementation internals.
- A same-platform deterministic trace is the initial target. Do not claim cross-platform bitwise floating-point parity without tests; compare with appropriate tolerances until stricter parity is established.

## 7. Errors, exceptions, logging, and assertions

- Prefer explicit return statuses/errors for expected failures: missing resources, invalid commands, corrupt inputs, unsupported formats, and failed initialization. Include useful context (resource name, offset, expected/actual condition).
- Do not use exceptions for normal application control flow; **no application-authored throw** in engine operations without a reviewed exception. C++ standard containers may throw on allocation; keep language exceptions enabled initially and catch std::exception/std::bad_alloc at top-level executable and test boundaries, where failures are logged and handled or terminated deliberately. Never silently swallow failures.
- Do not mark allocating functions noexcept without auditing the failure behavior. Do not introduce a general-purpose Result<T> abstraction unless repeated use justifies it.
- Assertions check impossible *internal* invariants, not malformed or hostile user-provided game data. Validate lengths/counts/offsets before allocation and decode; use bounded arithmetic.
- Logging and diagnostics must not alter simulation results. Record state transitions, allocations of note, asset failures, and command execution with enough context to reproduce failures.
- Keep the debugging console's user-visible error reporting separate from internal diagnostic logging.

## 8. Debug builds, automated testing, and quality gates

**Testing is required for every first-party production change.** The detailed test matrix, tool commands, CI plan, and coverage policy are in [TESTING.md](TESTING.md).

- Default debug builds: full GDB symbols, -O0, preserved frame pointers, no LTO, and inspectable private implementation types. Prefer -ggdb3 with GCC. Keep optimized builds separate.
- Enable useful first-party compiler warnings (at least -Wall -Wextra -Wpedantic on GCC/Clang or MSVC equivalents); fix warnings rather than globally silencing them.
- Register every test with CTest and label it unit, functional, threaded, memcheck, or helgrind as appropriate. Public CI must use synthetic fixtures without proprietary retail assets, external services, or graphical devices.
- **Every new or modified public behavior, command, bug fix, nontrivial algorithm, parser or state transition MUST have automated unit-test coverage**, including success, failure and relevant boundary paths. Data declarations and platform shims can be tested via a documented consumer; exceptions require maintainer review.
- **Every new executable feature or cross-subsystem behavior MUST have functional/integration tests wherever feasible.** Prefer exercising the real headless executable with controlled clocks, seeded RNG and synthetic fixtures. When a real device is required, test through a backend double and document an optional real-device check.
- Lifecycle changes MUST test partial initialization failures, cleanup, repeated load/unload and stale handles. FSM and world changes MUST test ordering and destroyed/missing actor references. Functional tests MUST assert meaningful state, not merely process exit.
- Do not disable, silently skip, or tolerate flaky tests to make PRs pass. Document unavoidable platform skips as reviewed exceptions. A compiled-only or skipped test is not a passing test.
- Measure first-party core line and branch coverage in Linux CI once the framework exists. **Initial minimum for new/changed testable core logic: 90% lines and 80% branches**, with reviewed exceptions for hardware-specific glue or unreachable defensive paths. A high coverage percentage alone does not establish correctness.
- Provide separate debug-symbol **ASan/UBSan**, **Memcheck**, and **Helgrind** configurations. Do not run Memcheck on ASan-instrumented binaries; consider ThreadSanitizer separately for threaded targets where supported.
- **Valgrind Memcheck (Linux):** a fast representative memory/ownership/teardown suite on each reconstruction PR; expanded eligible suite nightly or on manual dispatch. Valgrind errors and definite/possible leaks fail with a nonzero exit code. Report still-reachable blocks separately.
- **Valgrind Helgrind (Linux):** once threading exists, PR-gated tests for changes touching shared state, queues, worker threads, or network handoff, and an expanded recurring suite. Tests MUST actually exercise concurrent paths; a passing single-thread test provides no race guarantee.
- No accepted unsuppressed first-party memory errors, definite/possible leaks, or first-party race/lock-order reports. Keep any suppressions narrow, versioned and justified. Do not suppress entire modules.
- CI MUST include Linux and Windows builds/unit/functional tests, Linux ASan/UBSan, coverage, and Linux Memcheck; add Helgrind and TSan for actual concurrency. Missing required tools must fail a CI job rather than silently omit it.
- New/changed code PRs MUST report exact commands, OS/compiler, test counts and failures, coverage, sanitizer and Valgrind applicability, skips, and untested behavior. Never claim tests passed when they were not run.
- Build/test workflows executing PR source MUST use read-only, unprivileged pull_request permissions and no secrets. The existing trusted-base research integrity check is separate; adding a .github/ workflow requires its own reviewed governance proposal.

## 9. Source portability, review, and future C extraction

- Prefer headers with plain structs, enum classes, and explicit function declarations. Keep STL types behind module boundaries when a stable, narrow interface can avoid exposing them, but do not introduce adapters solely to simulate C compatibility.
- Do not introduce complex inheritance, overloaded arithmetic, RTTI-dependent mechanisms, exception-driven APIs, or extensive template metaprogramming without a measured benefit and review.
- A module that naturally uses plain data and procedural algorithms may carry a focused comment such as:
  
      // C_PORT_CANDIDATE: pure fixed-width parser; C++ is used only for vector storage.

  This is an annotation for later evaluation, **not** a promise of immediate C compilation. Do not annotate every function; document the concrete STL and ownership dependencies.
- A future port to C can replace containers and the module boundary incrementally. Do not constrain the initial implementation to binary compatibility or reproducing retail layout.
- Keep commits focused; explain resource ownership, invalidation, thread crossing, and error behavior in changes that introduce them. Changes to accepted research documentation follow the repository's separate review/promotion protocol.
- Generated code MUST be legible to a human maintainer, with meaningful names and straightforward GDB access. Review code paths for unintended allocations, side effects, and hidden lifecycle transitions before presenting it as complete.

## 10. First framework acceptance criteria

The first application-framework PR should demonstrate all of these, using synthetic fixtures only:

1. Configure, build, and run a minimal i76 executable in headless mode **with no display server, terminal, sound card, or input device**, linked against a testable core library.
2. Initialize and shut down the application explicitly; demonstrate repeat initialization/shutdown or document the exact lifetime constraints.
3. Parse basic CLI arguments and support help, version, and exit commands with clear errors.
4. Provide a small shared command dispatch interface for CLI, future TUI, and future GUI frontends; add null and recording sinks for the initial output channels, with identical simulation results.
5. Produce GDB-readable state and demonstrate a GDB/TUI invocation.
6. Include targeted unit tests for all new core/application behavior and functional headless CLI tests, including failure and shutdown paths.
7. Establish CTest, Linux sanitizer and coverage configurations, and a Valgrind-compatible debug build. Run a Memcheck smoke suite; provide labeled Helgrind targets when threading is introduced.
8. Propose the executable reconstruction CI workflow through a separate reviewed .github/ change; do not claim automated enforcement until that workflow is merged and running.
9. Create no dependency on proprietary retail resources, original binaries, or the original shell DLL.

**Review boundary:** Accepting this coding standard does not accept the earlier research roadmap's remaining gameplay or original-instruction claims. Implementation choices and reverse-engineering evidence retain separate provenance.
