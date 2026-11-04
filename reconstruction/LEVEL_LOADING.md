# Level and resource lifecycle — milestone 1


## BWD2 structure inspection (separate from activation)

A bounded, read-only BWD2 chunk inspector is now available for `.MSN`, `.SPC`,
and `.LVL` resources. It reports byte offsets, sizes, nesting and revision
words, without changing prepared/active level state or claiming retail mission
compatibility. Use `level inspect M06.MSN` or `level sections miss16/m06.msn`
after mounting a directory. Only synthetic `I76LEVEL 1` files can currently be
prepared or activated. See [BWD2.md](BWD2.md) for contract and limitations.

This is an independently authored, tested loading framework. **Only the BWD2
section structure is readable**; original `.MSN` levels cannot yet be activated,
and real vehicle/terrain/GEO formats are not decoded. Those will use the same
resource-provider interface in later milestones. No proprietary game resources
are included in the repository.

## Ownership and stages

| Lifetime | Owner | Contents and responsibility |
| --- | --- | --- |
| Application | `i76_runtime.resources` | Directory/memory mounts, loaded byte cache, explicit reference counts and monotonic handles |
| Prepared level | `i76_runtime.prepared_level` | Parsed synthetic definition and leases for its unique dependencies; never mutates active world |
| Active level | `i76_runtime.active_level` | Current definition and transferred asset leases; its objects live in `i76_runtime.world` |
| Output backends | App/host | Separate scene, audio and diagnostic null/recording sinks; no GPU/window required |

Two implementation libraries keep the responsibilities distinct: `i76_assets` owns the resource
store and directory provider; `i76_level` owns the independent synthetic-level decoder and
prepare/activate/unload operations. The existing `i76_world` library continues to own all runtime
object handles. No project namespaces or native file handles enter the portable state structures.

The **resource store** uses byte-copy leases: an acquired handle contains a one-based 32-bit slot and
monotonic 64-bit generation. Repeated acquisitions of the same logical key share a cache entry and
increase its reference count. Releasing the last lease frees its payload. Mounts remain until
application shutdown. Newer mounts have priority when an asset is not already cached; once cached,
the selected source is stable until the final release. `asset stats` reports cache occupancy,
reference totals and retained byte count. No LRU or background loading is implemented yet.

The **synthetic level loader** has two separate operations. `level inspect <name.level>` reads and parses a manifest and
releases its bytes without requiring any referenced assets. `level prepare` additionally acquires
each unique dependency, retaining leases in `i76_prepared_level`. The current level remains active
if preparation fails. `level activate` constructs a new world registry with the current registry's
last generation, and commits its slots and creation-order array only after construction succeeds.
Thus invalid input, missing dependencies and object-generation exhaustion do not replace the
previous world. Committing the new level releases the old level's leases. `level unload` clears
objects and references but preserves resource mounts. Repeated application shutdown and init
preserve world/resource generation history in the same runtime instance.

The current activation replaces *all* active world objects (including manually spawned debug
objects), not only objects declared by the previous level. A real mission's persistent game state,
transient audio events, and renderer-owned resources require later, separately designed ownership.

## Synthetic manifest format

The milestone-1 manifest is plain ASCII and deliberately **not** BWD2. For example:

```text
I76LEVEL 1
asset common.dat
object vehicle demo_car common.dat
object marker demo_checkpoint
object scenery bridge
```

The first nonempty/comment line must be `I76LEVEL 1`. Subsequent lines are
`asset <logical-resource-name>` or `object <vehicle|scenery|marker> <name> [asset]`.
Whitespace-separated tokens are required; empty lines and `#` comment lines are allowed.
Referenced assets are deduplicated. Validation limits: 64 KiB manifest, 4,096 object definitions,
256 distinct dependencies, and 16 MiB per provider file. Integer conversions and resource paths
are bounds-checked; asset and object data are value initialized. No object transforms, physics,
script binding, or retail format interpretation is implied.

Logical resource paths are ASCII case-normalized with forward slashes. Absolute paths, path
traversal and empty path segments are rejected. The directory provider canonicalizes and checks
paths remain inside its mounted root, including symlink targets. This is a developer-oriented
provider, **not a race-proof security sandbox** for malicious concurrent filesystem mutation.
On Linux, actual directory filenames currently need to match the normalized lowercase keys;
case-insensitive directory indexing for original installs is deferred. Archive providers (ZFS,
PIX/PAK) are not implemented. The accepted [resource acquisition reference](../manual/reference/engine/resource_acquisition.md)
remains the guide for original-game behavior rather than a claim that these simplified cache
semantics duplicate the retail engine.

## Run from the repository root

```sh
cmake -S reconstruction -B build/i76-debug -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build/i76-debug --parallel
ctest --test-dir build/i76-debug --output-on-failure
build/i76-debug/i76 --shell
```

The application automatically mounts a small **memory-only fixture** named `builtin` containing
`demo.level` and `demo_shared.dat`. It has no game-resource dependency. At the main menu:

```text
resource list
level inspect demo.level
level prepare demo.level
level status
asset stats
level activate
object list
level unload
asset stats
```

`play` enters the same synthetic level; `menu` unloads it. `level load <name>` is a convenience
operation combining prepare and activate. `level discard` releases a pending prepared level.
Commands also work via `--headless --command` with no window or terminal required.

To test the directory provider with your own *synthetic* fixture:

```sh
mkdir -p /tmp/i76-fixture
printf 'I76LEVEL 1\nasset sample.bin\nobject scenery bridge sample.bin\n' > /tmp/i76-fixture/sample.level
printf 'example asset bytes' > /tmp/i76-fixture/sample.bin
build/i76-debug/i76 --headless \
    --command 'resource mount /tmp/i76-fixture' \
    --command 'level inspect sample.level' \
    --command 'level load sample.level' \
    --command 'object list' \
    --command 'asset stats' \
    --command 'level unload' \
    --command 'asset stats'
```

The SDL3 shell stays optional; `--shell=sdl` uses the same typed world/level state but does not
assume a graphical renderer can display the synthetic asset bytes. Terminal and headless tests do
not call SDL.

## Tests and next boundary

`unit_resources`, `unit_level`, and `unit_level_commands` cover memory/directory providers,
normalization, reference counts, source precedence, stale handles, traversal rejection,
synthetic parsing, staged/failed loads, unload/reinit and shell command behavior. Existing
runtime/world/shell tests and full CTest functional checks are retained. Linux CI builds GCC,
Clang, ASan/UBSan, coverage and Memcheck; Windows MSVC exercises the same default headless suite.
Helgrind is not applicable while the core remains single-threaded.

Next: a separately tested **BWD2 chunk reader** and a case-insensitive/archived resource-provider
implementation. That work will translate original level records into a typed definition before
attempting retail object construction, terrain allocation, FSM actor binding or executable code.

## Mount inspection and removal

Use `resource list` (or `resource mounts`) to see **stable, one-based mount IDs**,
source type, mount name/root and current outstanding byte-lease references.
`resource cache` displays acquired resource keys, originating mount IDs,
reference counts and retained sizes. The console supports both
`resource unmount <id>` and `resource unmount <mount path/name>`. Directory
paths are canonicalized before lookup, including Windows path variants; numeric IDs
are preferred for paths containing spaces or potentially ambiguous names.
Mount IDs never change when another mount is removed, and new mounts receive
higher IDs after an unload or store reinitialization.

An unmount is refused with `resource still retained` while any resource acquired
from that mount has an outstanding reference (including a prepared or active
level). First use `level discard` or `level unload` as appropriate, then retry.
Removing a mount does not affect any other mount or change the identity of
previously acquired resource handles. The default `builtin` fixture mount may
also be removed, after which `demo.level` is unavailable until the runtime is
reinitialized. Resource lookup still uses the existing last-mounted-first
priority for **uncached** names; already acquired byte leases retain their
original source until the last reference is released.


## Retail semantic inspection (milestone 3)

Retail BWD2 missions remain **read-only**. The new `i76_retail_mission_definition`
is independent of `i76_level_definition` (the synthetic activation format).
After mounting a user-supplied game directory, run:

```text
level summary miss16/M06.MSN
level dependencies miss16/M06.MSN
level terrain miss16/M06.MSN
```

`summary` decodes mission/section revisions, section sizes, counts of recognizable
WRLD, OBJ, RSEG and FSM records, plus ZMAP/ZONE terrain metadata. The ZONE
prefix byte is displayed as opaque; only ZMAP supplies the TER page count. `terrain`
validates all 6,400 ZMAP page indices, resolves the ZONE .TER name **relative to
the mission directory**, checks the page count and byte size, and computes
packed 16-bit sample statistics (height range, surface flag count, and eight
surface-class histograms). `dependencies` reports the one verified dependency
format (ZONE .TER) and its lookup/validation result. WRLD remains opaque:
**its filename-field offsets are not yet established to implementation confidence**.

Parsing and probing acquire/release resource leases within each call; neither
modifies `prepared_level`, `active_level`, the world registry, or simulation.
Missing sidecars are reported as errors for `terrain`, but displayed as a
dependency status for `dependencies`. A failure never overwrites an existing
successful typed definition.

Unit tests and a full-process synthetic MISS16/M06.MSN + M06.TER fixture
exercise the code without shipping licensed game resources. On a local retail
installation, use the three commands above as an opt-in corpus smoke test.
See [RETAIL_MISSION.md](RETAIL_MISSION.md) for detailed format limits.
