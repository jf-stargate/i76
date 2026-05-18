/*
 * Program: i76.exe
 * Function: radar_render_context_helper_00460ea0
 * Entry: 00460ea0
 * Signature: undefined __cdecl radar_render_context_helper_00460ea0(int param_1)
 */


/* cgpt label refinement v19: was radar_classifier_specials_radar_render_helper_00460ea0. Shorten
   readability label. */

void __cdecl radar_render_context_helper_00460ea0(int param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  
  if (((*(int *)(param_1 + 0x70) != 0) &&
      (iVar1 = *(int *)(*(int *)(param_1 + 0x70) + 0x434), iVar1 != 0)) &&
     (iVar1 = *(int *)(iVar1 + 0x70), iVar1 != 0)) {
    uVar2 = *(uint *)(iVar1 + 0xc);
    uVar5 = (uint)(((byte)uVar2 & 4) != 4) << 2;
    uVar3 = uVar2 & 0xfffffffb | uVar5;
    *(uint *)(iVar1 + 0xc) = uVar3;
    if (((byte)uVar3 & 4) == 4) {
      *(uint *)(iVar1 + 0xc) = uVar2 & 0xfffffffa | uVar5;
      if (*(int *)(iVar1 + 0x54) != 0) {
        *(undefined1 *)(*(int *)(iVar1 + 0x54) + 0x1c) = 0x69;
      }
      *(undefined4 *)(iVar1 + 0x54) = 0;
      *(uint *)(iVar1 + 0xc) = *(uint *)(iVar1 + 0xc) & 0xffffffed;
      puVar6 = &DAT_004faed8;
      puVar7 = (undefined4 *)(iVar1 + 0x10);
      for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar7 = *puVar6;
        puVar6 = puVar6 + 1;
        puVar7 = puVar7 + 1;
      }
      *(undefined4 *)(iVar1 + 0x50) = 0;
    }
  }
  return;
}


