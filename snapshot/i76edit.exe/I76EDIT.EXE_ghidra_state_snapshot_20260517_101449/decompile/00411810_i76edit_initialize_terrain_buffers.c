/*
 * Program: I76EDIT.EXE
 * Function: i76edit_initialize_terrain_buffers
 * Entry: 00411810
 * Signature: undefined __cdecl i76edit_initialize_terrain_buffers(int param_1)
 */


/* [cgpt_i76edit_level_renames_v2:medium] References 'Initializing Terrain...' and 'Initializing
   Painted Terrain...'; called from terrain setup paths. */

void __cdecl i76edit_initialize_terrain_buffers(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  
  uVar4 = DAT_00433a70 & 0xffff | DAT_00433a70 << 0x10;
  if (param_1 == 0) {
    i76edit_set_status_bar_text(s_Initializing_Terrain____00434a48);
    puVar1 = &DAT_009bc820;
    for (iVar2 = 0xa0050; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar1 = 0;
      puVar1 = puVar1 + 1;
    }
    i76edit_set_status_bar_text(s_Initializing_Surface____00434a2c);
    thunk_FUN_004117f0(&DAT_00ebcaa0,uVar4,0x280140);
    i76edit_set_status_bar_text(s_Initializing_Painted_Surface____00434a04);
    thunk_FUN_004117f0(&DAT_00c3c960,&DAT_00630063,0x280140);
    i76edit_set_status_bar_text(s_Initializing_Workspace____004349e4);
    puVar1 = &DAT_013bcd20;
    for (iVar2 = 0xa0050; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar1 = 0;
      puVar1 = puVar1 + 1;
    }
    i76edit_set_status_bar_text(s_Initializing_Painted_Terrain____004349bc);
    thunk_FUN_004117f0(&DAT_0113cbe0,0x80008000,0x280140);
    iVar2 = 0;
    do {
      *(undefined4 *)((int)&DAT_00ebcaa0 + iVar2) = 0;
      *(undefined4 *)((int)&DAT_0113cbe0 + iVar2) = 0;
      *(undefined4 *)((int)&DAT_00c3c960 + iVar2) = 0;
      iVar2 = iVar2 + 0x8004;
    } while (iVar2 < 0x280140);
  }
  else {
    if (param_1 == 2) {
      i76edit_set_status_bar_text(s_Initializing_Surface____00434a2c);
      thunk_FUN_004117f0(&DAT_00ebcaa0,uVar4,0x280140);
      puVar1 = &DAT_00ebcaa0;
      do {
        *puVar1 = 0;
        puVar1 = puVar1 + 0x2001;
      } while (puVar1 < &DAT_0113cbe0);
      i76edit_set_status_bar_text(s_Ready_004346ec);
      return;
    }
    if (param_1 == 1) {
      thunk_FUN_004117f0(&DAT_00ebcaa0,uVar4,0x280140);
      i76edit_set_status_bar_text(s_Initializing_Surface____00434a2c);
      puVar1 = &DAT_00ebcaa0;
      do {
        *puVar1 = 0;
        puVar1 = puVar1 + 0x2001;
      } while (puVar1 < &DAT_0113cbe0);
    }
    else {
      if (param_1 == 4) {
        i76edit_set_status_bar_text(s_Initializing_Painted_Surface____00434a04);
        thunk_FUN_004117f0(&DAT_00c3c960,&DAT_00630063,0x280140);
        puVar1 = &DAT_00c3c960;
        do {
          *puVar1 = 0;
          puVar1 = puVar1 + 0x2001;
        } while (puVar1 < &DAT_00ebcaa0);
        i76edit_set_status_bar_text(s_Ready_004346ec);
        return;
      }
      if (param_1 == 3) {
        i76edit_set_status_bar_text(s_Initializing_Painted_Terrain____004349bc);
        thunk_FUN_004117f0(&DAT_0113cbe0,0x80008000,0x280140);
        i76edit_set_status_bar_text(s_Ready_004346ec);
        return;
      }
    }
  }
  i76edit_set_status_bar_text(s_Initializing_Workspace____004349e4);
  iVar5 = 0;
  thunk_FUN_004117f0(&DAT_0043c550,0x80008000,0x280140);
  iVar2 = 0;
  do {
    if (param_1 == 0) {
      *(undefined4 *)((int)&DAT_009bc820 + iVar2) = 0;
    }
    *(undefined4 *)((int)&DAT_0043c550 + iVar2) = 0;
    if (param_1 == 0) {
      puVar1 = (undefined4 *)(&DAT_00439ef0 + iVar5);
      for (iVar3 = 0x14; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar1 = 0xffffffff;
        puVar1 = puVar1 + 1;
      }
    }
    iVar5 = iVar5 + 0x50;
    iVar2 = iVar2 + 0x8004;
  } while (iVar2 < 0x280140);
  i76edit_set_status_bar_text(s_Ready_004346ec);
  return;
}


