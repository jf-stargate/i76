# Trusted-base publication blocker

Original protected base `9312486b92f15305d814c2bf0551f3cf1e233f48` was checked out untouched in a separate detached worktree. `python3 -B -m unittest discover -s .github/tests -v` runs 38 tests: 37 pass and one fails. Its only failing archive subtest is the already accepted M-TER-01 run `i76exe-20261029T023733Z-bd8eb024`.

`.github/tests/test_schema_versions.py:71` asserts `self.assertIn(version,("1.0.0","1.1.0"))`. That accepted run correctly declares `1.2.0`, supported/preferred by the current schema registry and protocol. The exact failure is `AssertionError: '1.2.0' not found in ('1.0.0', '1.1.0')`. The base worktree remains clean. `evidence/publication_blocker.json` records the private full test-log hash, inputs and results.

The required `integrity` workflow executes this trusted-base test suite before inspecting the PR candidate. Consequently this research PR cannot obtain a green required check against that base, regardless of candidate scientific results. Running the same suite in the candidate also rejects this new 1.2.0 run; this is the same outdated allowlist, not a reason to downgrade supported research schemas or rewrite accepted runs.

Scientific checks pass 3,807/3,807; the trusted-base path/hash/schema candidate inspector passes. Combined `validation.json` is **partial**, 3,844/3,845 (scientific checks plus the 38 trusted-base tests). Test totals are explicitly different scopes; CI is not reported as passed.

Reproduce by checking out the pinned base separately and running the command above. A maintainer-designated governance/tooling proposal must separately reconcile the archive test with the accepted schema registry and obtain human acceptance. This run does not edit that test, governance, or accepted runs. The research PR remains draft; no merge is attempted.
