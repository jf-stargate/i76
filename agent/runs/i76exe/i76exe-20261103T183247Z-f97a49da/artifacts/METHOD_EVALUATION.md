# Method evaluation — independent pilot 2

Code organization, calls and shared state support **reviewable source-file hypotheses at LOW to MODERATE confidence**. They do not independently verify original compilation units. Nine candidate fragments assign 41 bounded functions; a forwarding thunk is UNKNOWN. No calibrated accuracy estimate is possible without original objects, a map/PDB with contribution records, or a comparable build with known source membership. Candidate membership and confidence in separation are different judgments: a strongly coupled fragment may still be part of a larger file.

## 1. Does ordering preserve useful locality?

Yes, locally. Consecutive reader helpers share a two-cell serialized-input cursor; three texture wrappers share exclusive scratch; PIX and registered-source lifecycle/accessor families continue beyond the requested endpoints. Function alignment is often 16 bytes, but ordinary gaps range from one to fifteen bytes across both accepted relationships and proposed boundaries. A large gap is not better evidence: the AI update, host dispatcher and interpreter have trailing switch tables (00412C30+, 004144E4+, 004149B8+). The interpreter also has a noncontiguous defined body with a 13-byte interior exclusion. We did not repair or redefine that body.

Ordering is not enough to assign the five-byte 00493150 thunk. It forwards to 00493C10, associated with the later loader storage. Our map fragment is noncontiguous solely because this unresolved thunk is excluded. No hot/cold splitting, COMDAT ordering, identical-code folding, source-level inline expansion or whole-program optimization was independently established for this binary; these are alternative mechanisms, not assumed explanations. The Rich metadata does not resolve them.

## 2. Strongest relationships

The most discriminating observations combine a sustained change of distinctive storage with the surrounding initialization/consumer/teardown pattern. Examples are the texture wrappers' scratch at 0058D908/0C versus PIX arrays at 0058D91C/20, and map/render state versus the zone-loader page-source buffers at B01. Original descriptor table pointers strengthen the loader relationship, while the outside TREV callback limits that argument.

The VM chain is especially clear as a coupled fragment: 005244DC/E0/E4 have users confined to its four bounded functions in the defined-function inventory, and scheduler→interpreter→dispatcher calls join the lifecycle. This is strong *implementation coupling*, but it does not prove C `static` linkage or separation from import/preparation. Indirect accesses through escaped pointers could be absent from direct-reference counts.

## 3. Misleading relationships

- Functional labels are research annotations. 004702D0's key-canonicalizer label conceals an original call to cache eviction; a semantic classifier could assign it incorrectly.
- Resource routes call each other. PIX loading calls the cache, which invokes registration; these are ordinary service dependencies, not file identity. The stateless comparator 00470CA0 is passed by address by both PIX and registered-key routines.
- Shared layout is not shared TU ownership. The imported execution-node layout must cross loading, relocation and execution even if those lived in separate files or a common header.
- Shared diagnostic reporter 0042D5D0, CRT/math calls, pooled `null`, `.pak`, path formats and ordinary numeric constants provide weak discrimination. Writable PE `.data` contains many literals and tables; a writable section flag is not a mutable-global classification.
- Strong state overlap, calls, lifecycle similarity and semantic purpose are often correlated effects of one implementation relationship. They were not counted as independent votes or converted into percentages.
- A missing Ghidra xref is not absence of a callback. The raw retail descriptor values at 004FAE30/40/50 recover three loader callbacks with no entry xrefs in this database.

## 4. Difference from subsystem organization

The accepted functional map groups terrain loading, physics sampling and visible terrain under TER and separates rendering responsibility. Our map fragment retains visible-bounds and final map/render helpers alongside samplers, because the observed interleaving and state overlap resist a clean physics/render cut. It may extend into earlier renderer code, but we do not assign that unbounded region.

The FSM functional umbrella yields tentative import/preparation, tactics and execution fragments, with a LOW boundary after preparation and a credible one-file alternative. RES yields four fragments (cache/API, texture-name wrappers, PIX/PAK, registered sources), while the shared comparator cannot identify their original file ownership. These are hypotheses about old organization, not recommendations for modern reconstruction modules.

## 5. Coverage and unresolved membership

All 42 requested defined entries were examined: 13 terrain, 15 mission, 11 near cache/PIX, three near registered-source loading. Nine candidate fragments cover 41; **one remains unassigned**, 00493150. Functions outside the requested ranges are contrast/context, not assigned by this run. The complete private inventory contains 2,102 defined functions and 235 external functions; those figures are Ghidra database counts, not a claim that every retail routine has been discovered.

## 6. Is whole-executable clustering justified?

Not as an authoritative partition. A whole-program exploratory ranking of candidate pairs could help prioritize manual study, provided it retains unknowns, overlapping alternatives and observable evidence. This pilot does not establish an error rate, objective function, meaningful number of files or reliable stopping threshold. Additional bounded trials should include weaker-state regions and library-heavy code before paying for comprehensive manual assignment. Source reconstruction can use provisional fragments as navigation while retaining original addresses and avoiding irreversible module decisions.

## 7. Measurements that would improve reliability

Highest value: authenticated original MAP/PDB/OBJ/LIB contribution or file records, or a known-source build from the same compiler/linker with measured ordering behavior. The accepted-history artifact-name search found none of those original artifacts; this does not exclude private or untracked copies.

Next: recover data-object extents and escaped pointers, validate callback tables beyond the bounded neighborhoods, track indexed stores and indirect calls, distinguish compiler helper/library contributions, and compare complete initializer/teardown neighborhoods. A controlled function-pair benchmark with held-out known TU membership would be needed to calibrate confidence. A second related executable could support comparative ordering analysis if its build provenance is separately verified; shared addresses/names alone would not supply ground truth.

## Measurement definitions and limits

`group_connectivity.tsv` counts distinct direct caller-entry/callee-target pairs, excluding computed calls and forwarding jumps. Incoming edges are limited to defined-function instruction references; the inventory separately retains unowned callers, entry address-taking, interior incoming references, computed transfers and thunk targets. `direct_calls.tsv` records bounded callsites, so repeated calls there can exceed connectivity counts.

`state_ownership.tsv` uses a reviewed panel of **36 exact referenced addresses**, chosen for structural discrimination. It records whole-inventory users/writers and R/W/A categories. A means Ghidra DATA/address reference, including indexed reads/writes whose effective object is not resolved. Adjacent words of one object are not independent observations; a single cell may represent a large array. Zero selected state for tactics does not mean it accesses no globals: its initialized configuration-record family is evaluated separately in `table_references.tsv`. Counts are descriptive, not a learned clustering score. `literal_evidence.tsv` records a small reviewed diagnostic/format sample; the private capture retains all annotated string references. Unannotated strings and implicit pointer-derived accesses can be missed.

No dynamic behavior was tested. The 100 factual validation checks, six manual positive relationship reviews, four manually reviewed separation pairs and six negative examples validate capture/reference facts and expose alternatives; they cannot certify source-file boundaries.
