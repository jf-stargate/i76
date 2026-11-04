# Retail HZD horizon manifests

Evidence: binary-static on authenticated retail EXE/v100, plus archive-authenticated retail corpus. This is a research candidate, not a promoted manual or an end-to-end execution result. Source identities and exact paths are in `../evidence/corpus.json` and `../manifest.json`; reviewed original instructions and constants are in `../evidence/`.

## Observed wire profile

All **74** available HZD logical resources, **33** distinct SHA-256 payloads, are **224-byte ASCII text**. Every payload has sixteen records of twelve filename bytes followed by CRLF (`0d 0a`), including the last record. Record i starts at `14*i`, filename occupies `[14*i,14*i+12)`, CR is +12 and LF is +13. No signature, count, version, binary prefix, terminating NUL, comment, numeric parameter or other trailing content is present. Extensions are `.MAP` in the corpus. These are logical texture names; their literal MAP files need not exist.

```
manifest = record * 16
record   = name CR LF
```

The original parser does not enforce this grammar or twelve-byte names. Sixteen is its fixed destination/load loop bound, corroborated by these files; it is not proof about every historical HZD. No alternative stock layout was found. Names/record order are serialized; texture pairs, geometry, palette and mode flags are not serialized in HZD.

Duplicates are meaningful slots: 32 files have eight unique names repeated in the second half, 42 have sixteen unique names. Empty records and blank lines were not observed. M15 in both mission modes has an empty **WRLD HZD field**, which disables horizon initialization; it is not an empty HZD specimen. Do not deduplicate sixteen runtime slots into eight merely because some stock files repeat.

## Exact retail scanner behavior

`00401546/4b` copies six bytes from `004c20d0`: `20 2c 09 0d 0a 00`. Its delimiters are **space, comma, tab, CR, LF**, followed by the CRT string terminator. IAT entries independently resolve to `strpbrk` (`004bc290`) and `strncpy` (`004bc28c`); see `parser_constants.json`.

After acquiring the resource, the **first** token begins at payload byte0 with no leading-whitespace skip. `0040159a` finds the first delimiter. `004015b7` subtracts the input pointer from that result and `004015c0` copies that many bytes to a stack buffer. There is no null-result test or bound on the difference. `004015a2..b1` clears **255 bytes**, not the full annotated 256-byte local, before that copy. The original does not explicitly append NUL after copying. Normal twelve-byte corpus tokens remain terminated by the clear.

`004015dc..f8` scans that local until NUL and copies the token **including its NUL** into the next runtime record, advancing destination by 24 bytes. The runtime name area is inferred to be 16 bytes from its adjacent pair at +16; the original copy enforces neither that capacity nor even the full record size.

For subsequent tokens `004015fc` starts **one byte after the prior delimiter**. `004015ff..00401637` advances until the character-class result masked with **0x103** is nonzero. It selects `_pctype` table access when `__mb_cur_max <=1`, otherwise imported `_isctype`. This is the Microsoft CRT alphabetic-class convention, not an arbitrary whitespace or digit skip. Exact predicate and imported names are binary facts; locale-dependent membership was not measured. [Microsoft's CRT documentation](https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/isalpha-iswalpha-isalpha-l-iswalpha-l?view=msvc-170) describes the alphabetic behavior and locale dependence. Keep the exact mask in any comparison model rather than substituting a host's Unicode classifier.

It then runs another delimiter search and unchecked copy (`0040163f..65`). Thus blank lines or punctuation between records may be skipped; there is no representation of an intentional later empty slot through that scan. A first-byte delimiter instead produces an empty first string and still consumes one slot. A leading digit or underscore in later records may be skipped before an alphabetic suffix; the first token differs. A comma-separated sequence can supply slots, but no escaping, quoting, comments or parameter syntax is recognized. Text after the sixteenth token's first delimiter is ignored; the delimiter search for that last token still occurs. Extra words are possible next texture slots, not verified parameters.

No acquired-length query, end pointer, EOF check, record count parse, token bound, delimiter-null check or encoding validation occurs here. Missing delimiters or fewer than sixteen names can overread, use null-pointer subtraction as a copy length, corrupt the stack/global records, or fail to terminate. These are static consequences; malformed native retail execution was not attempted. The no-op error reporter does not make the scanner safe.

## Independent reader policy

`../scripts/hzd.py` implements the **observed CRLF profile**, deliberately narrower than retail's permissive/unsafe scanner: exactly sixteen nonempty records, ASCII letter first, remaining ASCII letters/digits/underscore/dot/hyphen, at most fifteen bytes per name, CRLF after every record, no excess records or trailing bytes. Total bound is272 bytes. Twelve is the observed width, **not** a coded retail maximum; fifteen is the independent 16-byte runtime-name capacity policy. No fixed extension restriction is inferred from the parser. Any later loader must separately validate extension derivation against its own capacities.

The reader rejects blank/empty entries, bare LF/CR, comma/tab/space delimiters, NUL, non-ASCII/control bytes, paths, oversized names, incomplete/missing records and trailing content. These rejections are safety/support policy, not claims that retail rejects them. Duplicate names remain ordered. `Manifest.raw`/`serialize()` retain all accepted original bytes and case; `offsets` gives record boundaries. Unsupported input is an explicit `FormatError`; callers may preserve the complete source as an opaque inventory item. There are **no identified unknown fields** to silently discard or assign meaning. Raw preservation is tested; no normalized re-encoding is substituted.

Unknown: older releases/layouts, locale changes, intentional hand-authored permissive inputs, complete renderer interpretation and malformed execution outcomes. None prevents safe stock-profile parsing and dependency reporting.
