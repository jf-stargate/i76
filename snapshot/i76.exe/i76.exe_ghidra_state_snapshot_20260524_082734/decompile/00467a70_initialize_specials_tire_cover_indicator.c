/*
 * Program: i76.exe
 * Function: initialize_specials_tire_cover_indicator
 * Entry: 00467a70
 * Signature: undefined __cdecl initialize_specials_tire_cover_indicator(undefined4 param_1, int param_2, int param_3, int param_4)
 */


/* cgpt whole-binary semantic rename v1: strings tire cover/diode */

void __cdecl
initialize_specials_tire_cover_indicator(undefined4 param_1,int param_2,int param_3,int param_4)

{
  bool bVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  byte *pbVar6;
  
  if (param_2 != 0) {
    iVar2 = ftol();
    bVar1 = false;
    iVar4 = 0;
    iVar5 = 0;
    do {
      if (((*(int *)((int)&DAT_004f8360 + iVar5) <= iVar2) &&
          (iVar2 <= *(int *)((int)&DAT_004f8364 + iVar5))) &&
         (((&DAT_004f85f0)[param_3] != iVar4 || (param_4 != 0)))) {
        draw_texture_widget_to_hud_surface_and_bind_object
                  (DAT_0054b9ec,(byte *)(s_zbks_320_map_004f8190 + DAT_004f863c * 0xd),
                   s_3sp_diode_1_004f84c0 + DAT_004f863c + param_3 * 0x10,
                   s_3off_004f8350 + iVar5 + DAT_004f863c,&DAT_0054b9b8,0);
        bVar1 = true;
        (&DAT_004f85f0)[param_3] = iVar4;
      }
      iVar5 = iVar5 + 0x18;
      iVar4 = iVar4 + 1;
    } while (iVar5 < 0x78);
    if (bVar1) {
      pbVar6 = (byte *)(s_zbks_320_map_004f8190 + DAT_004f863c * 0xd);
      piVar3 = (int *)bind_or_load_texture_set_for_object(DAT_0054b9ec,pbVar6,0);
      mark_texture_set_binding_dirty_or_track_special_view(piVar3,(char *)pbVar6);
    }
  }
  return;
}


