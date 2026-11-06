# Crossing cases and address ownership

Finding F-CROSS; primary evidence [scan_cases.jsonl](../evidence/scan_cases.jsonl), exact inputs in [results.json](../evidence/results.json). M06 MSN/TER and CD M02 MSN/TER match #141 identities. The M02 mission metadata is the authenticated CD copy, not an assumed alternate local mission. Both corpora are used for native scan probes. `variant=retail` retains every original input byte; nevertheless names ending `unaligned` and `default_cross` are **injected invocation states**, not observed retail regions. `clear`, `neighbor`, `repeat`, `siteN`, and `class_flat` explicitly identify controlled private copies and record mutations/hashes separately.

## What linear crossing means

An X offset beyond127 carries into the next 128-word row of the same backing page, if that address remains in the page. It does not fetch the right-hand ZMAP neighbor. A Z offset beyond127 leaves the 0x8000-byte backing page. For active pages the TER mapping stores page ordinals contiguously, so the next bytes can belong to the next **serialized ordinal**, independent of geographic adjacency. If that ordinal happens to be the geographic neighbor, addresses can coincide by accident. A diagonal overrun combines row carry and allocation crossing. After the final allocated TER ordinal, no terrain bytes are owned. Default backing occupies `[0059C588,005A4588)`; overrunning it enters other PE virtual memory, not a geographic default neighbor.

The bounded observer distinguishes object ownership from virtual mapping. Linux anonymous TER padding and other mapped PE globals do not become valid terrain merely because the CPU could read them. An attempted load outside TER's exact byte length or default's exact 32768 bytes is recorded with `word=null`, then stopped **before executing that load**. For default overruns, the precise unrelated global contents and any resulting hypothetical class decision remain unresolved.

Selected exact M06 examples (size8; first iteration i=7):

| Case | Origin | Load PC | Original address / word | Coordinate-resolved address / word | Outcome |
|---|---|---|---|---|---|
| Horizontal neighbor class3 | 380,9504 | 0049160F | 4006A806 / 000F | 40062706 / 6192 | original leaf; coordinate scan split |
| Vertical neighbor class3 | 288,9596 | 0049160F | 4007034E / 606E | 4007034E / 606E | both split; adjacency happens to match ordinal order |
| Diagonal neighbor class3 | 380,9596 | 0049160F | 40070406 / 0032 | 40018306 / 609B | original leaf; coordinate scan split |
| Repeated page, class3 at next-page top-right | 380,9504 | 004915F7 | 4006A106 / 000E | 4006A006 / 600E | original leaf; coordinate scan split |
| Active to default, cleared classes | 764,9504 | 004915F7 | 40052106 / 00C7 | 0059E58E / 0000 | both leaf, different addresses/values |
| Last TER allocation, retail words | 380,9852 | 0049160F | 40080406 / blocked | 40028306 / 2104 | original out of owned terrain; coordinate scan leaf |
| Default overrun | 124,124 | 0049160F | 005A498E / blocked | 0059C88E / 0000 | original out of default object; coordinate scan leaf |

All original addresses and branches are CPU observations; coordinate alternatives are independent bounded-model results. The 124-case corpus contains five stopped unsafe attempts: three final-TER M06 variants and default overrun in each mission. These are not five executed invalid loads. M02's discovered seam-pair set did not include its final TER ordinal, so this suite does not claim an M02 final-allocation probe.

## Aligned boundaries

For side8, origin local120 scans120..127; for side16 origin112 scans112..127; for side32 origin96 scans96..127. No scan reaches128. The geometric far-edge vertex is at128 and **does** resolve the neighboring page through the ordinary height helper. A root can straddle many pages; the original forces its larger regions to subdivide before class scanning. The same invariant protects active/default seams and repeated references.

This narrows #140's unsupported/default-page concern: initialized defaults and repeated references work for the recovered normal aligned caller. Arbitrary unaligned calls remain observably unsafe or semantically different. The runtime grid, page allocation order and alias semantics agree with #141; no bilinear sampler correction is implied.
