/*
 * Program: i76.exe
 * Function: cockpit_gauge_context_helper_004598b0
 * Entry: 004598b0
 * Signature: undefined __cdecl cockpit_gauge_context_helper_004598b0(int param_1)
 */


/* cgpt label refinement v19: was cockpit_hud_ui_cockpit_gauge_helper_004598b0. Remove duplicated
   cockpit wording. */

void __cdecl cockpit_gauge_context_helper_004598b0(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  puVar1 = *(undefined4 **)(param_1 + 0x70);
  iVar2 = get_root_ancestor_world_object(param_1);
  if (iVar2 != 0) {
    *(int *)(*(int *)(iVar2 + 0x70) + 0x3a8 + puVar1[0x10] * 4) = param_1;
  }
  puVar3 = (undefined4 *)(param_1 + 0x18);
  puVar4 = puVar1;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  puVar1[0x11] = 0;
  puVar1[0x12] = 0;
  return;
}


