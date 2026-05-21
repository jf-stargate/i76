# Interstate ’76 `DATABASE.MW2` Format Reference

**Scope:** `DATABASE.MW2` as used by `i76shell.dll`.  
**Status:** Container format, most image resources, palettes, glyph sheets, credits text, and the final-mission special UI resource are understood well enough for asset recovery.  
**Primary consumers:** `i76shell.dll`, especially shell UI/menu drawing, glyph/text rendering, and shell frontend resources.

---

## 1. High-level summary

`DATABASE.MW2` is an indexed shell resource pack used by `i76shell.dll`. It contains frontend/menu assets, not the main game archive format.

It should not be confused with the game’s `ZFSF` archive format. `DATABASE.MW2` is much simpler: a record count, an absolute-offset table, and raw record payloads.

The uploaded/reference `DATABASE.MW2` has 83 records. The record set is now strongly partitioned:

```text
Records 1–32:   mpack-compressed shell RLE screen/background surfaces
Records 33–35:  shell random-selection resources; exact format unresolved
Records 36–63:  ordinary "1.10" UI overlay / multi-subresource resources
Record 64:      final-mission special "1.10" menu resource, palette-paired with surface record 27
Records 65–71:  glyph sheets
Records 72–82:  WAVE/PIFF audio-ish records
Record 83:      credits text
```

The most important semantic anchor is record 64. The user confirmed that it is a special menu selection screen shown only before the final mission. Binary evidence confirms it is loaded by `10023b60 preload_final_mission_special_menu_record_0x40` and rendered using palette/surface context from record 27.

---

## 2. Container layout

The top-level `DATABASE.MW2` file is a simple indexed pack:

```c
struct mw2_database {
    uint32_t record_count;
    uint32_t record_offsets[record_count]; // absolute offsets from start of file
    uint8_t  record_data[];
};
```

For the uploaded/reference `DATABASE.MW2`:

```text
file size:        8,204,554 bytes
record count:     83
offset table end: 0x150
first record off: 0x150
```

Record IDs are effectively 1-based in the shell API.

That is, shell record ID `1` corresponds to offset table entry `0`, shell record ID `64` corresponds to offset table entry `63`, and so on.

---

## 3. Shell database functions

Important `i76shell.dll` functions:

```text
10007fd0  open_mpack_database
10008240  mpack_database_get_item
10008320  mpack_database_get_item_alloc_or_alias
```

The database object layout:

```text
+0x80  FILE*
+0x84  record_count
+0x88  offset/size table/list object
```

`open_mpack_database` opens `DATABASE.MW2`, reads the record count and offset table, and computes per-record sizes.

`mpack_database_get_item` takes a 1-based record ID, resolves offset and size, allocates or returns a buffer, reads raw record bytes, and returns the payload.

`mpack_database_get_item_alloc_or_alias` appears to apply mpack/LZSS decompression for selected records before returning a usable payload.

---

## 4. Record classification

The current durable record partition is:

| Record range | Class | Status |
|---:|---|---|
| 1–32 | Shell RLE surface/background | Decoded |
| 33–35 | Shell random-selection resources | Format unresolved |
| 36–63 | Ordinary `1.10` UI overlay resources | Decoded indexed |
| 64 | Final-mission special `1.10` UI overlay | Decoded indexed, palette-paired |
| 65–71 | Glyph sheets | Structurally decoded |
| 72–82 | WAVE/PIFF audio-ish records | Classified |
| 83 | Credits text | Decoded text |

Class counts from the v2 resource map:

```text
audio:           11
glyph_sheet:      7
shell_resource:   3
shell_surface:   32
text:             1
ui_overlay:      29
```

Status counts from the v2 resource map:

```text
classified:                         11
decoded shell surfaces:             32
decoded indexed ordinary overlays:  28
decoded indexed palette-paired:      1
decoded structural glyph sheets:     7
decoded text:                        1
unresolved-format shell resources:   3
```

---

## 5. mpack / LZSS-style decompression

Many records are stored compressed. The shell function `mpack_database_get_item_alloc_or_alias` is the important wrapper around ordinary record lookup and optional decompression.

The working decoders used an LZSS-style model with a 0x1000-byte ring initialized to zero. An earlier broad scanner incorrectly initialized the ring and accepted zero surfaces; the corrected broad scanner used the zero-initialized ring and discovered all 32 shell surfaces.

Practical rule:

```text
Use the corrected mpack/LZSS decompression path before interpreting records 1–32 and many shell resources.
```

Known script history:

```text
cgpt_i76_scan_all_shell_surface_palettes_apply_to_110.py
  Initial broad scanner. Do not use; wrong LZSS ring init and accepted zero surfaces.

cgpt_i76_scan_all_shell_surface_palettes_apply_to_110_v2.py
  Correct broad scanner. Scans all records, discovers shell surfaces 1–32,
  extracts palettes, applies unique palette groups to 1.10 overlays,
  and can create contact sheets.
```

---

## 6. Records 1–32: shell RLE surfaces

Records `1–32` are shell screen/background surfaces.

They are mpack-compressed. After decompression, each surface contains a header, an RLE pixel stream, and a trailing RGB8 palette.

Decoded layout:

```text
payload header at +0x00
simple RLE stream at +0x80
trailing 0x300 bytes = RGB8 palette
```

The trailing palette is 256 RGB triplets:

```c
uint8_t palette_rgb8[256][3];
```

For PNG/export, use the trailing RGB8 palette directly.

The shell’s DirectDraw palette path quantizes RGB8 to RGB6 by shifting each byte right by two:

```c
dst_rgb6[i] = src_rgb8[i] >> 2;
```

Function:

```text
1003ea06  extract_shell_bitmap_palette_from_buffer
```

implements this RGB8-to-RGB6 palette extraction.

Important: the RGB6 interpretation looks blown out when exported as a normal RGB image. It should be treated as diagnostic for DirectDraw palette behavior, not as the preferred PNG export palette.

---

## 7. Shell surface RLE decode

Function:

```text
1003e984  decode_simple_rle_bitmap_to_shell_surface
```

Simple shell RLE model:

```text
data begins at record + 0x80

for each scanline:
  read controls until line_width pixels have been produced

  if (control & 0xc0) == 0xc0:
      count = control & 0x3f
      value = next byte
      emit value repeated count times
  else:
      emit control as one literal pixel
```

This is line-oriented. Decode each scanline independently until the expected line width is produced.

---

## 8. Shell surface palette groups

The 32 decoded shell surfaces contain several distinct trailing palettes.

Current palette groups:

```text
Group A, common shell UI palette from record 1:
  records 1,2,3,4,6,7,8,9,10,11,12,13,16,18,19,20,21,22,23,24,25,26,28,29,30,31,32

Group B:
  record 5

Group C:
  record 14

Group D:
  records 15,17

Group E:
  record 27, final-mission special
```

Most ordinary `1.10` overlays render correctly with the common record 1 / group A palette.

Record 64 specifically uses record 27 / group E.

---

## 9. Direct shell surface use map

Direct shell surface call mappings from precise callsite export and v2 resource map include:

```text
10003ac0  shell_ui_object_event_handler                    -> surface record 1
10018ae0  FUN_10018ae0                                    -> surface record 3
100258f0  FUN_100258f0                                    -> surface record 4
1000e2e0  handle_play_options_screen                      -> surface record 6
1000dae0  shell_screen_state_handler_b                    -> surface record 7
10011cb0  confirm_leave_game_dialog                       -> surface record 8
10011fd0  handle_video_options_screen                     -> surface record 9
10014270  handle_gameplay_options_screen                  -> surface record 10
100145f0  handle_save_game_prompt                         -> surface record 11
100147a0  handle_save_game_scene_selection                -> surface record 11
10012fe0  FUN_10012fe0                                    -> surface record 12
10007930  init_shell_ui_state                             -> surface record 13
1001f3e0  FUN_1001f3e0                                    -> surface record 14
1000eb80  handle_input_mapping_screen                     -> surface record 16
1000fb90  FUN_1000fb90                                    -> surface record 16
10010790  handle_input_binding_selection_screen           -> surface record 16
10027f20  handle_mission_selection_screen                 -> surfaces 18,19,20,22,23,24,25 plus dynamic cases
10025980  FUN_10025980                                    -> surface record 26
10023b60  preload_final_mission_special_menu_record_0x40  -> surface record 27
1003f830  FUN_1003f830                                    -> surface record 28
10023fc0  FUN_10023fc0                                    -> surfaces 29 and 31
10013950  handle_modem_setup_screen                       -> surface record 32
```

Some older context evidence is broad/noisy. Prefer direct loader/user/draw evidence from v2 maps rather than broad `context_functions`.

---

## 10. Records 36–64: `1.10` UI overlay resources

Records `36–64` are `1.10` multi-subresource UI image resources.

Top-level format:

```c
struct mw2_multi_bitmap_v1_10 {
    char     magic[4];       // "1.10"
    uint32_t count;
    uint32_t data_start;     // observed: 16 + (count - 1) * 8
    uint32_t reserved;       // observed 0
    uint64_t end_offsets[count - 1];
    uint8_t  subresources[];
};
```

Each subresource begins with a 24-byte header candidate:

```c
struct mw2_bitmap_subresource_header_candidate {
    uint16_t height_a;
    uint16_t width_a;
    uint32_t zero_04;
    uint32_t zero_08;
    uint32_t zero_0c;
    uint32_t width_b;
    uint32_t height_b;
    uint8_t  compressed_payload[];
};
```

The current decoder treats subresources as bounded indexed bitmaps with a custom byte-oriented RLE stream.

---

## 11. `1.10` RLE decode model

Working model:

```text
control = next byte
flag = control & 1
count = control >> 1

flag=0, count=0:
  end of line

flag=0, count>0:
  fill run
  value = next byte
  emit value repeated count times

flag=1, count=0:
  extended skip
  skip_count = next byte
  advance x by skip_count without writing pixels

flag=1, count>0:
  literal copy
  copy count literal bytes from stream to output
```

This format is line-oriented. The `flag=0,count=0` control terminates the current scanline.

The current exporter/decoder model is sufficient to visually decode ordinary overlays and the final-mission special overlay.

---

## 12. `1.10` draw path

Ordinary `1.10` draw path is direct indexed blit, not palette remap.

Relevant functions:

```text
10039390  draw_mw2_image_subresource_to_shell_surface
  -> 1003a8f4  blit_mw2_image_subresource_rle_clipped
```

`10031a30 draw_ui_image_subrect_with_optional_restore` chooses the normal draw path unless optional restore/masked path is enabled.

In observed calls, `param_10 = 0`, so the remap-aware path is not used.

Remap functions exist:

```text
1003ae6b  set_shell_image_palette_remap_table
1003c38d  remap_mw2_image_record_rle_stream_in_place
```

But bad colors in early overlay exports were palette-context problems, not missing remap-table behavior.

Practical palette rule:

```text
Ordinary overlays: use common shell surface record 1 palette unless proven otherwise.
Record 64: use shell surface record 27 palette.
```

---

## 13. `1.10` preload mapping

Known preload/record mapping:

```text
10031640 -> record 0x24 / 36 -> g_shell_ui_image_record_ptr_100f4f90

100316a0 -> table-driven records 0x25–0x34
          plus direct records 0x35–0x3b and 0x3f

100314a0 -> records 0x3c, 0x3d / 60, 61
          -> g_shell_ui_image_record_ptr_100f4fb4
          -> g_shell_ui_image_record_ptr_100f4fb8

10031670 -> record 0x3e / 62

10023b60 -> record 0x40 / 64, final-mission special
```

Strong ordinary draw client:

```text
10031b20  draw_vehicle_config_component_ui_overlays
```

It uses preloaded globals such as:

```text
g_shell_ui_image_record_ptr_100f4f48
g_shell_ui_image_record_ptr_100f4f60
g_shell_ui_image_record_ptr_100f4f70
g_shell_ui_image_record_ptr_100f4f80
g_shell_ui_image_record_ptr_100f4f94
g_shell_ui_image_record_ptr_100f4f98
g_shell_ui_image_record_ptr_100f4f9c
g_shell_ui_image_record_ptr_100f4fa0
g_shell_ui_image_record_ptr_100f4fa4
```

and draws through:

```text
10031a30  draw_ui_image_subrect_with_optional_restore
10039390  draw_mw2_image_subresource_to_shell_surface
```

---

## 14. Record 64: final-mission special

Record 64 / `0x40` is a special `1.10` UI resource.

Function:

```text
10023b60  preload_final_mission_special_menu_record_0x40
```

Binary behavior:

```text
mpack_database_get_item(DAT_100cc53c, 0x40, &DAT_100d3968, &local_4)
load/apply surface record 0x1b / 27 through 100387d0
```

User confirmation:

```text
Record 64 entries are from a special menu selection screen that appears only before the final mission.
```

Visual/palette conclusion:

```text
Record 64 is correct with palette from record 27.
Record 64 is not correct with common record 1 palette.
```

Durable classification:

```text
record_id: 64
class: ui_overlay
subclass: mw2_1_10_final_mission_special_menu
status: decoded_indexed_palette_paired
palette_source_record: 27
palette_group: E_record27_final_mission_special
format: 1.10 multi-subresource image
encoding: custom byte-oriented RLE
draw_model: direct indexed blit
```

---

## 15. Records 33–35: unresolved shell random-selection resources

Records `33–35` are loaded by:

```text
100196b0  preload_randomized_shell_resources_0x21_0x23
```

Behavior:

```text
rand() % 5 -> DAT_100d1d88
rand() % 5 -> DAT_100d1d84
rand() % 5 -> DAT_100d1d8c

load record 33 -> DAT_100d1dc4
load record 34 -> DAT_100d1dc8
load record 35 -> DAT_100d1dcc
```

Classification:

```text
records 33–35: shell random-selection resources
exact format unresolved
```

Recommended name:

```text
100196b0  preload_randomized_shell_resources_0x21_0x23
```

A concrete consumer path exists:

```text
10019f40  draw_vehicle_part_damage_indicator
```

This function selects one of the randomized resources based on part damage/current value and draws it as an overlay.

Current status:

```text
Nonblocking for shell launch contract and main asset recovery.
Worth revisiting only if exact vehicle damage indicator UI reconstruction is needed.
```

---

## 16. Records 65–71: glyph sheets

Glyph sheet format is structurally solved.

Common layout:

```c
struct mw2_glyph_sheet {
    char     magic[4];                  // "1.  "
    uint32_t glyph_count;               // 8896, 256, or 144
    uint32_t glyph_height;              // 12, 15, or 10
    uint32_t flags;                     // 0 for record 65, 0xff for ASCII sheets
    uint32_t glyph_offsets[count];      // absolute starts from record base
    // glyph payloads follow
};
```

ASCII records `66–71`:

```c
struct glyph_entry_ascii_8bpp {
    uint32_t width;
    uint8_t  pixels[width * glyph_height]; // 8bpp row-major
};
```

Localized record `65`:

```c
struct glyph_entry_localized_1bpp {
    uint32_t width;
    uint8_t  bitpacked_rows[ceil(width / 8) * glyph_height]; // 1bpp bit-packed rows
};
```

Validated records:

```text
record 65: entries 8896, height 12, 1bpp bitpacked, valid entries 8896, nonempty 8802
record 66: entries 256,  height 15, 8bpp
record 67: entries 256,  height 15, 8bpp
record 68: entries 144,  height 12, 8bpp
record 69: entries 256,  height 15, 8bpp
record 70: entries 256,  height 15, 8bpp
record 71: entries 144,  height 10, 8bpp
```

Manual inspection confirmed:

```text
record 65 appears Unicode/UTF-style or DBCS/localized.
records 66–71 are simple ASCII glyph sheets.
```

---

## 17. Glyph/text functions

Important shell glyph/text functions:

```text
10015530  construct_shell_glyph_sheet
1003e419  get_shell_glyph_sheet_height
10015580  measure_string_width_from_glyph_sheet
100155d0  get_wrapped_glyph_width
1003e42c  get_glyph_width
1003e44c  blit_glyph_to_surface
1003e5d7  draw_ascii_string_from_glyph_sheet
100395b0  measure_and_draw_string_from_glyph_sheet
10039750  draw_single_glyph_to_shell_surfaces
10038fd0  clear_text_rect
1003c888  blit_or_fill_rect_clipped

1001fbf0  update_debug_mouse_coordinate_overlay
100157d0  draw_glyph_from_glyph_sheet_object
100374c0  process_rich_text_glyph_stream
100157a0  draw_string_from_glyph_sheet_object
10015800  draw_edit_buffer_glyph_or_control
100373e0  render_rich_text_object
10037490  rewind_and_render_rich_text_to_position
100377c0  step_rich_text_object
100398b0  prepare_or_clear_text_draw_context
```

Localized/DBCS glyph functions:

```text
1003f5d0  get_localized_glyph_width_and_set_stride
1003f620  blit_localized_glyph_to_surface
1003f7e5  draw_localized_string_to_surface
```

Localized globals:

```text
DAT_1004efa0  global character stride / text mode width; becomes 1 or 2
DAT_1004ef9c  lead-byte/glyph-page mapping table for localized glyph rendering
DAT_1004efa4  current localized glyph draw byte/color/index
```

Rich text controls handled by `process_rich_text_glyph_stream`:

```text
 or \A  switch/reset drawing attribute/color table
NNN     move baseline/x position backward
\gNNN     move to absolute/relative tab stop from left origin
	 or \T  advance to next tab stop
```

It can emit 16-bit glyph codes with:

```c
CONCAT11(next_byte, current_byte)
```

---

## 18. Records 72–82: audio-ish records

Records `72–82` are classified as WAVE/PIFF audio-ish records.

Current status:

```text
classified audio records
not deeply reversed in this pass
secondary priority unless audio asset recovery becomes important
```

---

## 19. Record 83: credits text

Record `83` is decoded as text and appears to contain credits.

Current status:

```text
decoded_text
```

---

## 20. Shell surface/display context functions

Important `DATABASE.MW2` display context functions:

```text
10037a50  construct_shell_surface_context
1000cb40  select_shell_display_mode_and_backend
10038530  copy_shell_surface_palette_out
10038550  set_shell_surface_palette_from_rgb6
10038630  load_shell_rle_bitmap_surface_from_buffer
100387d0  load_or_apply_shell_surface_record_by_id_candidate
10039230  load_shell_rle_bitmap_surface_from_database_record
1003ea06  extract_shell_bitmap_palette_from_buffer
1003e984  decode_simple_rle_bitmap_to_shell_surface
1003ea31  get_shell_bitmap_dimensions_packed
10039390  draw_mw2_image_subresource_to_shell_surface
1003a8f4  blit_mw2_image_subresource_rle_clipped
```

ShellMain allocates a shell surface context object of size `0x3d8` and constructs it through:

```text
10037a50  construct_shell_surface_context
```

The context is stored at:

```text
DAT_100cc518
```

---

## 21. Practical export guidance

### 21.1 Shell surfaces

For records `1–32`:

1. mpack-decompress the record.
2. Decode shell RLE from payload `+0x80`.
3. Extract trailing RGB8 palette from the last `0x300` bytes.
4. Export PNG using trailing RGB8 palette.
5. Treat RGB6 as DirectDraw diagnostic only.

### 21.2 1.10 overlays

For records `36–64`:

1. Parse `1.10` top-level header.
2. Use `count`, `data_start`, and `uint64 end_offsets[count-1]`.
3. Parse each subresource header candidate.
4. Decode line-oriented byte RLE.
5. Apply correct palette context:
   - ordinary overlays: common record 1 palette group A
   - record 64: record 27 palette group E

### 21.3 Final-mission special

Record 64 should be exported with record 27 palette.

Useful composition from prior sample:

```text
surface record 27 as background
record 64 subresources overlaid at draw origin recovered from 10031b20:
  x = 0x145
  y = 0x70
```

This produced visually validated final-mission special sample outputs.

---

## 22. Important scripts/artifacts

Preferred/current scripts from this line of work:

```text
cgpt_i76_decode_database_mw2_shell_rle_surfaces_v3.py
  Current preferred shell surface decoder.
  mpack-decompresses selected DATABASE.MW2 records,
  decodes shell RLE,
  uses trailing RGB8 palette.
  rgb8_trailing is correct; rgb6_trailing is diagnostic/blown out.

cgpt_i76_scan_all_shell_surface_palettes_apply_to_110_v2.py
  Correct broad scanner.
  Discovers shell surfaces 1–32, extracts palettes,
  applies unique palette groups to 1.10 overlays,
  can create contact sheets.

cgpt_i76_build_database_mw2_resource_map_v2.py
  Current preferred durable resource-map builder.
  Separates direct_loader_functions, direct_surface_user_functions,
  direct_draw_functions, and context_functions.

cgpt_i76_reconstruct_database_mw2_shell_screens.py
  Standalone reconstruction/composition tool.
  Reads DATABASE.MW2 directly.
  Implements mpack, shell surface decode, 1.10 overlay parsing/RLE,
  and palette policy.
```

Useful generated artifact:

```text
i76_database_mw2_final_mission_sample_v1.tar
```

This contains record 27 surface, record 64 subresources with palette 27, and candidate composites.

---

## 23. Known caveats

1. Records `33–35` remain unresolved-format shell resources.
   - They are loaded by `100196b0`.
   - They are used by `10019f40 draw_vehicle_part_damage_indicator`.
   - They are nonblocking for launch/session recovery and most shell asset recovery.

2. Some v2 resource-map context arrays are intentionally broad/noisy.
   - Prefer:
     ```text
     direct_loader_functions
     direct_surface_user_functions
     direct_draw_functions
     evidence
     notes
     ```
   - Treat broad `context_functions` as debug context, not proof of direct record use.

3. RGB6 palette output should not be used as the normal PNG export palette.
   - Use trailing RGB8 for exports.

4. Ordinary `1.10` overlays do not require DAT_1004ee3c remap-table behavior in observed static paths.
   - Bad colors were palette-context issues.

5. Record 64 is a special case.
   - It must use record 27 palette.

---

## 24. Recommended future work

For `DATABASE.MW2`, future work is optional unless shell UI fidelity is important.

Highest-value possible follow-ups:

```text
1. Resolve records 33–35 exact format.
2. Build a complete shell screen reconstruction set using direct surface/overlay usage maps.
3. Improve 1.10 subresource placement by recovering exact draw origins from each screen handler.
4. Decode/export audio-ish records 72–82 if audio asset recovery becomes important.
5. Create a clean standalone DATABASE.MW2 extractor CLI with:
   --export-surfaces
   --export-overlays
   --export-glyphs
   --export-text
   --compose-known-screens
```

For the broader project, `DATABASE.MW2` is sufficiently understood for now. The next major value is in `i76.exe`, especially the shell callback table targets, post-ShellMain launch handling, and mission/resource loading.
