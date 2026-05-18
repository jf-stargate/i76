/*
 * Program: i76.exe
 * Function: radar_context_helper_0045f970
 * Entry: 0045f970
 * Signature: undefined __cdecl radar_context_helper_0045f970(int param_1, int param_2)
 */


/* cgpt label refinement v19: was cockpit_hud_ui_radar_context_helper_0045f970. Shorten readability
   label. */

void __cdecl radar_context_helper_0045f970(int param_1,int param_2)

{
  undefined4 *puVar1;
  int iVar2;
  bool bVar3;
  int *piVar4;
  undefined3 extraout_var;
  LPVOID pvVar5;
  uint uVar6;
  
  iVar2 = *(int *)(*(int *)(param_1 + 0x70) + 0x108);
  piVar4 = (int *)get_active_player_or_camera_world_object_entry();
  if (piVar4 != (int *)0x0) {
    bVar3 = radar_render_context_helper_00461680(*piVar4);
    uVar6 = ~*(uint *)(*(int *)(*piVar4 + 0x70) + 0x454) & 1;
    if (*(int *)(param_1 + 0x6c) == 8) {
      if ((((*(uint *)(param_1 + 0x10) & 0x200) == 0) && (CONCAT31(extraout_var,bVar3) == 0)) &&
         (uVar6 == 0)) {
        *(undefined4 **)(param_2 + 4) = &DAT_00609380;
        *(undefined4 **)(param_2 + 0x54) = &DAT_00609380;
        *(undefined4 *)(param_2 + 0x5c) = DAT_00609380;
        *(undefined4 *)(param_2 + 0x60) = DAT_00609380;
        *(undefined4 *)(param_2 + 100) = DAT_00609380;
        *(undefined4 *)(param_2 + 0x68) = DAT_00609380;
        *(undefined4 *)(param_2 + 0x6c) = DAT_00609380;
        *(undefined4 *)(param_2 + 0x70) = DAT_00609380;
        *(undefined4 *)(param_2 + 0x74) = DAT_00609380;
        *(uint *)(param_2 + 0xc) = *(uint *)(param_2 + 0xc) | 0x10;
        return;
      }
      *(undefined **)(param_2 + 4) = &DAT_00609340;
      *(undefined **)(param_2 + 0x54) = &DAT_00609340;
      *(undefined4 *)(param_2 + 0x5c) = 0;
      *(undefined4 *)(param_2 + 0x60) = 0;
      *(undefined4 *)(param_2 + 100) = 0;
      *(undefined4 *)(param_2 + 0x68) = 0;
      *(undefined4 *)(param_2 + 0x6c) = 0;
      *(undefined4 *)(param_2 + 0x70) = 0;
      *(undefined4 *)(param_2 + 0x74) = 0;
      *(uint *)(param_2 + 0xc) = *(uint *)(param_2 + 0xc) & 0xffffffef;
      return;
    }
    if ((CONCAT31(extraout_var,bVar3) == 0) && (uVar6 == 0)) {
      puVar1 = (undefined4 *)(iVar2 + 0xa9b4);
      pvVar5 = release_world_object_tree_reference(*(LPVOID *)(iVar2 + 0xa9b4),&DAT_004c2a10);
      *puVar1 = pvVar5;
      *(undefined4 **)(param_2 + 4) = puVar1;
      *(undefined4 **)(param_2 + 0x54) = puVar1;
      *(undefined4 *)(param_2 + 100) = *puVar1;
      uVar6 = *(uint *)(param_2 + 0xc) | 0x10;
    }
    else {
      *(undefined **)(param_2 + 4) = &DAT_00609340;
      *(undefined **)(param_2 + 0x54) = &DAT_00609340;
      *(undefined4 *)(param_2 + 100) = 0;
      uVar6 = *(uint *)(param_2 + 0xc) & 0xffffffef;
    }
    *(uint *)(param_2 + 0xc) = uVar6;
    *(undefined4 *)(param_2 + 0x5c) = *(undefined4 *)(iVar2 + 0xa9b4);
    *(undefined4 *)(param_2 + 0x60) = *(undefined4 *)(iVar2 + 0xa9b4);
    *(undefined4 *)(param_2 + 0x68) = *(undefined4 *)(iVar2 + 0xa9b4);
    *(undefined4 *)(param_2 + 0x6c) = *(undefined4 *)(iVar2 + 0xa9b4);
    *(undefined4 *)(param_2 + 0x70) = *(undefined4 *)(iVar2 + 0xa9b4);
    *(undefined4 *)(param_2 + 0x74) = *(undefined4 *)(iVar2 + 0xa9b4);
  }
  return;
}


