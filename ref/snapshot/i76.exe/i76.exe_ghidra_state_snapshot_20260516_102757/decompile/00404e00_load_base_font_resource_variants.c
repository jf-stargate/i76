/*
 * Program: i76.exe
 * Function: load_base_font_resource_variants
 * Entry: 00404e00
 * Signature: undefined __stdcall load_base_font_resource_variants(void)
 */


/* cgpt whole-binary semantic rename v1: references base6x7*.fnt variants */

void load_base_font_resource_variants(void)

{
  int iVar1;
  char *pcVar2;
  
  if (DAT_00504c0c != (LPVOID)0x0) {
    dib_surface_context_getter_helper_004766d0(DAT_00504c0c);
  }
  if (g_display_mode_variant_index == '\x06') {
    pcVar2 = s_base6x74_fnt_004c2588;
    iVar1 = 1;
  }
  else if (g_display_mode_variant_index == '\a') {
    pcVar2 = s_base6x7_fnt_004c257c;
    iVar1 = 0;
  }
  else {
    pcVar2 = s_base6x76_fnt_004c256c;
    iVar1 = 2;
  }
  system_cutscene_memory_context_helper_004998f0(iVar1,pcVar2);
  DAT_00504c0c = dib_surface_palette_context_helper_004764c0();
  return;
}


