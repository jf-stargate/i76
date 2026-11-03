# Interstate '76 — independent reconstruction

**Status:** Proposed new implementation workstream. This directory is separate from the retail executable's reverse-engineering evidence and the agent research protocol.

**Goal:** Build a playable, openly published, modern logical reimplementation that loads the original game's resources from a user-supplied installation. The initial target is one application executable with a reusable core library, headless/console operation, and later graphics, audio, UI, and multiplayer. Binary compatibility with the original game is not an initial requirement.

**Language:** C++20, intentionally procedural and GDB-friendly. Standard containers and strings are permitted. Runtime resource lifecycles, simulation ordering, and object identities remain explicit.

**Before contributing:** Read [CODING_STANDARDS.md](CODING_STANDARDS.md) and the repository's [AGENTS.md](../AGENTS.md) publication rules. The scoped [.clang-format](.clang-format) applies to new C++ source under this directory.

**Current state:** Coding standard proposed first. No application framework, asset loader, or game-runtime implementation is claimed to exist yet.

**Research boundary:** Original executable behavior is documented in [manual/reference](../manual/reference/README.md) and historical [ref/](../ref/). Reconstructed functionality must distinguish verified retail behavior from approximations and must not commit original proprietary resources or private Ghidra files.
