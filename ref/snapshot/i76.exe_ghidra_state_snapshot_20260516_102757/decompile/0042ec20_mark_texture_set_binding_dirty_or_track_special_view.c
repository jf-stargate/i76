/*
 * Program: i76.exe
 * Function: mark_texture_set_binding_dirty_or_track_special_view
 * Entry: 0042ec20
 * Signature: undefined __cdecl mark_texture_set_binding_dirty_or_track_special_view(int * param_1, char * param_2)
 */


/* [cgpt i76.exe player weapon targeting rename v26; confidence=medium] Marks texture-set binding
   dirty/special after HUD/object texture binding; special-cases zbk, ZRADF000, and RearView
   bindings. */

void __cdecl mark_texture_set_binding_dirty_or_track_special_view(int *param_1,char *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if (DAT_00504be8 != 0) {
    apply_texture_palette_to_display_context(param_1);
    return;
  }
  iVar3 = 0;
  iVar2 = DAT_0052b910;
  if (0 < DAT_0052b910) {
    do {
      iVar1 = iVar2 + iVar3 >> 1;
      if ((int *)(&DAT_005280f0)[iVar1 * 7] < param_1) {
        iVar3 = iVar1 + 1;
        iVar1 = iVar2;
      }
      iVar2 = iVar1;
    } while (iVar3 < iVar1);
  }
  if (((int *)(&DAT_005280f0)[iVar3 * 7] == param_1) && (param_1 != (int *)0x0)) {
    iVar2 = _stricmp(param_2,s_zbk__map_004edf90);
    if ((iVar2 != 0) && (iVar2 = _stricmp(param_2,s_ZRADF000_tmt_004edf80), iVar2 != 0)) {
      iVar2 = _stricmp(param_2,s_RearView_004edf74);
      if (iVar2 == 0) {
        DAT_005280e8 = get_current_texture_cache_generation();
      }
      (&DAT_005280fc)[iVar3 * 7] = 0xfffffc18;
      return;
    }
    (&DAT_005280f8)[iVar3 * 7] = 1;
  }
  return;
}


