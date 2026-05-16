/*
 * Program: i76.exe
 * Function: ui_bitmap_region_context_helper_0049ae50
 * Entry: 0049ae50
 * Signature: undefined __stdcall ui_bitmap_region_context_helper_0049ae50(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v20: was ui_scroll_input_region_ui_bitmap_region_helper_0049ae50. Remove
   duplicated UI/region wording. */

void ui_bitmap_region_context_helper_0049ae50(void)

{
  if (g_active_smacker_cutscene_handle != 0) {
    if (DAT_004f9f20 == 0) {
      if (DAT_005a7d74 != 0) {
        _SmackBufferSetPalette_4(DAT_005a7d74);
      }
    }
    else {
      _DAT_005a7d7c = 1;
    }
    _SmackSoundOnOff_8(g_active_smacker_cutscene_handle,1);
    _DAT_005a7d78 = 1;
    return;
  }
  _DAT_005a7d78 = 0;
  return;
}


