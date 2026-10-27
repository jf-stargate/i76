# Provisional translation-unit grouping

The original retail addresses `00437230–00437F88` (vehicle tire/suspension visual compression), followed immediately by `00437F90–004382D3` (class-1 camera-specific basis helper), are consistent with a vehicle-visualization/control-source neighborhood; **file boundary or original `.c/.h` name not proven**. `0045EBD0–0045ECF9` initializes root/child object records; `00493CA0`, `00494C80`, `00494710`, `00495000` are math/vector utility neighborhoods, despite v97's inherited `zone_satellite_map_*` naming. The two known call sites `00406D40` and `00407236` lie in camera update callbacks.

The fact that `00437F90` reads class-1 runtime and writes global smoothing state is evidence against its older `effect_target_bounds_query_helper` label. No Ghidra baseline or canonical symbol was renamed. Retain all original VAs in future reports; avoid invented original source-unit names.
