# Interstate ’76 `i76shell.dll` Reverse-Engineering Reference

**Scope:** `i76shell.dll`, the Interstate ’76 shell/frontend DLL.  
**Status:** Practical shell analysis is complete enough to pivot to `i76.exe`.  
**Primary goal:** Understand shell-to-engine launch behavior and recover shell assets, not exhaustively name every frontend helper.

---

## 1. Role of `i76shell.dll`

`i76shell.dll` is the shell/frontend DLL used by `i76.exe` for the menus and launch preparation. It handles mission selection, campaign/trip selection, player and vehicle selection, vehicle configuration, save/load screens, options screens, multiplayer/DirectPlay setup, shell UI drawing, `DATABASE.MW2` asset loading, and preparation of the shell-to-engine launch/session config block.

It is not the main game runtime. The shell prepares a launch/session state and returns to `i76.exe`, which performs post-shell asset/cache refresh and starts the selected game/session.

---

## 2. Binary baseline

Image base:

```text
10000000
```

Known exports:

```text
1001e260  ShellMain
1001da10  ShellWindowProc
10040040  DLL/CRT entry
```

The final rename pass applied most consolidated high/medium-confidence names successfully:

```text
total embedded rename rows: 165
applied: 131
skipped: 33
failed: 1
```

The only failure was nonblocking:

```text
10030bc0  free_phonebook_entry_record
reason: no function at or containing address
```

Treat `10030bc0` as a dropped local-label/comment candidate unless it becomes relevant later.

---

## 3. Ghidra scripting conventions

Use a flat script category:

```java
//@category i76
```

Do not create subcategories like `i76/export` or `i76/renames`.

Script filenames should identify the target binary, for example:

```text
cgpt_i76shell_...
cgpt_i76exe_...
```

Exporter scripts should preserve an interactive output-directory prompt, but default to:

```text
/media/stargate-remote/prj/i76/scratch_data/
```

Exporter scripts should create a timestamped unpacked folder and a sibling `.tar` archive using system `tar`. Avoid custom Java tar writers.

Observed Ghidra 12.0.4 API behavior:

```java
getReferencesFrom(Address)   -> Reference[]
getReferencesTo(Address)     -> ReferenceIterator
```

Avoid helper names that collide with final inherited GhidraScript/FlatProgramAPI methods. For example, do not define `getFunction(String)` in a script.

---

## 4. Shell-to-engine contract

### 4.1 `i76.exe` call into `ShellMain`

`i76.exe` calls into the shell through:

```text
004022e0  call_shell_main
```

`call_shell_main` builds a `0x6c`-byte callback table on the stack and passes it as ShellMain arg9. It passes a launch/session config block as arg10.

ShellMain argument mapping from the `i76.exe` callsite:

```text
ShellMain(
  arg1  = DAT_005dd2f8,              // loaded i76shell.dll HMODULE
  arg2  = 0,
  arg3  = call_shell_main param_2,
  arg4  = call_shell_main param_3,
  arg5  = call_shell_main param_1,    // likely HWND/window or engine context
  arg6  = DAT_004f9f20 ? 0x643920 : 0,
  arg7  = &DAT_004c2160,
  arg8  = &DAT_005dcea4,
  arg9  = &local_6c callback table,
  arg10 = param_4,                   // launch/session config block
  arg11 = previous DAT_004c2164,
  arg12 = &DAT_005dce80,
  arg13 = &DAT_004f9e08
)
```

Shell side confirms:

```text
DAT_10058198 = arg9 callback table
DAT_100d2170 = arg10 launch/session config block
DAT_100d218c = (*arg10 >> 5) & 1
```

Network/session code aliases arg10 through:

```text
DAT_100f231c
```

Key binding function:

```text
1002f178  bind_shell_launch_config_block_and_close_previous_directplay
```

### 4.2 Callback table from `i76.exe`

`ShellMain` arg9 is the engine callback table stored by the shell in `DAT_10058198`.

Known entries:

```text
+0x00  004b4c10
+0x04  004b4b80
+0x08  004b2b30  register_resource_file_record
+0x0c  004b6850
+0x10  004b73a0
+0x14  004b58a0  load_shell_vehicle_definition
+0x18  004b7190
+0x1c  004b72b0
+0x20  004b0bd0
+0x24  004b0b00
+0x28  00421400
+0x2c  00421d50
+0x30  00421e90
+0x34  00421f50
+0x38  00423520
+0x3c  00423540
+0x40  004235a0
+0x44  00470f90  prompt_for_cd2_if_needed
+0x48  00499ba0
+0x4c  00433de0
+0x50  00423330
+0x54  004233d0
+0x58  004b4a80
+0x5c  00499920
+0x60  00499410
+0x64  004b3570
+0x68  004b35a0
```

The remaining exact callback-slot semantics should be resolved from `i76.exe`, because the targets live there.

Highest-priority callback targets:

```text
+0x08  004b2b30  register_resource_file_record
+0x14  004b58a0  load_shell_vehicle_definition
+0x44  00470f90  prompt_for_cd2_if_needed
```

### 4.3 Launch/session config block

ShellMain arg10 is the engine-owned launch/session config block. Shell stores it in `DAT_100d2170`.

Known/inferred fields:

```text
+0x00  flags
       Shell writes 1, then ORs mode/network flags.
       Bit 0x20 mirrors DAT_100d218c = (*arg10 >> 5) & 1.

+0x04  shell/session mode id
       Multiplayer paths write DAT_100d217c here.

+0x08  DirectPlay/session handle or engine handle
       FUN_1002f178 closes it if nonzero.

+0x0c  DirectPlay player id
       Destroyed/cleared by FUN_1002f178.

+0x4e  path/resource buffer
       Filled through 1002d2d0 format_launch_config_resource_path_at_0x4e.

+0x5d  mission filename buffer
       ShellMain compares this against a01.msn and writes t%02d.msn here.
       Multiplayer paths copy the selected mission filename here.

+0x6c  selected map/session scalar
       i76.exe later copies this to DAT_00504a04.

+0x70  short session/map/player text block
       i76.exe later copies 0x1e bytes to DAT_00504a08.

+0x90  selected session descriptor scalar A

+0x94  selected session descriptor scalar B / close marker
       FUN_1002f178 clears bytes +0x94..+0x97 when closing a prior session.

+0x98  0x66-dword session/connection descriptor block
       Multiplayer launch/join paths fill this from DAT_100f4778.
       i76.exe later copies 0x66 dwords to DAT_00504a30.
```

After successful ShellMain return, `i76.exe` reads/copies at least:

```text
param_4 + 0x4e   used to build/copy mission/session path
param_4 + 0x70   copied into DAT_00504a08, length 0x1e
param_4 + 0x6c   copied into DAT_00504a04
param_4 + 0x98   copied as 0x66 dwords into DAT_00504a30
```

### 4.4 ShellMain return behavior

ShellMain low byte `0xff` is treated by `i76.exe` as cancellation/exit.

Non-cancel returns trigger post-shell asset/cache refresh and launch setup. Return value `3` is strongly associated with starting a selected game/session.

Post-shell calls in `i76.exe` include:

```text
00470ac0
0046fab0
0046fb30
00470660  load_pix_index
```

---

## 5. Key shell launch/session functions

```text
1002f178  bind_shell_launch_config_block_and_close_previous_directplay
10016a20  launch_single_player_arcade_seed_session
10016b50  launch_single_player_trip_seed_session
10002750  dispatch_selected_mission_or_vehicle_config_transition
10002130  populate_current_mission_vehicle_selection_list
1002f368  start_hosted_multiplayer_game_session_and_fill_launch_config
1002fcd8  validate_joined_multiplayer_session_and_fill_launch_config
1002d2d0  format_launch_config_resource_path_at_0x4e
```

---

## 6. `DATABASE.MW2`

### 6.1 Container format

`DATABASE.MW2` is a simple indexed pack:

```c
uint32_t record_count;
uint32_t record_offsets[record_count]; // absolute offsets from start of file
uint8_t record_data[];
```

Observed uploaded `DATABASE.MW2`:

```text
file size: 8,204,554 bytes
record count: 83
offset table end: 0x150
first record offset: 0x150
```

Records are effectively 1-based IDs in shell `mpack_database_get_item`.

Database functions:

```text
10007fd0  open_mpack_database
10008240  mpack_database_get_item
10008320  mpack_database_get_item_alloc_or_alias
```

Database object:

```text
+0x80 FILE*
+0x84 record_count
+0x88 offset/size table/list object
```

### 6.2 Record partition

```text
Records 1–32:  mpack-compressed shell RLE screen/background surfaces
Records 33–35: shell random-selection resources loaded by 100196b0; exact format unresolved
Records 36–63: ordinary "1.10" UI overlay / multi-subresource resources
Record 64:     final-mission special 1.10 menu resource paired with surface/palette record 27
Records 65–71: glyph sheets
Records 72–82: WAVE/PIFF audio-ish records
Record 83:     credits text
```

Record class counts from the v2 map:

```text
audio: 11
glyph_sheet: 7
shell_resource: 3
shell_surface: 32
text: 1
ui_overlay: 29
```

### 6.3 Final-mission special record

```text
10023b60  preload_final_mission_special_menu_record_0x40
```

This loads `DATABASE.MW2` record `0x40` / 64 and applies surface/palette record `0x1b` / 27. User confirmed record 64 is a special menu selection screen shown only before the final mission.

Correct palette for record 64:

```text
record 27 / palette group E
```

---

## 7. Shell surface records 1–32

Records `1–32` are mpack-compressed shell RLE surfaces with trailing RGB8 palettes.

Payload after mpack decompression:

```text
payload header at +0x00
RLE stream at +0x80
trailing 0x300 bytes = RGB8 palette
```

Simple shell RLE:

```text
for each scanline:
  read until line_width pixels produced

  if (control & 0xc0) == 0xc0:
      count = control & 0x3f
      value = next byte
      emit value repeated count times
  else:
      emit control as one literal pixel
```

For PNG/export, use trailing RGB8 directly.

Shell internal DirectDraw palette path converts RGB8 to RGB6:

```c
dst[i] = src[i] >> 2;
```

Function:

```text
1003ea06  extract_shell_bitmap_palette_from_buffer
```

Palette groups:

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

---

## 8. 1.10 UI overlay resources

Records `36–64` are `1.10` UI overlay / multi-subresource resources.

Top-level format:

```c
struct mw2_multi_bitmap_v1_10 {
    char magic[4];       // "1.10"
    uint32_t count;
    uint32_t data_start; // observed: 16 + (count - 1) * 8
    uint32_t reserved;   // observed 0
    uint64_t end_offsets[count - 1];
    uint8_t subresources[];
};
```

Subresource header candidate:

```c
struct mw2_bitmap_subresource_header_candidate {
    uint16_t height_a;
    uint16_t width_a;
    uint32_t zero_04;
    uint32_t zero_08;
    uint32_t zero_0c;
    uint32_t width_b;
    uint32_t height_b;
    uint8_t compressed_payload[];
};
```

Current byte-oriented RLE model:

```text
flag = control & 1
count = control >> 1

flag=0,count=0 -> end of line
flag=0,count>0 -> fill next byte for count pixels
flag=1,count=0 -> extended skip; next byte is skip count
flag=1,count>0 -> literal copy count bytes
```

Ordinary draw path is direct indexed blit:

```text
10039390  draw_mw2_image_subresource_to_shell_surface
  -> 1003a8f4  blit_mw2_image_subresource_rle_clipped
```

Remap functions exist but are not the ordinary static path:

```text
1003ae6b  set_shell_image_palette_remap_table
1003c38d  remap_mw2_image_record_rle_stream_in_place
```

---

## 9. Glyph and text rendering

Glyph sheet layout:

```c
struct mw2_glyph_sheet {
    char magic[4];                  // "1.  "
    uint32_t glyph_count;
    uint32_t glyph_height;
    uint32_t flags;
    uint32_t glyph_offsets[count];
};
```

ASCII glyph entries:

```c
struct glyph_entry_ascii_8bpp {
    uint32_t width;
    uint8_t pixels[width * glyph_height];
};
```

Localized glyph entries:

```c
struct glyph_entry_localized_1bpp {
    uint32_t width;
    uint8_t bitpacked_rows[ceil(width / 8) * glyph_height];
};
```

Record details:

```text
65: 8896 entries, height 12, 1bpp bitpacked, localized/DBCS/Unicode-style
66: 256 entries, height 15, 8bpp ASCII
67: 256 entries, height 15, 8bpp ASCII
68: 144 entries, height 12, 8bpp ASCII
69: 256 entries, height 15, 8bpp ASCII
70: 256 entries, height 15, 8bpp ASCII
71: 144 entries, height 10, 8bpp ASCII
```

Important text/glyph functions:

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
1003f5d0  get_localized_glyph_width_and_set_stride
1003f620  blit_localized_glyph_to_surface
1003f7e5  draw_localized_string_to_surface
```

Localized text globals:

```text
DAT_1004efa0  global character stride / text mode width; becomes 1 or 2
DAT_1004ef9c  lead-byte/glyph-page mapping table
DAT_1004efa4  current localized glyph draw byte/color/index
```

---

## 10. Shell surface/display context

The shell display/surface context is allocated by ShellMain and constructed by:

```text
10037a50  construct_shell_surface_context
```

It is stored at:

```text
DAT_100cc518
```

Important surface/display functions:

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
10037e80  flush_or_repaint_shell_surface_context
100382e0  shell_surface_repaint_or_flip_with_palette_update
```

---

## 11. UI/list/factory layer

Localized strings:

```text
10037180  resolve_localized_shell_string_cached
100370e0  compare_localized_string_resource_key
```

Pointer/list helpers:

```text
10027800  create_pointer_list_default_16
10027870  create_pointer_list_with_capacity
100278f0  destroy_pointer_list_with_optional_item_destructor
10027970  insert_pointer_list_item_sorted_or_append
10027a90  remove_pointer_list_item
10027af0  find_pointer_list_item_index
10027b20  clear_pointer_list
10027b50  hit_test_ui_object_list_by_point
10027bf0  point_in_ui_object_bounds
10027c20  allocate_shell_ui_object_0x20
10027c80  initialize_single_player_shell_session_defaults
```

Static UI descriptor layer:

```text
10016760  destroy_static_ui_descriptor_widgets
100167a0  hit_test_static_ui_descriptor_table
1000e6b0  handle_static_menu_descriptor_selection
```

---

## 12. Modal/dialog layer

```text
1000b660  show_modal_ok_dialog
1000bc40  show_modal_two_button_choice_dialog
1000b080  open_modal_scroll_list_dialog
1000b2e0  open_modal_scroll_list_dialog_with_selection
1000a360  close_active_modal_list_dialog
100090d0  set_modal_list_previous_callback
1000bad0  handle_modal_dialog_confirm_or_default
1000bdd0  handle_modal_dialog_escape_or_cancel
1000c160  restore_previous_shell_dialog_state
```

---

## 13. Vehicle configuration subsystem

Vehicle config UI:

```text
10005400  initialize_vehicle_config_ui_lists
10005680  destroy_vehicle_config_ui_lists
10005820  draw_vehicle_config_section_labels
10005a30  draw_vehicle_part_list_column
10005ad0  draw_vehicle_part_list_column_indented
10005b80  draw_vehicle_part_inventory_scroll_list
10005e20  redraw_vehicle_config_screen
10007340  validate_required_vehicle_parts_selected
```

Vehicle part dialogs:

```text
100094c0  open_vehicle_part_selection_list_dialog
1000a440  redraw_vehicle_part_dialog_list_entries
1000a910  handle_vehicle_part_category_click
1000ab10  toggle_vehicle_part_dialog_selection
1000b020  open_equipped_vehicle_part_replacement_dialog
10007180  open_current_mission_vehicle_choice_dialog
10006b70  open_vehicle_part_subtype_choice_dialog
10006f00  open_vehicle_part_inventory_choice_dialog
1000a5e0  open_vehicle_part_category_screen
10007720  calculate_current_vehicle_config_weight
100076d0  show_vehicle_weight_limit_warning
10019f40  draw_vehicle_part_damage_indicator
```

Vehicle catalog and part helpers:

```text
10017f80  initialize_builtin_vehicle_catalog
100337b0  find_current_vehicle_part_by_type_and_name
10033b00  find_profile_vehicle_part_by_type_and_name
100338d0  populate_matching_vehicle_part_selection_list
10033d90  populate_equipped_vehicle_part_selection_list
10033f80  populate_vehicle_part_list_by_current_slot_names
100342f0  is_special_equipment_part_type
10034f70  build_vehicle_part_category_lists
10034e60  destroy_vehicle_part_category_lists
```

Vehicle serialization/export:

```text
10008b80  read_i76car_vehicle_definition_file
10008cf0  write_i76car_vehicle_definition_file
10009010  write_multicar_vehicle_definition_file
10017630  read_user_vehicle_lookup_table
10017710  write_user_vehicle_lookup_table
10032980  write_vehicle_scene_config_file
10033120  write_user_mel_file
100331e0  read_user_mel_file
10034420  write_user_repair_profile_file
100347d0  read_user_repair_profile_file
10034e50  delete_user_repair_profile_file
10035250  export_current_vehicle_config_with_parts
10035930  export_vehicle_scene_with_selected_parts
10035f30  remove_pointer_list_items_present_in_other_list
10035f70  write_vehicle_part_pointer_list_records
```

---

## 14. Input/options/save/load screens

Input/options:

```text
1000d430  handle_audio_options_screen
1000e2e0  handle_play_options_screen
1000eb80  handle_input_mapping_screen
1000f390  parse_input_mapping_file
1000fd30  write_input_mapping_file
100102d0  scan_configured_input_devices
10010530  populate_input_binding_device_action_list
10010790  handle_input_binding_selection_screen
100115d0  open_input_binding_action_choice_dialog
10011710  format_input_binding_display_name
1001cd60  format_keyboard_key_display_name
1001f660  format_mouse_binding_display_name
10011fd0  handle_video_options_screen
10013950  handle_modem_setup_screen
10013ea0  draw_modem_setup_current_values
10014020  read_modem_ini_settings
10014270  handle_gameplay_options_screen
```

Save/load:

```text
10011cb0  confirm_leave_game_dialog
10013670  draw_load_game_scene_list
100137d0  initialize_load_game_screen
100145f0  handle_save_game_prompt
100147a0  handle_save_game_scene_selection
100150a0  draw_save_game_scene_list
10033020  read_savegame_directory_index
10032f80  enumerate_savegame_directory
10013380  commit_selected_savegame_and_launch_session
```

Player files:

```text
10016f70  read_player_definition_file
10017050  write_player_definition_file
10017300  write_default_player_definition_file
```

---

## 15. DirectPlay/network subsystem

DirectPlay interface/wrapper layer:

```text
10022ca0  create_or_open_directplay_interface
10022d10  release_directplay_interface
10022d50  query_directplay_service_provider_caps_or_guid
```

Connection state:

```text
1002e2f0  initialize_directplay_connection_for_mode
10036010  create_multiplayer_connection
10036350  construct_multiplayer_connection_state
10036410  destroy_multiplayer_connection_state
100364b0  initialize_multiplayer_connection_callbacks
10036550  reset_multiplayer_connection_session_state
```

Dialogs and state UI:

```text
1002c1c0  open_network_provider_choice_dialog
1002f018  open_directplay_session_connection_dialog
1002eb17  redraw_multiplayer_connection_status_dialog
1002e9b7  shutdown_directplay_session_and_thread
1002f1f8  destroy_directplay_connection_handle
1002f2c8  is_multiplayer_connection_active
```

Launch/join:

```text
1002f368  start_hosted_multiplayer_game_session_and_fill_launch_config
1002e487  join_selected_multiplayer_session
1002fcd8  validate_joined_multiplayer_session_and_fill_launch_config
100304e8  rebuild_directplay_session_pointer_list
```

Multiplayer browser/list drawing:

```text
1002b180  draw_multiplayer_provider_status_panel
1002b350  draw_multiplayer_map_or_mission_list_page
1002b450  draw_available_multiplayer_games_list
1002b5b0  redraw_multiplayer_lobby_browser_screen
1002d340  update_victory_record_for_selected_map
1002e2c0  draw_shell_text_at_position
1002e3d0  poll_directplay_session_enumeration
1002ed57  refresh_directplay_session_list_async
10030338  compact_or_update_directplay_player_records
10030748  find_current_directplay_session_desc
```

Enumeration callbacks/descriptors:

```text
1002d250  directplay_provider_enum_callback
1002d260  directplay_session_enum_callback
1002d280  directplay_player_enum_callback
1002d290  copy_directplay_guid_or_descriptor_blob
1002d310  free_directplay_session_descriptor
1002d320  format_directplay_session_descriptor
```

---

## 16. Shell asset recovery status

Decoded/recovered:

```text
DATABASE.MW2 record index/container
shell RLE surface records 1–32
surface palettes
1.10 overlay records 36–64
record 64 final mission special, palette-paired to record 27
glyph sheets 65–71
credits text record 83
audio-ish records 72–82 classified
```

Partially unresolved but nonblocking:

```text
records 33–35
```

They are loaded by:

```text
100196b0  preload_randomized_shell_resources_0x21_0x23
```

They are consumed at least by:

```text
10019f40  draw_vehicle_part_damage_indicator
```

Exact format remains unresolved.

---

## 17. Recommended pivot to `i76.exe`

The shell DLL is sufficiently documented and renamed to act as a reference while analyzing `i76.exe`.

First `i76.exe` priorities:

1. Strengthen `call_shell_main`.
2. Confirm ShellMain return enum handling.
3. Confirm how post-ShellMain arg10 offsets `+0x4e`, `+0x6c`, `+0x70`, and `+0x98` are copied/used.
4. Resolve callback table slot semantics from the engine side.
5. Continue resource/archive stack recovery.
6. Trace mission/session launch path into mission loading.

Known or inferred `i76.exe` names relevant to the pivot:

```text
004022e0  call_shell_main
004b9800  open_zfs_archive
004b9bd0  read_zfs_record
004b9fc0  decompress_zfs_record
004b28c0  enumerate_resource_directory_files
004b42b0  resolve_mission_or_resource_path
00470660  load_pix_index
```

Suggested first `i76.exe` exporter:

```text
cgpt_i76exe_export_shell_contract_consumers_v1.java
```

It should export:

```text
call_shell_main decompile/disassembly
all refs/calls around 004022e0 call_shell_main
post-ShellMain return handling
reads/writes of launch config block offsets +0x4e/+0x6c/+0x70/+0x98
callback table construction at stack local_6c
all callback target function decompiles
post-launch resource/cache refresh calls
mission filename/path propagation
resource/ZFS callback usage
```

Callback target decompiles to include:

```text
004b4c10, 004b4b80, 004b2b30, 004b6850, 004b73a0,
004b58a0, 004b7190, 004b72b0, 004b0bd0, 004b0b00,
00421400, 00421d50, 00421e90, 00421f50,
00423520, 00423540, 004235a0, 00470f90,
00499ba0, 00433de0, 00423330, 004233d0,
004b4a80, 00499920, 00499410, 004b3570, 004b35a0
```

---

## 18. Important generated shell artifacts

Shell/database reconstruction:

```text
cgpt_i76_reconstruct_database_mw2_shell_screens.py
i76_database_mw2_final_mission_sample_v1.tar
```

Key shell evidence exporters:

```text
cgpt_i76shell_export_baseline_v3_fixed2.java
cgpt_i76shell_export_object_layout_evidence_v2.java
cgpt_i76shell_export_factory_layer_evidence_v3.java
cgpt_i76shell_export_launch_contract_evidence_v1_fixed.java
cgpt_i76shell_export_final_closure_evidence_v1_fixed.java
```

Final rename script:

```text
cgpt_i76shell_apply_final_semantic_renames_v1.java
```

The shell DLL is now sufficiently documented and renamed for the next phase of `i76.exe` work.
