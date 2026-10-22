# Migration state and next acceptance gates

## Indexed in this reviewable proposal

- Indexed 108 legacy reference blobs and 217 legacy script blobs at original Git content SHA.
- Registered 15500 snapshot blobs with top-level tree identities, without copying their contents.
- Added a manual/reference navigation entry point for new researchers.
- Kept existing `ref/`, `scripts/`, and `snapshot/` paths unmodified.

## Deferred to separately reviewed promotion

1. Activate and verify trusted PR integrity CI, branch protection, code-owner approval, and distinct publisher/reviewer identities.
2. Recover original editor v01–v20 report archives and evidence tables. Commit source text or appropriate small derived artifacts **with real provenance**; do not assign historical run IDs retroactively.
3. Inspect legacy snapshot contents for original executables, private content and oversized dumps before moving any files into agent baseline references.
4. Move each vetted current technical reference into `manual/reference/` in small reviewed groups; preserve legacy redirects and hyperlinks until consumers have migrated.
5. Move actively maintained analysis scripts into `agent/tools/`, keeping script hashes, test fixtures and executable/Baseline identity.
6. Exercise a *truly new conversation* with only the repository URL; check whether it reads AGENTS.md, pinned policies, active PRs and accepted baselines without relying on memory.

This PR provides discovery metadata, **not** completed structural migration or authorization to reconstruct the game.
