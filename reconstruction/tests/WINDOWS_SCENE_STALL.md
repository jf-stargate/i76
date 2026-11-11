# Windows scene test stall

The scene and terrain test fixture writers indexed four characters from every
`std::string_view` tag. Their `"REV"` argument has size three. Reading `tag[3]`
violates the view's bounds even when a string literal's backing array happens
to contain a zero there. This is undefined behavior in the test fixture writer.

## Evidence and failing phase

- Historical PR #139 run [42140488100](https://github.com/jf-stargate/i76/actions/runs/42140488100),
  Windows job 127639353686: MSVC 19.44 compiled successfully; CTest passed
  `style_cpp_sources`, started `unit_retail_scene`, then was cancelled after
  approximately 19 minutes without test output.
- Latest main reconstruction run at bootstrap,
  [42149558305](https://github.com/jf-stargate/i76/actions/runs/42149558305),
  Windows job 127669184835, shows the same sequence. Its five Linux jobs passed.
  Current main has the same affected fixture writers.
- On Linux with GCC 16.2 and `-D_GLIBCXX_ASSERTIONS`, both `unit_retail_scene`
  and `unit_terrain_scene` abort immediately on the string-view bounds check.
  GDB identifies `add_chunk(tag="REV")`, index 3, called by `add_revision`,
  `make_mission`, `add_assets`, and `test_rejections`.
- The last successful test operation before fixture construction is the
  expected `missing_mission` result from the empty mounted memory store.
  Within construction, the BWD2 header and three bytes `REV` have been appended
  (mission vector length 11). The next operation reads `tag[3]`; the revision
  length and payload have not been appended. No authored scene assets have
  been registered and no successful scene preparation has begun.

The [MSVC 17.14 STL implementation](https://github.com/microsoft/STL/blob/vs-2022-17.14/stl/inc/__msvc_string_view.hpp)
checks `operator[]` against the view's size in Debug and reports an out-of-range
subscript. Microsoft's [CRT assertion documentation](https://learn.microsoft.com/en-us/visualstudio/debugger/c-cpp-assertions?view=visualstudio)
describes the default assertion dialog. A blocked assertion dialog explains
the observed Windows stall, but no live Windows debugger or dialog was captured
in this Linux investigation. The out-of-bounds access is directly reproduced;
the historical runner's UI state is inferred.

Ordinary Linux builds happened to read the literal's backing zero. ASan and
Memcheck need not detect a logical view-bound violation inside a valid array.
This is independent of integer signedness and host path normalization. The
failure occurs before resource acquisition for any authored scene, before
scene activation and before runtime initialization/shutdown. No deadlock or
infinite-loop mechanism is needed to explain this failure. The same helper bug
in `test_terrain_scene.cpp` would be exposed after the first test is repaired.

## Fix and regression coverage

Both fixture writers now copy a tag character only when the index is within
the view; otherwise they emit an explicit zero. This matches the existing
fixture writers in `test_bwd2.cpp` and `test_retail_mission.cpp`. No production
runtime, lifecycle, path handling, workflow, timeout or assertion is changed.

Each affected suite tests exact serialized bytes for a three-byte view backed
by `{'R', 'E', 'V', '!'}`, a full four-byte nonterminated view, and an empty
view. The short-view case detects the bug even without library assertions:
the old writer emits `!` where the expected FourCC requires zero. Existing
scene rejection, resource-lease cleanup, sampling, repeated lifecycle and
headless process tests remain enabled.

## Local reproduction

On the unpatched base, configure and build:

```sh
cmake -S reconstruction -B /tmp/i76-scene-checked -G Ninja \
  -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_FLAGS=-D_GLIBCXX_ASSERTIONS
cmake --build /tmp/i76-scene-checked --parallel 4
ctest --test-dir /tmp/i76-scene-checked \
  -R '^unit_(retail_scene|terrain_scene)$' --output-on-failure --no-tests=error
gdb -q -batch -ex run -ex bt /tmp/i76-scene-checked/i76_unit_retail_scene
```

Both tests fail before the fix. With the fix, run the full CTest suite using
the same checked build. For actual Windows MSVC verification, the accepted CI
commands are:

```powershell
cmake -S reconstruction -B build/windows -G "Visual Studio 17 2022" -A x64
cmake --build build/windows --config Debug --parallel
ctest --test-dir build/windows -C Debug --output-on-failure --no-tests=error
```

The PR records the exact tested head and complete reconstruction CI results.
This host has no runnable Windows/MSVC environment; `clang-cl` alone is not an
MSVC runtime or Windows reproduction.

## Bootstrap and scope

Base commit: `19c755a77db404ba9cb0ab51f307b4261e983aff`, authenticated from
`jf-stargate/i76` default branch `main`. Read the pinned `AGENTS.md`, protocol
1.0.5, access policy, bootstrap, reconstruction merge procedure, documentation
workflow/template and accepted reconstruction standards/testing/style guidance.
Live ruleset 25664125 was active: main PR requirement, trusted `integrity`,
zero formal approvals, thread resolution, no bypass actors, no force pushes.
Open PRs #142 (terrain lattice), #143 and #144 (research) were discovered;
this fix owns a separate `feature/reconstruction-` branch and worktree.

Track: `i76exe`; maintained reconstruction test fix, not an original-binary
research run. Baseline metadata, accepted promotions and resource/terrain
reference documents were inspected for context. No retail executable or
Ghidra database was needed or claimed as an input. No canonical change:
this defect concerns independently authored synthetic test serialization.
No research run, promotion, protected design document or CI policy is changed.
