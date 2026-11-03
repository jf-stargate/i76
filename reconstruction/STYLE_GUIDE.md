# Reconstruction style guidance from the maintainer's i69 sample

**Status:** Proposed conventions based on the user-provided `i69.tar` source sample (reviewed without executing the archive's `a.out` binary). This file records style preferences, not reverse-engineering evidence, a production implementation, or a request to publish the original sample.

## Observed patterns worth retaining

- Types and identifiers consistently use **lower_snake_case**, often with `i69_` prefixes for public data contracts: `i69_frame_input`, `i69_frame_output`, `i69_render_packet_list`. Other internal types are descriptive, e.g. `root_clock`, `sdl_platform`.
- State is explicit in **plain structs** with readable fields and small named operations: `init`, `shutdown`, `reset_session`, `tick`, `clear`, `add_event`.
- Inputs and outputs are **distinct structures**: player controls and commands enter as frame input; camera, render packets, audio events, and debug geometry leave as frame output.
- SDL-specific types and event handling occur in a platform wrapper, not throughout the `i69_core` data contract.
- Functions favor direct branches and early validation instead of hidden control flow. Section headers are descriptive and separated with conspicuous C-style comment rules.
- Fixed-capacity queues and small structures are direct to inspect in GDB. The C++ reconstruction may still use `std::vector` and `std::string` where justified; opacity is the design problem, not the mere presence of standard containers.
- The example uses `#pragma once`, four-space indentation, and mostly left-attached pointer/reference declarations. Both `f(void)` and conventional C++ `f()` are acceptable; do not rewrite for cosmetic reasons.

## Conventions adopted

1. Use `lower_snake_case` for types, functions, fields, enum types and constants; `i76_` prefixes are allowed on public data contracts. Avoid enforced PascalCase names.
2. Prefer plain structs, visible ownership, and explicit lifecycle functions or small methods. No hidden resource teardown, deep object trees, or template-heavy wrappers.
3. Separate state input, state update, and emitted output. Avoid `printf` directly from simulation or parser code: emit structured diagnostics to an injected sink so tests can capture or discard them. Host/frontends decide how to present them.
4. Keep `SDL_*`, terminal, audio and OS calls inside backend implementation files. No platform header in portable engine public headers.
5. Keep large algorithms in `.cpp` when helpful for GDB stepping, despite the sample's header-inline experimentation. Public headers describe data and behavior; tests exercise both.
6. Replace ambiguous `int` and platform-dependent `long` with `std::uint32_t`, `std::int64_t`, etc., subject to the specific exceptions in [CODING_STANDARDS.md](CODING_STANDARDS.md).
7. Treat a frame clock as **host-supplied real-time input** and a **runtime-owned fixed simulation tick**. The sample's direct `steady_clock::now()` calls and variable `dt` are fine as a prototype, but not as the deterministic mission/physics contract.
8. A full output queue should expose an explicit error/overflow result or a documented dropped-event counter. Merely printing an overflow and silently discarding commands is insufficient for deterministic or testable gameplay.
9. Prefer portable format specifiers (`<cinttypes>` macros or type-safe format APIs) rather than assuming `uint64_t` maps to a particular C `printf` length modifier.
10. Keep the code understandable without a debugger-specific presentation framework. A GDB/TUI user must be able to print the principal application, world, mission and frame structures directly.

## Not copied into the repository

No game source, SDL harness, archive entries, or compiled binary from the supplied example were committed. Its prototype algorithms, clock parameters and resource definitions have **not** been accepted as I76 engine behavior. The guidance above reflects only its code style and architectural patterns.
