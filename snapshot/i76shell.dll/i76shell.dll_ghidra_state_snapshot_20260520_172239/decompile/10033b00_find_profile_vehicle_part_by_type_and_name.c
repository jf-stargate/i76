/*
 * Program: i76shell.dll
 * Function: find_profile_vehicle_part_by_type_and_name
 * Entry: 10033b00
 * Signature: undefined * * __cdecl find_profile_vehicle_part_by_type_and_name(int param_1, int param_2, int * param_3)
 */


undefined ** __cdecl
find_profile_vehicle_part_by_type_and_name(int param_1,int param_2,int *param_3)

{
  int *piVar1;
  byte bVar2;
  int iVar3;
  byte *pbVar4;
  int iVar5;
  undefined4 *puVar6;
  byte *pbVar7;
  byte *pbVar8;
  bool bVar9;
  int local_8;
  
  piVar1 = param_3 + 0xf;
  local_8 = 0;
  if (*piVar1 < 1) {
    return (undefined **)0x0;
  }
  pbVar8 = (byte *)(param_3 + 0x100);
  param_3 = param_3 + 0x10;
  do {
    iVar3 = 6;
    bVar9 = true;
    pbVar7 = pbVar8;
    pbVar4 = (byte *)s_EMPTY_1004cdf4;
    do {
      if (iVar3 == 0) break;
      iVar3 = iVar3 + -1;
      bVar9 = *pbVar7 == *pbVar4;
      pbVar7 = pbVar7 + 1;
      pbVar4 = pbVar4 + 1;
    } while (bVar9);
    if (bVar9) {
      return &PTR_DAT_100432c0;
    }
    if ((*param_3 == param_1) && (iVar3 = 0, 0 < *(int *)(param_2 + 4))) {
      puVar6 = *(undefined4 **)(param_2 + 8);
      do {
        pbVar7 = *(undefined **)*puVar6;
        pbVar4 = pbVar8;
        do {
          bVar2 = *pbVar4;
          bVar9 = bVar2 < *pbVar7;
          if (bVar2 != *pbVar7) {
LAB_10033b92:
            iVar5 = (1 - (uint)bVar9) - (uint)(bVar9 != 0);
            goto LAB_10033b97;
          }
          if (bVar2 == 0) break;
          bVar2 = pbVar4[1];
          bVar9 = bVar2 < pbVar7[1];
          if (bVar2 != pbVar7[1]) goto LAB_10033b92;
          pbVar4 = pbVar4 + 2;
          pbVar7 = pbVar7 + 2;
        } while (bVar2 != 0);
        iVar5 = 0;
LAB_10033b97:
        if (iVar5 == 0) {
          return (undefined **)*puVar6;
        }
        iVar3 = iVar3 + 1;
        puVar6 = puVar6 + 1;
      } while (iVar3 < *(int *)(param_2 + 4));
    }
    local_8 = local_8 + 1;
    param_3 = param_3 + 8;
    pbVar8 = pbVar8 + 0x1e;
    if (*piVar1 <= local_8) {
      return (undefined **)0x0;
    }
  } while( true );
}


