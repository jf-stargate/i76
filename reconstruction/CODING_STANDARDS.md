# I76 reconstruction — C++20 coding standards

**Status:** Proposed v0.1.0 for maintainer acceptance. **Scope:** independently authored code under reconstruction/, not original-binary research, historical snapshots, or the agent publication protocol. These are proposed engineering conventions, not claims about the original game's implementation.

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
- Use namespace i76 and narrow named namespaces for modules; never put using namespace directives in public headers.
- Filenames: lower_snake_case.cpp/.hpp; types and enum types: PascalCase; functions, variables, fields, namespaces: lower_snake_case; compile-time constants: kPascalCase; macros, when unavoidable: I76_UPPER_CASE.
- Prefer std::uint32_t, std::size_t and other explicit standard types where width or meaning matters. File-format parsing MUST use exact-width types and explicit byte-order conversion.
- Prefer early validation and simple control flow. Keep functions focused. Avoid hidden mutation in getters. Mark side effects in names or documentation when nonobvious.
- Use auto only when the deduced type is obvious from the initializer or type repetition obscures the operation. Do not hide ownership or conversions behind auto.
- Use named functions for simulation math when operator overloads would obscure control flow. Avoid clever expression templates and user-defined implicit conversions.
- No function-like macros for logic, iteration, allocation, object access, or error propagation. Preprocessor use is limited to guards, portability switches, and tightly justified compile-time configuration.
- Each public header MUST include what it uses; never rely on transitive includes. Keep public headers small and implementation details out of interfaces.
- Apply reconstruction/.clang-format to new C++ files. Four-space indent, 100-column guideline, braces as configured; avoid manual formatting wars.

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

- Expose explicit operations such as app_initialize/app_shutdown, mission_load/mission_unload, resource_open/resource_close, and session_start/session_stop. Name the owner of every persistent resource.
- Do not put OS handles, GPU allocations, network sessions, or mission teardown side effects in surprise destructors. Their release MUST occur at explicit and testable shutdown points. A destructor may defensively assert a resource was released or perform trivial local cleanup, but should not quietly implement the application's state machine.
- Prefer value storage and containers for small owned data. std::unique_ptr may be used sparingly for clear single-owner heap objects; do not build the world-object graph out of unique_ptr chains. std::shared_ptr and std::weak_ptr require a specific documented justification and review.
- Avoid raw owning new/delete in gameplay code. Centralize construction in modules/factories with explicit corresponding teardown. Non-owning raw pointers are acceptable for short-lived access when lifetime is obvious.
- Long-lived application resources, mission resources, and per-frame scratch state MUST have distinguishable owners. A mission unload must invalidate mission handles, clear FSM state, and release mission-owned resources without terminating the app.
- Do not allocate, release, or relocate core simulation state unexpectedly during a frame. Preallocate and reserve when practical; any runtime allocation path MUST be observable and documented.
- Never create mutable globals or side-effectful static initialization for registries, configuration, logging, or game state. Pass contexts explicitly.
- Do not conflate deterministic destructor timing with deterministic gameplay. Scheduling, ordering, RNG, and mutation phases are independently specified below.

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

## 8. Debug builds, quality, and tests

- Default developer debug configuration: full GDB symbols, -O0, preserved frame pointers, no LTO, and symbols for private implementation types. Prefer -ggdb3 when using GCC. Provide a separate optimized build.
- Enable useful warnings on first-party targets (at minimum -Wall -Wextra -Wpedantic for GCC/Clang; appropriate MSVC equivalents). Fix warnings rather than suppressing categories globally. Consider -Wconversion/-Wshadow per target as code stabilizes.
- Provide separate AddressSanitizer and UndefinedBehaviorSanitizer test configurations on supported compilers. Keep sanitizer and ordinary GDB builds separate; do not assume sanitizer results replace direct debugging.
- Add CTest unit tests for containers/ownership contracts, parsers, handle invalidation, mission load/unload, VM execution and ordering, and commands as these modules are introduced. Use synthetic fixtures in public CI.
- Every new public entry point MUST have at least one success-path test and relevant failure-path coverage, unless the PR documents why testing is deferred.
- Favor regression snapshots of *structured* parsed world/VM state and behavior over image-only assertions. Compare against measured retail evidence where available, clearly labeling original instruction, emulation, inference, or approximation.
- No PR should claim a test passed unless it was actually run. Report exact commands, platform/compiler, failures, and untested targets.

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

1. Configure, build, and run a minimal i76 executable in headless mode, linked against a testable core library.
2. Initialize and shut down the application explicitly; demonstrate repeat initialization/shutdown or document the exact lifetime constraints.
3. Parse basic CLI arguments and support help, version, and exit commands with clear errors.
4. Provide a small shared command dispatch interface that a future GUI can invoke; no graphical shell is required for this milestone.
5. Produce GDB-readable state and CTest results; document a working GDB/TUI debug invocation.
6. Create no dependency on proprietary retail resources, original binaries, or the original shell DLL.

**Review boundary:** Accepting this coding standard does not accept the earlier research roadmap's remaining gameplay or original-instruction claims. Implementation choices and reverse-engineering evidence retain separate provenance.
