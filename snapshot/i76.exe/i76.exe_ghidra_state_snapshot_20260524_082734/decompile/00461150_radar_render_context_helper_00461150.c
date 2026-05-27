/*
 * Program: i76.exe
 * Function: radar_render_context_helper_00461150
 * Entry: 00461150
 * Signature: undefined __cdecl radar_render_context_helper_00461150(int param_1, int param_2)
 */


/* cgpt label refinement v19: was radar_classifier_specials_radar_render_helper_00461150. Shorten
   readability label. */

void __cdecl radar_render_context_helper_00461150(int param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  
  if ((((*(int *)(param_1 + 0x70) != 0) &&
       (iVar1 = *(int *)(*(int *)(param_1 + 0x70) + 0x434), iVar1 != 0)) &&
      (iVar1 = *(int *)(iVar1 + 0x70), iVar1 != 0)) &&
     (((*(uint *)(iVar1 + 0xc) & 1) != 0 && (((byte)*(uint *)(iVar1 + 0xc) & 4) != 4)))) {
    piVar2 = *(int **)(iVar1 + 4);
    if (param_2 == 1) {
      param_1 = *(int *)(iVar1 + 0x68);
    }
    if (param_2 == 2) {
      param_1 = *(int *)(iVar1 + 0x6c);
    }
    if (param_2 == 8) {
      param_1 = *(int *)(iVar1 + 0x70);
    }
    if (param_2 == 0x10) {
      param_1 = *(int *)(iVar1 + 0x74);
    }
    if (piVar2 != (int *)0x0) {
      do {
        if (*piVar2 == param_1) break;
        piVar2 = (int *)piVar2[8];
      } while (piVar2 != (int *)0x0);
      if (piVar2 != (int *)0x0) {
        if (*(int *)(iVar1 + 0x54) != 0) {
          *(undefined1 *)(*(int *)(iVar1 + 0x54) + 0x1c) = 0x69;
        }
        *(int **)(iVar1 + 0x54) = piVar2;
        *(undefined1 *)(piVar2 + 7) = 0;
        *(uint *)(iVar1 + 0xc) = *(uint *)(iVar1 + 0xc) | 0x10;
        return;
      }
    }
    if (*(int *)(iVar1 + 0x54) != 0) {
      *(undefined1 *)(*(int *)(iVar1 + 0x54) + 0x1c) = 0x69;
    }
    *(undefined4 *)(iVar1 + 0x54) = 0;
    *(uint *)(iVar1 + 0xc) = *(uint *)(iVar1 + 0xc) & 0xffffffed;
    puVar4 = &DAT_004faed8;
    puVar5 = (undefined4 *)(iVar1 + 0x10);
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar5 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar5 = puVar5 + 1;
    }
    *(undefined4 *)(iVar1 + 0x50) = 0;
  }
  return;
}


