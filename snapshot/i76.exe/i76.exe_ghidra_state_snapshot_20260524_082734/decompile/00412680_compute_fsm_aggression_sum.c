/*
 * Program: i76.exe
 * Function: compute_fsm_aggression_sum
 * Entry: 00412680
 * Signature: int __cdecl compute_fsm_aggression_sum(int param_1, undefined4 param_2, int param_3, int param_4)
 */


/* cgpt whole-binary semantic rename v1: string evidence: calc_sum - agg out of bounds */

int __cdecl compute_fsm_aggression_sum(int param_1,undefined4 param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  undefined4 *local_4c;
  int local_48;
  int local_44;
  int local_40 [16];
  
  local_48 = 0;
  local_44 = 0;
  iVar6 = *(int *)(*(int *)(*(int *)(param_1 + 0x70) + 0x108) + 0xa818);
  if ((iVar6 < 0) || (4 < iVar6)) {
    report_error();
  }
  iVar4 = param_4 * 0x1d8 + param_3 * 0x1354;
  iVar2 = *(int *)(&DAT_004c3f34 + iVar4);
  if (0 < iVar2) {
    piVar3 = (int *)(&DAT_004c3f78 + iVar4 + iVar6 * 0x40);
    iVar6 = iVar2;
    do {
      local_48 = local_48 + *piVar3;
      piVar3 = piVar3 + 1;
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
  }
  if (0 < local_48) {
    if (0 < iVar2) {
      piVar3 = (int *)(&DAT_004c3f78 +
                      param_3 * 0x1354 +
                      param_4 * 0x1d8 +
                      *(int *)(*(int *)(*(int *)(param_1 + 0x70) + 0x108) + 0xa818) * 0x40);
      piVar7 = local_40;
      for (; iVar2 != 0; iVar2 = iVar2 + -1) {
        *piVar7 = *piVar3;
        piVar3 = piVar3 + 1;
        piVar7 = piVar7 + 1;
      }
    }
    do {
      iVar6 = rand();
      iVar6 = iVar6 % local_48;
      iVar4 = 0;
      if (local_40[0] <= iVar6) {
        piVar3 = local_40;
        iVar2 = local_40[0];
        do {
          piVar3 = piVar3 + 1;
          iVar6 = iVar6 - iVar2;
          iVar4 = iVar4 + 1;
          iVar2 = *piVar3;
        } while (iVar2 <= iVar6);
      }
      iVar5 = 0;
      iVar6 = *(int *)(&DAT_004c3f38 + (iVar4 + param_3 * 0x4d5) * 4 + param_4 * 0x1d8);
      iVar2 = *(int *)(&DAT_004c3e5c + iVar6 * 0x1354);
      if (iVar2 < 1) {
        return iVar6;
      }
      local_4c = (undefined4 *)(&DAT_004c3e60 + iVar6 * 0x1354);
      while (iVar1 = (*(code *)*local_4c)(param_1,param_2), iVar1 != 0) {
        iVar5 = iVar5 + 1;
        local_4c = local_4c + 1;
        if (iVar2 <= iVar5) {
          return iVar6;
        }
      }
      local_48 = local_48 - local_40[iVar4];
      local_44 = local_44 + 1;
      local_40[iVar4] = 0;
    } while ((local_44 < 0x12) && (0 < local_48));
  }
  return 0xf;
}


