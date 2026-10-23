# Provisional original source grouping — vehicle/resource boundary

**Binary-proven addresses and relationships:** `004AD6F0` top-level VCF constructor; `004AE3A0` VDF VGEO callback; `004B75A0` 100-byte VGEO part-instantiator; `00449680` VTFC owner-texture binding; `0044AB90` TMT header/frames decoder; `0044AC80` creates owner-slot record; `004469A0` GEO cache loader; `00446C90` GEO converter; `004466C0` runtime geometry variant binding/selector. The `00449xxx`–`0044Axxx` material routines share global keyed tables at `00531E20` and `00533FA0`. GEO cache tables are at `0052FB60` and `0052DBA8`.

**Provisional grouping:** `00449680`, `0044AB90`, `0044AC80` may originate from a coherent texture-set/owner-binding module; `004469A0`, `00446C90`, `004466C0` from a geometry-cache/variant module. The proximity and shared globals warrant the hypothesis but do not prove original translation-unit boundaries or source filenames.

**Exclusions:** do not infer that current Ghidra symbol names or memory layouts are original source names. Do not confuse the 100-byte VGEO path `004B75A0` with the unrelated 120-byte `004B7800` path.
