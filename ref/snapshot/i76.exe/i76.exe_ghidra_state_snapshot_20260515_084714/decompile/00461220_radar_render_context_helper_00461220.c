/*
 * Program: i76.exe
 * Function: radar_render_context_helper_00461220
 * Entry: 00461220
 * Signature: undefined __cdecl radar_render_context_helper_00461220(int param_1)
 */


/* cgpt label refinement v19: was radar_classifier_specials_radar_render_helper_00461220. Shorten
   readability label. */

void __cdecl radar_render_context_helper_00461220(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  if (((*(int *)(param_1 + 0x70) != 0) &&
      (iVar1 = *(int *)(*(int *)(param_1 + 0x70) + 0x434), iVar1 != 0)) &&
     (iVar1 = *(int *)(iVar1 + 0x70), iVar1 != 0)) {
    if (*(int *)(iVar1 + 0x54) != 0) {
      *(undefined1 *)(*(int *)(iVar1 + 0x54) + 0x1c) = 0x69;
    }
    *(uint *)(iVar1 + 0xc) = *(uint *)(iVar1 + 0xc) & 0xffffffed;
    *(undefined4 *)(iVar1 + 0x54) = 0;
    puVar3 = &DAT_004faed8;
    puVar4 = (undefined4 *)(iVar1 + 0x10);
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar4 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar4 = puVar4 + 1;
    }
    *(undefined4 *)(iVar1 + 0x50) = 0;
  }
  return;
}


