# Structural model, blind version 1

This model is specified before inspecting either earlier translation-unit pilot. Addresses identify functions; semantic names, strings' text, and manual memberships never enter scores. The analysis is a boundary-ranking experiment, not a translation-unit classifier.

For each cut, take up to three defined functions on either side within the bounded extraction (including one external context function at each end). Compute weighted Jaccard turnover (1 minus intersection/union) for mutable data references, direct call targets, incoming caller identities and literal/readonly data. An empty union contributes zero, not positive evidence. Mutable data means writable nonexecutable memory with an observed WRITE reference anywhere among its whole-program users. Writable data without an observed write remains a separate uncertain class and is not treated as a proven literal. A defined string is a literal even if its segment is writable. Reference ownership is observed, not C linkage.

Mutable objects receive inverse whole-program function-user weights. Other Jaccards are unweighted. Whole-program users include interior references to defined data objects. Undefined storage is resolved at exact referenced addresses; overlapping undefined fields may remain separate. Heap fields, register aliases and unrecognized address arithmetic are not recovered by this proxy.

Build an undirected local graph: a function pair connects if one directly calls/jumps to the other, or if both reference the same observed mutable object. Cross density is cross-cut graph edges divided by possible cross-cut pairs. Adjacent link is 1 if the two functions bordering a cut have such an edge. Baseline score:

`2 * mutable_turnover + call_turnover + caller_turnover + 0.5 * literal_turnover - 2 * cross_density - adjacent_link`.

Turnover supports separation; cross-cut connectivity and immediate adjacency oppose it. Shared callees and callers are correlated with connectivity. The score is ordinal, uncalibrated, and never a probability. Individual positive and negative terms are retained. Distinctive writes inform mutable classification but are not an independent score, to avoid double-counting state. Escapes, callbacks, release relationships and tail-call candidates are retained for manual adjudication; no name-derived lifecycle labels enter discovery.

No physical-gap bonus is permitted. Gaps, noncontiguous body ranges, alignment, embedded tables and padding are extracted and audited separately. Constants are retained as reference-address overlap; numeric immediates and string text are excluded because common compiler constants and pooling are especially confounded. Original callback tables are inspected after ranking and cannot silently alter it.

Sensitivity: independently vary every baseline weight by factors 0.8 and 1.2, and use window sizes 2 and 4. Record rank range and inclusion among the top five over baseline plus these 14 alternatives. A candidate absent from top five in any alternative is called unstable as a top-five choice. Ties break on address. Threshold partitions at scores 1.5, 2.0 and 2.5 are alternative exploratory partitions, never forced file assignments. Edge-window truncation is recorded.

Negative controls are selected mechanically after ranking: the five lowest-ranked cuts, plus largest observed gap and highest-ranked singleton-like weak connection. Manual interpretation must explain false positives and false negatives without changing the frozen model. This deliberately small model is falsifiable by counterexamples and later independent neighborhoods.
