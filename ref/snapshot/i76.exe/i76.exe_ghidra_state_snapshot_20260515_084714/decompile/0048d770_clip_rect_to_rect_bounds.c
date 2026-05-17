/*
 * Program: i76.exe
 * Function: clip_rect_to_rect_bounds
 * Entry: 0048d770
 * Signature: undefined4 __cdecl clip_rect_to_rect_bounds(int * param_1, int * param_2)
 */


/* [cgpt i76.exe damage dispatch rename v19; confidence=HIGH] Clips one four-int rectangle against
   another; returns -1 fully outside, 0 unchanged, 1 clipped. */

undefined4 __cdecl clip_rect_to_rect_bounds(int *param_1,int *param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  iVar1 = *param_2;
  uVar2 = (((param_1[1] - param_2[1] & 0x80000003U |
            (param_1[1] - param_2[3]) - 1U >> 1 & 0x40000000) >> 1 |
           (*param_1 - param_2[2]) - 1U & 0x80000001) >> 1 | *param_1 - iVar1 & 0x80000000U) ^
          0x50000000;
  uVar3 = (((param_1[3] - param_2[1] & 0x80000003U |
            (param_1[3] - param_2[3]) - 1U >> 1 & 0x40000000) >> 1 |
           (param_1[2] - param_2[2]) - 1U & 0x80000001) >> 1 | param_1[2] - iVar1 & 0x80000000U) ^
          0x50000000;
  if ((uVar2 & uVar3) != 0) {
    return 0xffffffff;
  }
  if (uVar3 == 0 && uVar2 == 0) {
    return 0;
  }
  if ((uVar2 & 0x80000000) != 0) {
    *param_1 = iVar1;
  }
  if ((uVar2 & 0x20000000) != 0) {
    param_1[1] = param_2[1];
  }
  if ((uVar3 & 0x40000000) != 0) {
    param_1[2] = param_2[2];
  }
  if ((uVar3 & 0x10000000) != 0) {
    param_1[3] = param_2[3];
  }
  return 1;
}


