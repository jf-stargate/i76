# Authenticated private corpus consistency

Scope: base-game `orig/I76.ZFS` and its already extracted `zfs/resources/` root.
The installed base-game copy has the same observed size/header; Nitro Pack was
located but excluded as a different product/archive specimen. No layout claim
is made for that unexamined archive. No proprietary files, full file identities,
index dumps or resource inventories are included in this run.

Authenticated container: 55,535,506 bytes; SHA-256
`0610541842dfd10464ea02307dec9749ac2b31da4019e1af05d5fcfc55d9020d`; 6,116 directory records. The pinned historical ZFS
reader plus system liblzo2 decoded all 3,516 active PIX/PAK records in memory;
each decoded length/hash matched its extracted file. Compression flags were
0:405, 2:574, 4:2537. Raw records use stored length; their flags' expanded-length
bits are zero, not a claim that the resource is zero length. This authentication
is conditional on that outer ZFS decoder, not a new proof of ZFS internals.

## Coverage

- 1,758 PIX files, 1,758 PAKs, 1,758 valid paired indexes; zero unsupported or
  missing/backing-range failures; zero unreferenced PAKs in this root.
- 23,507 valid rows, 23,243 normalized logical keys.
- 70,149,016 total decoded PAK bytes; referenced union 70,149,016; unused 0.
- Zero overlap pairs, zero nonzero initial offsets, zero descending-offset
  indexes, zero zero-length members. Every PAK is tiled by declared spans.
- 264 duplicate keys / extra rows, all at distinct locations; zero differing
  payload hashes. Six keys have duplicates within a PAK. This does not prove
  original selection or exercise original collision branches.
- Every PIX is CRLF text. No fixed-width serialized binary-record variant
  occurred in this examined root.

| Entry extension | Rows |
|---|---:|
| .geo | 9012 |
| .m16 | 5419 |
| .map | 321 |
| .tmt | 2755 |
| .vqm | 6000 |

The absence of indexed CBK was checked across all rows, not inferred from loose
file absence. There are 53 top-level CBK records. Reviewed `ambient.cbk` is a
registered/ZFS specimen: physical stored offset 10,235,358, stored size 48,395,
flag 2, decoded size 65,540, decoded SHA-256
`794448242904ae4f30bfa7a4bb88c3e2a9d1789850bbd77243ebde2133c7121e`.
It has no PIX member offset. Its decoded bytes matched the extracted file.

## Reviewed bounded examples

These ten rows deliberately include offset-zero and nonzero examples for each
indexed family. Their exact PIX token byte positions, PIX/PAK file hashes and
payload hashes are in `corpus.json`; no payload bytes are printed or committed.

| Logical name | Backing logical PAK | Offset | Length |
|---|---|---:|---:|
| A11_BAS1.GEO | a1flag1g.pak | 0 | 822 |
| A11_FLG1.GEO | a1flag1g.pak | 822 | 848 |
| A2_1SG_1.M16 | a2fnsg16.pak | 0 | 1038 |
| A4_ATK_1.M16 | a4tankc6.pak | 8530 | 8714 |
| MCALT101.MAP | mcaltrpm.pak | 0 | 4104 |
| MCALT102.MAP | mcaltrpm.pak | 4104 | 4104 |
| 1AZ1FTFT.TMT | ambamz1t.pak | 0 | 128 |
| 1AZ1FTRT.TMT | ambamz1t.pak | 128 | 96 |
| 3ABRTMS1.vqm | 3escape.pak | 0 | 2904 |
| 3AUDCON1.vqm | 3escape.pak | 2904 | 2904 |

For example `A11_BAS1.GEO` is absent as a loose file in this extracted root,
yet resolves at PAK offset 0, length 822. Its neighbor `A11_FLG1.GEO` begins at
822, length 848. These are bounded examples, not a full asset listing. Full
reader-vs-independent-seek validation also covers every one of the 23,507 rows;
`examples.json` records its aggregate digest. Duplicate tests use explicit ordinal
selection, so they do not pretend to measure a retail duplicate winner.

## Reproducible aggregate digests

`corpus.json` includes a digest over all authenticated file identity tuples
and another over all per-backing range/union records. `inspect_corpus.py` specifies
canonical JSON encoding (sorted keys, compact separators); ordering is original
ZFS directory order for identities, sorted PIX filenames for range rows. Optional
`--private-details` writes these full tables to a caller-selected private location;
never pass a public run path. They are intentionally omitted from Git.

All historical row tuples/lengths/hash comparisons agreed on this corpus; no
mismatch counters are nonzero. A leading-zero decimal incompatibility was found
using synthetic data and is documented in the handoff. That input spelling is
not a reported mismatch in these retail records.

This work did not execute retail acquire/release or media callbacks. It validates
metadata, decoded-file identities, range arithmetic and returned reference-reader
bytes. It does not establish runtime cache contents, source selection, teardown
safety, all installed mission variants, or fidelity of unrelated asset exporters.
