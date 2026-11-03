# Reconstruction implementation: conditional PR self-merge

This **narrow exception** to the otherwise manual merge rule applies only to ordinary maintained reconstruction implementation. It is not authorization for research, baselines, curated documentation, standards, CI, or governance changes.

Read this file from pinned protected `main`, together with `AGENTS.md` and `access.yaml`. Never use proposed governance from a PR branch to authorize its own merge. The GitHub account is shared across conversations: a branch name or claimed agent identity is not an access-control boundary. The decision depends on changed paths, current protected policy, exact-head checks and explicit scope.

## Activation: fail closed

Autonomous reconstruction merge is **disabled until the human maintainer accepts and merges** the reconstruction standards (#112), initial buildable framework (#114), and unprivileged reconstruction CI workflow (#115), or explicitly reviewed equivalents. None of those activation PRs may self-merge.

Verify the accepted `reconstruction/TESTING.md`, executable CMake/CTest tests, and `.github/workflows/reconstruction-ci.yml` exist on protected `main`. The CI workflow must run on unprivileged `pull_request`, execute candidate code without secrets/write token privileges, and must **not** use `pull_request_target` to execute candidate code. Verify the active `main` ruleset requires PRs and trusted-base `integrity`, and disallows direct pushes. A policy file alone does not configure GitHub settings. If any prerequisite or enforcement is unknown: proposal only.

## Eligible reconstruction PR

All conditions must hold at the instant of merging:

1. Base `main`, same-repository head, branch beginning `feature/reconstruction-` or `reconstruction/`. The exact current protected `main` SHA must be an ancestor of the PR head; reconcile and rerun checks after changes to the head/base.
2. Non-draft, mergeable, no unresolved review conversations, no unaccepted dependent PR. Examine **all changed paths and types**. Every changed path must be strictly inside `reconstruction/`, with **no deletions, renames, symlinks, submodules or generated binary artifacts**. No direct push/force update.
3. Do not modify standards or governing design documents: `reconstruction/CODING_STANDARDS.md`, `reconstruction/TESTING.md`, `reconstruction/ARCHITECTURE.md`, `reconstruction/STYLE_GUIDE.md`, `reconstruction/README.md`, `reconstruction/.clang-format`. Any change to architecture policy, build/test policy, security or release procedures requires explicit maintainer review even if physically under `reconstruction/`.
4. Implement independently authored C++20 runtime, tests or implementation-local documentation conforming to accepted fixed-width types, initialization, lifecycle, portability, mock/null sinks, GDB-friendly design and testing rules. Do not publish retail binaries/resources, GZF, original proprietary code or unsupported claims of original-game behavior. New or modified behavior must have meaningful unit and, where feasible, headless functional tests.
5. All seven named checks must be **successful, completed and associated with the exact PR head SHA**. Verify the trusted GitHub origin and accepted workflow, not merely display names or badges:
   - `integrity`
   - `linux-gcc-ctest`
   - `linux-clang-ctest`
   - `windows-msvc-ctest`
   - `linux-asan-ubsan-ctest`
   - `linux-coverage`
   - `linux-valgrind-memcheck`
   
   Missing, stale, skipped, neutral, cancelled, timed-out or failed checks are **not** passing. Require nonempty unit/functional suites, actual sanitizer, coverage and Memcheck execution. Helgrind is conditional upon supported threaded tests under accepted testing policy.
6. Check diff and test inventory for regressions, untested behavior, bypassed guards or weakened checks. Do not reduce test registration, filter failing tests, disable sanitizers/Valgrind, lower coverage requirements, or sidestep platform validation merely to obtain a green result. Any ambiguous loss of test strength requires human review.

If eligible, the reconstruction implementation agent **may merge that PR via the GitHub pull-request merge API only**. Recheck latest main/head and statuses immediately before calling the API. On a race, changed head, merge failure, missing gate or unclear evidence, stop and submit for maintainer review. Verify the merge SHA is on `main` before reporting completion.

## Always human-owned

Research runs and promotion (`agent/runs/`, `agent/promotions/`, `agent/baselines/`), shared tools (`agent/tools/`), `manual/`, `ref/`, `scripts/`, `snapshot/`, `AGENTS.md`, `agent/protocol/`, `.github/`, root `README.md`, all mixed-scope PRs, and the activation PRs #112/#114/#115 **must still be explicitly accepted by the human maintainer**.

The GitHub ruleset currently only requires `integrity`; this additional condition is procedural unless the maintainer separately deploys stronger GitHub enforcement. No agent is authorized to edit the live ruleset to bypass it. If the rule cannot be checked, it is not satisfied.
