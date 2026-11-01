# Source-oriented semantic map

This is an atlas seed, not recovered original source-file/module boundaries or an implemented modern interface. `SEMANTIC_INVENTORY.json` retains current/result signatures, original addresses, dispositions, field offsets where relevant, source-row evidence, immutable source digests, confidence, relationships, unknowns and conceptual future boundaries. Historical migration rows retain inherited evidence classification rather than claiming a new instruction audit of every inherited assertion.

## TER: borrowed storage and three different queries

`00493080` fills the 16,384-entry pointer grid at `00644380` with the borrowed default page and overlays an 80x80 byte ZMAP at +24,+24. Each page is 128x128 uint16 samples (0x8000 bytes), not the editor's 0x8004 plane. Page lifetime belongs to loader state. Low12 encodes height; high3 material; bit12 remains unknown.

`00493160` reads masked lattice height12. `00493550` independently reads four corners and interpolates bilinearly, using x87 control-word qualifications. `004927B0` chooses a rounded discrete material class. `004931C0` writes a triangle-selected approximate normal and returns the explicit output pointer in EAX; it consumes ftol and approximate-inverse-square-root boundaries. Shared addressing is not proof of source-level calls between these functions. Conceptual future boundary: `TerrainQueries` over a borrowed page view, with explicit rounding and lifetime requirements. No replacement is supplied.

## FSM: import phase, live state and synchronous services

`00410490` imports 0x10BC execution nodes; `00412500` relocates scalar entry index at +10A8 to a live token pointer and installs the synthetic frame. Their Ghidra signatures remain unchanged to avoid a false pre-relocation pointer.

Live node regions: mixed operand/frame workspace +0000..0FFF; separate 40 host words +1000..109F; condition +10A0; token base +10A4; live IP +10A8; frame +10AC; operand cursor +10B0; host cursor +10B4; next +10B8. Local retirement counter/scratch are not persistent node fields.

`004149F0` cooperatively visits nodes in list order. `00414670` executes until explicit yield or restored operand cursor equals node base. `00412CE0` synchronously dispatches host records, normally resets host cursor and advances IP once. Counts, heaps and trailing unresolved words retain their distinctions. Conceptual future boundary: `MissionScript.step` with synchronous service calls and persistent resume state; not a new VM implementation or runtime equivalence claim.

## RES: identity, bytes, index and owners

`0046FFC0` returns retained bytes using conditional PIX-first/loaded-file-first priority. `00470070` owns inline payloads after a 0x24 loaded-file header. `00470B20` returns a slice of a separately retained whole PAK using 0x1C PIX rows and 0x18 PAK-retention rows. `00470340` tests membership only.

`004B2E00` searches 0x30 registered-key rows and returns a selected static 0x10C mounted-source row. `004B3030` handles selected loose/ZFS reads and optional destination/capacity. Size query and name-based release use independent PIX-first precedence. The five structures are separate and remain database-mapping proposals; GEO/TMT owner caches are adjacent consumers, not this payload cache. Conceptual future boundary: retained named bytes with explicit acquisition policy, source selection and release identity. Collision/invalidation/media contracts remain unknown.

## ENG/OBJ compatibility

Existing 0xB0 world nodes, 0x0C class-list nodes, 0x78 active entries and 27x0x34 descriptor table remain intact. `world_node->class_runtime` is polymorphic/opaque. Enrolled and pending lists have different payload roles; the mutable +68 contextual link is not a stable parent. The four exact C regression controls and all prior type definitions survive unchanged.

See CONFLICTS.md before using these groupings as reconstruction input. A future atlas should add producer/consumer relationships and evidence at each unknown boundary rather than infer one common object from matching pointer widths.
