# v91 provisional source-layout observations

These are *source-file hypotheses*, not recovered original source names or guaranteed translation-unit boundaries. Machine-code addresses are real; grouping is inferred.

1. **Navigation/road-route AI cluster** around `00414BC0–00415Cxx`: `00414BC0` teleport and subsequent path geometry/progress setup at `00415020`, `004151F0`, `00415220`. Proximity here supports a candidate path/navigation translation-unit neighborhood, but these functions have heterogeneous responsibilities and may span several `.obj` files. Confidence: medium for subsystem grouping; low for exact `.c` boundaries.
2. **Vehicle AI follow and buffered control** `0041EF40–004210xx`: follow proximity producer at `0041EF40`, ring dequeue at `0041F8E0`, enqueue at `0041F9C0`, queue drained reader at `0041FCE0`; path initialization and updates at `00420A20–00420FC0`. Their shared AI+`A6C8/A6CC/A6D0` and AI+`A988` fields provide a second, data-flow linkage. Confidence: high subsystem neighborhood, low source TU boundaries.
3. **Mission objectives, UI and allocator neighbors** `0045DA70–0045EBB0`: objective parser/notepad rendering, flags and sound at `0045E960–0045EA90`, followed by objective index setter and **world-object heap allocation/release** at `0045EB70/0045EBA0`. The abrupt topic change around `0045EB70` is a candidate original object-module or linker-order boundary; do **not** group by contiguous location alone. Confidence: moderate for boundary marker; low for precise source unit assignment.
4. **Mission camera independent cluster** `0049D400–0049DDA0`: camera setup, world/map transforms and consuming camera-arrival flag `0049D730`. No evidence it shares a source file with AI navigation merely because of related command names. Confidence: high for separate subsystem, low for `.c` boundaries.

Evidence preserved in the v91 function census, three native decompilation files, displacement candidate scan, and Ghidra symbol-audit record.
