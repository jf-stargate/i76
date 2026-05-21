/*
 * Program: i76.exe
 * Function: radar_render_context_helper_00460f20
 * Entry: 00460f20
 * Signature: undefined __cdecl radar_render_context_helper_00460f20(int * param_1)
 */


/* cgpt label refinement v19: was radar_classifier_specials_radar_render_helper_00460f20. Shorten
   readability label. */

void __cdecl radar_render_context_helper_00460f20(int *param_1)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  undefined4 *puVar7;
  int *piVar8;
  undefined4 *puVar9;
  
  uVar6 = (uint)param_1[4] >> 0x10 & 7;
  if ((((param_1[0x1c] != 0) && (iVar1 = *(int *)(param_1[0x1c] + 0x434), iVar1 != 0)) &&
      (iVar1 = *(int *)(iVar1 + 0x70), iVar1 != 0)) &&
     (((*(uint *)(iVar1 + 0xc) & 1) != 0 && (((byte)*(uint *)(iVar1 + 0xc) & 4) != 4)))) {
    piVar2 = *(int **)(iVar1 + 4);
    piVar3 = *(int **)(iVar1 + 0x54);
    if (piVar2 == (int *)0x0) {
      if (piVar3 != (int *)0x0) {
        *(undefined1 *)(piVar3 + 7) = 0x69;
      }
      *(undefined4 *)(iVar1 + 0x54) = 0;
      *(uint *)(iVar1 + 0xc) = *(uint *)(iVar1 + 0xc) & 0xffffffed;
      puVar7 = &DAT_004faed8;
      puVar9 = (undefined4 *)(iVar1 + 0x10);
      for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
        *puVar9 = *puVar7;
        puVar7 = puVar7 + 1;
        puVar9 = puVar9 + 1;
      }
      *(undefined4 *)(iVar1 + 0x50) = 0;
      return;
    }
    piVar8 = piVar2;
    param_1 = piVar2;
    if ((piVar3 != (int *)0x0) &&
       (piVar8 = (int *)piVar3[8], param_1 = piVar3, (int *)piVar3[8] == (int *)0x0)) {
      piVar8 = piVar2;
    }
    do {
      uVar4 = vehicle_damage_component_runtime_context_helper_00466de0(*piVar8);
      if (uVar4 != 0) {
        uVar4 = *(uint *)(*piVar8 + 0x10) >> 0x10 & 7;
        iVar5 = is_damage_side_effects_suppressed();
        if ((iVar5 != 0) && (uVar4 != uVar6)) {
          *(undefined1 *)(param_1 + 7) = 0x69;
          *(undefined1 *)(piVar8 + 7) = 0;
          *(int **)(iVar1 + 0x54) = piVar8;
          *(uint *)(iVar1 + 0xc) = *(uint *)(iVar1 + 0xc) | 0x10;
          return;
        }
        if ((uVar4 != 0) && (uVar4 != uVar6)) {
          *(undefined1 *)(param_1 + 7) = 0x69;
          *(undefined1 *)(piVar8 + 7) = 0;
          *(int **)(iVar1 + 0x54) = piVar8;
          *(uint *)(iVar1 + 0xc) = *(uint *)(iVar1 + 0xc) | 0x10;
          return;
        }
      }
      piVar8 = (int *)piVar8[8];
      if (piVar8 == (int *)0x0) {
        piVar8 = *(int **)(iVar1 + 4);
      }
    } while (piVar8 != param_1);
  }
  return;
}


