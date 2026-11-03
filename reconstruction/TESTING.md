# Reconstruction testing and CI policy

**Status:** Proposed alongside [coding standards v0.2.0](CODING_STANDARDS.md). The reconstruction has no build or test binaries yet; these are **requirements for the first implementation PR**, not claims about currently passing tests.

## Test completeness

Every new or modified first-party production **behavior** must have an automated test. This is not one test per source line or trivial getter; it is traceable coverage of public contracts, nontrivial internal logic, state transitions, error behavior, and regressions.

- For each new public API, command, parser, resource operation, allocation/ownership boundary, and simulation algorithm, provide unit tests for normal operation, relevant empty/invalid/boundary inputs, and cleanup/failure propagation.
- Parsing tests include malformed/truncated data, oversized length/count, integer overflow, unsupported version and unexpected resource references.
- Lifecycle tests cover repeat initialize/shutdown, partial-failure teardown, repeat mission load/unload, stale handles, removed actors, and resource invalidation.
- Simulation/FSM tests use fixed seeds, controlled time, explicit ordering, and assertions on resulting state and host-call events. Every fixed bug receives a regression test.
- Every feature involving multiple modules or visible application behavior receives a functional/integration test where feasible, preferably running the actual headless binary with synthetic assets.
- Platform-specific functionality must use testable backend interfaces. When real hardware or original licensed assets are indispensable, add a synthetic test and describe a separate opt-in real-device/retail-data test; proprietary assets never enter public CI.
- Every source module must be exercised by a named test suite. Pure data declarations and portability glue may be covered indirectly with a documented reason; missing tests require an explicit maintainer-approved exception.
- All test binaries and scenarios are registered in CTest. Use labels: unit, functional, threaded, memcheck, helgrind; optional slow and requires_assets. No silent skips, zero-test success, or unexamined flaky tests.

## Proposed CI matrix

| Job | On reconstruction PR | Scheduled/extended | Required condition |
| --- | --- | --- | --- |
| Linux GCC/Clang debug CTest | Yes | Optional | Build, unit and functional tests pass |
| Windows MSVC/Clang CTest | Yes | Optional | Portable build, unit and functional tests pass |
| Linux ASan + UBSan | Yes | Optional | Supported test binaries clean |
| Coverage | Yes | Optional | >=90% line and >=80% branch on new/changed testable core logic, or approved exception |
| Valgrind Memcheck | Fast smoke selection | Full eligible tests nightly | No invalid accesses or definite/possible leaks |
| Valgrind Helgrind | Targeted tests for concurrency changes, once threaded code exists | Full concurrent suite nightly | No unsuppressed first-party races or lock-order violations |
| ThreadSanitizer | New threading features where practical | Expanded concurrency tests | Independent check, not combined with ASan |
| Retail-resource tests | No | Local/opt-in | Verify behavior against user-supplied installation |

The PR gating jobs should be kept fast and deterministic; long/stress runs may be scheduled. Missing required Linux Valgrind installation on a CI runner is a failure, not a success or silent omission. Helgrind should be marked **not applicable** until we introduce meaningful concurrent tests; a passing trivial single-thread program is not evidence of race freedom.

## Developer command interface to implement

These are target commands for the first framework, not currently runnable:

    cmake -S reconstruction -B build/i76-debug -DCMAKE_BUILD_TYPE=Debug -DI76_BUILD_TESTS=ON
    cmake --build build/i76-debug --parallel
    ctest --test-dir build/i76-debug --output-on-failure
    ctest --test-dir build/i76-debug -L unit --output-on-failure
    ctest --test-dir build/i76-debug -L functional --output-on-failure

Provide separate CMake presets for debug, ASan/UBSan, coverage, and **plain debug** (without sanitizer instrumentation) for Valgrind. Provide a script or CTest integration that discovers actual CTest test executables, arguments, working directories, timeouts and labels, and invokes the selected tests under the requested tool; do not hardcode guessed test paths.

### Memcheck options (Linux)

    valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all \
      --errors-for-leak-kinds=definite,possible --track-origins=yes \
      --error-exitcode=99 <registered-test-executable> [args]

Treat Memcheck memory faults, reported definite/possible leaks, and any test failure as CI failures. Still-reachable blocks are reported for review rather than automatically classified as leaks. Expected application caches must be explicitly shut down in lifecycle tests.

### Helgrind options (Linux)

    valgrind --tool=helgrind --history-level=full --error-exitcode=99 \
      <registered-threaded-test-executable> [args]

Concurrent tests must actually start/join threads and exercise cross-thread queues, updates and shutdown. Helgrind can report races, lock misuse, and lock-order errors, but cannot prove absence of all threading bugs, particularly for unsupported atomic/OS synchronization. Use repeated schedules and ThreadSanitizer where supported.

All Valgrind invocations MUST preserve nonzero status, enforce per-test timeouts, produce per-test diagnostic logs, and fail if the required tool is unavailable. A suppression must be narrowly scoped, versioned, explained, and reviewed; never silence an entire subsystem. Keep the debugger/sanitizer/Valgrind builds separate.

## Coverage and acceptance

The **90% line / 80% branch** baseline applies to newly added or changed testable core logic (not a retrospective claim that every line executes). A coverage report is required once the framework exists; document focused exceptions for unreachable guards, external APIs or GUI/device code. Test quality and boundary cases remain mandatory even at 100% coverage.

Every reconstruction code PR must report the changed behavior and corresponding unit tests; functional test coverage or a concrete feasibility exception; exact tested platform/compiler/commands and pass/fail/skip counts; coverage results; ASan/UBSan, Memcheck and Helgrind results or **not applicable/not run** with reasons; and any observed resource-lifetime or simulation-order change.

The first application-framework PR must introduce runnable test targets and Valgrind plumbing, plus the separate reviewed proposal for a reconstruction build/test workflow. The existing GitHub trusted-base research publication-integrity workflow MUST NOT be repurposed to execute untrusted candidate game code. The future reconstruction workflow must use read-only pull_request permissions, no secrets, and explicit maintainer review under .github/ governance. Do not assert any new gate is active until workflow execution and branch protection have been verified.
