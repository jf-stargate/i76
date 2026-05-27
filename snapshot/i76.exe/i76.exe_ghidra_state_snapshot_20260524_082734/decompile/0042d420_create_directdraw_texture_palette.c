/*
 * Program: i76.exe
 * Function: create_directdraw_texture_palette
 * Entry: 0042d420
 * Signature: undefined4 __cdecl create_directdraw_texture_palette(undefined4 * param_1, int param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: string evidence: failed to create palette for destination
   texture */

undefined4 __cdecl create_directdraw_texture_palette(undefined4 *param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  int local_434 [13];
  undefined4 auStack_400 [256];
  
  bVar1 = 3;
  if (param_2 == 1) {
    bVar1 = 0;
  }
  iVar2 = init_display_mode_full_setup_candidate
                    (bVar1,(HWND)param_1[0x2f],&LAB_0042e500,0,&LAB_0042e4e0,0);
  if (iVar2 == 0) {
    return 0;
  }
  if (param_2 == 1) {
    (*(code *)param_1[0xff])(param_1);
    (*(code *)param_1[0x100])(param_1);
    if (DAT_005fff34 == 1) {
      puVar3 = auStack_400;
      for (iVar2 = 0x100; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar3 = 0;
        puVar3 = puVar3 + 1;
      }
      iVar2 = (**(code **)(*DAT_006080b8 + 0x14))(DAT_006080b8,0x44,auStack_400,&DAT_006080cc,0);
      if (iVar2 != 0) {
        directdraw_error_to_string(iVar2);
        report_error();
        return 0;
      }
    }
  }
  else {
    puVar3 = (undefined4 *)construct_bitmap_surface_context(local_434,DAT_00608400,DAT_00608404,1,0)
    ;
    puVar4 = param_1;
    for (iVar2 = 0xd; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar4 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar4 = puVar4 + 1;
    }
    query_directdraw_surface_descriptor(&DAT_00643930,DAT_006080c4);
    _DAT_00643920 = DAT_006080b8;
    _DAT_00643924 = DAT_006080c0;
    _DAT_00643928 = DAT_006080c4;
    _DAT_0064392c = DAT_006080c8;
  }
  if (param_1[0xb] == 0) {
    return 0;
  }
  puVar3 = (undefined4 *)
           construct_bitmap_surface_context
                     (local_434,(param_1[9] - param_1[7]) + 1 >> 3,(int)(param_1[1] << 3) >> 3,0,0);
  puVar4 = param_1 + 0xd;
  for (iVar2 = 0xd; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  if (param_1[0x18] == 0) {
    param_1[0x39] = 3;
    return 0;
  }
  return 1;
}


