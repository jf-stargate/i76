/*
 * Program: i76.exe
 * Function: select_best_display_driver_for_caps_mask
 * Entry: 004337e0
 * Signature: undefined4 __cdecl select_best_display_driver_for_caps_mask(int * param_1, uint param_2)
 */


/* cgpt readability rename v13 set A: Selects the best enumerated display/D3D driver matching a
   capability mask and preference flags. */

undefined4 __cdecl select_best_display_driver_for_caps_mask(int *param_1,uint param_2)

{
  int iVar1;
  uint *puVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar1 = 0;
  if (0 < DAT_005fde50) {
    puVar2 = &DAT_005fdf44;
    do {
      if ((*puVar2 & param_2) != 0) break;
      iVar1 = iVar1 + 1;
      puVar2 = puVar2 + 0x4f;
    } while (iVar1 < DAT_005fde50);
  }
  if (DAT_005fde50 <= iVar1) {
    *param_1 = -100;
    return 1;
  }
  iVar5 = 0;
  if (0 < DAT_005fde50) {
    iVar4 = iVar1 * 0x13c;
    iVar3 = 0;
    do {
      if (((*(uint *)((int)&DAT_005fdf44 + iVar3) & param_2) != 0) &&
         (((*(int *)((int)&DAT_005fdf84 + iVar3) != 0 && (*(int *)((int)&DAT_005fdf84 + iVar4) == 0)
           ) || ((*(int *)((int)&DAT_005fdf84 + iVar3) == *(int *)((int)&DAT_005fdf84 + iVar4) &&
                 ((((&DAT_005fdeb0)[iVar3] & 1) != 0 && (((&DAT_005fdeb0)[iVar4] & 1) == 0)))))))) {
        iVar1 = iVar5;
        iVar4 = iVar3;
      }
      iVar5 = iVar5 + 1;
      iVar3 = iVar3 + 0x13c;
    } while (iVar5 < DAT_005fde50);
  }
  if (DAT_005fde50 <= iVar1) {
    *param_1 = -100;
    return 1;
  }
  *param_1 = iVar1;
  return 1;
}


