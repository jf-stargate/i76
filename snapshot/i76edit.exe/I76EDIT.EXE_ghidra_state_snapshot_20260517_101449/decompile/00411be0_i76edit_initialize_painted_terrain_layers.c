/*
 * Program: I76EDIT.EXE
 * Function: i76edit_initialize_painted_terrain_layers
 * Entry: 00411be0
 * Signature: undefined4 __cdecl i76edit_initialize_painted_terrain_layers(int param_1)
 */


/* [cgpt_i76edit_level_renames_v2:medium] References 'Initializing Terrain...' and 'Initializing
   Painted Terrain...'; likely layer/buffer setup wrapper. */

undefined4 __cdecl i76edit_initialize_painted_terrain_layers(int param_1)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  undefined2 *puVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  undefined2 *puVar9;
  undefined4 *puVar10;
  undefined4 *puVar11;
  int local_1c;
  
  uVar6 = DAT_00433a70 & 0xffff;
  uVar2 = DAT_00433a70 << 0x10;
  bVar1 = false;
  iVar3 = 0;
  local_1c = -1;
  iVar7 = 0;
  do {
    iVar8 = 0;
    do {
      if ((char)(&DAT_00439ef0)[iVar8 + iVar3] == param_1) {
        bVar1 = true;
        break;
      }
      iVar8 = iVar8 + 1;
    } while (iVar8 < 0x50);
    if (bVar1) break;
    iVar3 = iVar3 + 0x50;
    iVar7 = iVar7 + 1;
  } while (iVar3 < 0x1900);
  iVar3 = 0;
  piVar4 = &DAT_009bc820;
  do {
    if (*piVar4 != 0) {
      local_1c = iVar3;
    }
    piVar4 = piVar4 + 0x2001;
    iVar3 = iVar3 + 1;
  } while (piVar4 < &DAT_00c3c960);
  if ((char)(&DAT_00439ef0)[iVar8 + iVar7 * 0x50] == local_1c) {
    local_1c = -1;
  }
  if ((iVar7 == 0x50) && (iVar8 == 0x50)) {
    return 0;
  }
  (&DAT_00439ef0)[iVar8 + iVar7 * 0x50] = 0xff;
  if (-1 < local_1c) {
    iVar7 = 0;
    bVar1 = false;
    iVar3 = 0;
    do {
      iVar8 = 0;
      do {
        if ((char)(&DAT_00439ef0)[iVar8 + iVar7] == local_1c) {
          bVar1 = true;
          break;
        }
        iVar8 = iVar8 + 1;
      } while (iVar8 < 0x50);
      if (bVar1) break;
      iVar7 = iVar7 + 0x50;
      iVar3 = iVar3 + 1;
    } while (iVar7 < 0x1900);
    (&DAT_00439ef0)[iVar8 + iVar3 * 0x50] = (char)param_1;
    thunk_FUN_00409dc0(param_1);
    iVar3 = 0x32;
    puVar5 = &DAT_0163ce72 + param_1 * 100;
    do {
      *puVar5 = 0xffff;
      iVar3 = iVar3 + -1;
      *(undefined1 *)(puVar5 + -1) = 0xff;
      *(undefined1 *)((int)puVar5 + -1) = 0xff;
      puVar5 = puVar5 + 2;
    } while (iVar3 != 0);
    i76edit_set_status_bar_text(s_Initializing_Terrain____00434a48);
    puVar10 = &DAT_009bc820 + local_1c * 0x2001;
    puVar11 = &DAT_009bc820 + param_1 * 0x2001;
    for (iVar3 = 0x2001; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar11 = *puVar10;
      puVar10 = puVar10 + 1;
      puVar11 = puVar11 + 1;
    }
    i76edit_set_status_bar_text(s_Initializing_Surface____00434a2c);
    puVar10 = &DAT_00ebcaa0 + local_1c * 0x2001;
    puVar11 = &DAT_00ebcaa0 + param_1 * 0x2001;
    for (iVar3 = 0x2001; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar11 = *puVar10;
      puVar10 = puVar10 + 1;
      puVar11 = puVar11 + 1;
    }
    i76edit_set_status_bar_text(s_Initializing_Painted_Surface____00434a04);
    puVar10 = &DAT_00c3c960 + local_1c * 0x2001;
    puVar11 = &DAT_00c3c960 + param_1 * 0x2001;
    for (iVar3 = 0x2001; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar11 = *puVar10;
      puVar10 = puVar10 + 1;
      puVar11 = puVar11 + 1;
    }
    i76edit_set_status_bar_text(s_Initializing_Workspace____004349e4);
    puVar10 = &DAT_013bcd20 + local_1c * 0x2001;
    puVar11 = &DAT_013bcd20 + param_1 * 0x2001;
    for (iVar3 = 0x2001; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar11 = *puVar10;
      puVar10 = puVar10 + 1;
      puVar11 = puVar11 + 1;
    }
    i76edit_set_status_bar_text(s_Initializing_Painted_Terrain____004349bc);
    puVar10 = &DAT_0113cbe0 + local_1c * 0x2001;
    puVar11 = &DAT_0113cbe0 + param_1 * 0x2001;
    for (iVar3 = 0x2001; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar11 = *puVar10;
      puVar10 = puVar10 + 1;
      puVar11 = puVar11 + 1;
    }
    (&DAT_0113cbe0)[param_1 * 0x2001] = 1;
    (&DAT_00ebcaa0)[param_1 * 0x2001] = 1;
    (&DAT_00c3c960)[param_1 * 0x2001] = 1;
    (&DAT_009bc820)[param_1 * 0x2001] = 1;
    i76edit_set_status_bar_text(s_Initializing_Workspace____004349e4);
    puVar10 = &DAT_0043c550 + local_1c * 0x2001;
    puVar11 = &DAT_0043c550 + param_1 * 0x2001;
    for (iVar3 = 0x2001; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar11 = *puVar10;
      puVar10 = puVar10 + 1;
      puVar11 = puVar11 + 1;
    }
    iVar3 = 0x32;
    puVar5 = &DAT_0163ce72 + local_1c * 100;
    puVar9 = &DAT_0163ce72 + param_1 * 100;
    do {
      *puVar9 = *puVar5;
      iVar3 = iVar3 + -1;
      *(undefined1 *)(puVar9 + -1) = *(undefined1 *)(puVar5 + -1);
      *(undefined1 *)((int)puVar9 + -1) = *(undefined1 *)((int)puVar5 + -1);
      puVar5 = puVar5 + 2;
      puVar9 = puVar9 + 2;
    } while (iVar3 != 0);
    thunk_FUN_00409e00(param_1,local_1c);
    i76edit_export_height_txt_debug_view(param_1);
    param_1 = local_1c;
  }
  i76edit_set_status_bar_text(s_Initializing_Terrain____00434a48);
  puVar10 = &DAT_009bc820 + param_1 * 0x2001;
  for (iVar3 = 0x2001; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar10 = 0;
    puVar10 = puVar10 + 1;
  }
  i76edit_set_status_bar_text(s_Initializing_Surface____00434a2c);
  thunk_FUN_004117f0(&DAT_00ebcaa0 + param_1 * 0x2001,uVar6 | uVar2,0x8004);
  i76edit_set_status_bar_text(s_Initializing_Painted_Surface____00434a04);
  thunk_FUN_004117f0(&DAT_00c3c960 + param_1 * 0x2001,&DAT_00630063,0x8004);
  i76edit_set_status_bar_text(s_Initializing_Workspace____004349e4);
  puVar10 = &DAT_013bcd20 + param_1 * 0x2001;
  for (iVar3 = 0x2001; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar10 = 0;
    puVar10 = puVar10 + 1;
  }
  i76edit_set_status_bar_text(s_Initializing_Painted_Terrain____004349bc);
  thunk_FUN_004117f0(&DAT_0113cbe0 + param_1 * 0x2001,0x80008000,0x8004);
  (&DAT_0113cbe0)[param_1 * 0x2001] = 0;
  (&DAT_00ebcaa0)[param_1 * 0x2001] = 0;
  (&DAT_00c3c960)[param_1 * 0x2001] = 0;
  i76edit_set_status_bar_text(s_Initializing_Workspace____004349e4);
  thunk_FUN_004117f0(&DAT_0043c550 + param_1 * 0x2001,0x80008000,0x8004);
  iVar3 = 0x32;
  puVar5 = &DAT_0163ce72 + param_1 * 100;
  do {
    *puVar5 = 0xffff;
    iVar3 = iVar3 + -1;
    *(undefined1 *)(puVar5 + -1) = 0xff;
    *(undefined1 *)((int)puVar5 + -1) = 0xff;
    puVar5 = puVar5 + 2;
  } while (iVar3 != 0);
  thunk_FUN_00409dc0(param_1);
  thunk_FUN_004160c0();
  thunk_FUN_00403260();
  (&DAT_009bc820)[param_1 * 0x2001] = 0;
  i76edit_export_height_txt_debug_view(param_1);
  InvalidateRgn(DAT_01641fb4,(HRGN)0x0,0);
  i76edit_set_status_bar_text(s_Ready_004346ec);
  return 1;
}


