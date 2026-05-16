/*
 * Program: i76.exe
 * Function: initialize_640x480_display_surface_context
 * Entry: 00434100
 * Signature: undefined4 __cdecl initialize_640x480_display_surface_context(undefined4 * param_1, int param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v2: Initializes 640x480 display/surface context for shell/windowed or full mode. */

undefined4 __cdecl initialize_640x480_display_surface_context(undefined4 *param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  uint uVar3;
  undefined4 *puVar4;
  int *local_484;
  undefined4 local_480;
  undefined4 local_47c;
  undefined4 local_474;
  undefined4 local_470;
  undefined4 local_46c;
  undefined4 local_468;
  undefined4 local_464;
  undefined4 local_460;
  undefined4 local_45c;
  undefined4 local_458;
  undefined4 local_448;
  undefined4 local_444;
  undefined4 local_440;
  HWND local_438;
  int local_434 [4];
  undefined4 local_424;
  undefined4 local_420;
  undefined4 local_41c;
  undefined4 local_418;
  undefined4 auStack_400 [256];
  
  DAT_005fff34 = 1;
  DAT_00608400 = 0x280;
  DAT_00608404 = 0x1e0;
  if (param_2 == 0) {
    DAT_00608408 = 8;
    uVar3 = 3;
  }
  else {
    DAT_00608408 = 0x10;
    uVar3 = 0;
  }
  if (uVar3 == 0) {
    local_434[2] = 0x1e0;
    local_444 = 0x1e0;
    local_484 = local_434;
    local_434[1] = 0x500;
    local_424 = 0;
    local_420 = 0;
    local_41c = 0x27f;
    local_418 = 0x1df;
    local_464 = 0;
    local_460 = 0;
    local_47c = 0x300;
    local_470 = 0x40ffffff;
    local_474 = 1;
    local_46c = 0x43fa0000;
    local_468 = 0x48f42400;
    local_45c = 0x400;
    local_480 = 8;
    local_458 = 0;
    local_448 = 0x280;
    local_440 = 32000;
    local_438 = (HWND)param_1[0x2f];
    iVar1 = (*DAT_00608ba8)(&local_484);
    uVar3 = (uint)(iVar1 == 0);
  }
  else {
    uVar3 = init_display_mode_shell_or_windowed_candidate(uVar3,(HWND)param_1[0x2f],0,0,0,0);
  }
  if (uVar3 == 0) {
    return 0;
  }
  if (param_2 == 1) {
    (*(code *)param_1[0xff])(param_1);
    (*(code *)param_1[0x100])(param_1);
    if (DAT_005fff34 == 1) {
      puVar2 = auStack_400;
      for (iVar1 = 0x100; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar2 = 0;
        puVar2 = puVar2 + 1;
      }
    }
  }
  else {
    puVar2 = (undefined4 *)construct_bitmap_surface_context(local_434,DAT_00608400,DAT_00608404,1,0)
    ;
    puVar4 = param_1;
    for (iVar1 = 0xd; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar4 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar4 = puVar4 + 1;
    }
    query_directdraw_surface_descriptor(&DAT_00643930,DAT_006080c4);
    _DAT_00643920 = DAT_006080b8;
    _DAT_00643924 = DAT_006080c0;
    _DAT_00643928 = DAT_006080c4;
    _DAT_0064392c = DAT_006080c8;
  }
  if (param_1[0xb] != 0) {
    puVar2 = (undefined4 *)
             construct_bitmap_surface_context
                       (local_434,(param_1[9] - param_1[7]) + 1 >> 3,(int)(param_1[1] << 3) >> 3,0,0
                       );
    puVar4 = param_1 + 0xd;
    for (iVar1 = 0xd; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar4 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar4 = puVar4 + 1;
    }
    if (param_1[0x18] != 0) {
      return 1;
    }
    param_1[0x39] = 3;
    return 0;
  }
  return 0;
}


