/*
 * Program: i76shell.dll
 * Function: find_current_vehicle_part_by_type_and_name
 * Entry: 100337b0
 * Signature: undefined * * __cdecl find_current_vehicle_part_by_type_and_name(int param_1, int param_2)
 */


undefined ** __cdecl find_current_vehicle_part_by_type_and_name(int param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  byte *pbVar4;
  int iVar5;
  undefined4 *puVar6;
  byte *pbVar7;
  byte *pbVar8;
  bool bVar9;
  int *local_10;
  int local_8;
  
  local_8 = 0;
  iVar2 = *(int *)(DAT_100c5ad8 + 0x38) * 0x8c4;
  if (*(int *)(&DAT_100581dc + iVar2) < 1) {
    return (undefined **)0x0;
  }
  pbVar8 = &DAT_100585a0 + iVar2;
  local_10 = (int *)(&DAT_100581e0 + iVar2);
  do {
    iVar3 = 6;
    bVar9 = true;
    pbVar7 = pbVar8;
    pbVar4 = (byte *)s_EMPTY_1004cde4;
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
    if ((*local_10 == param_1) && (iVar3 = 0, 0 < *(int *)(param_2 + 4))) {
      puVar6 = *(undefined4 **)(param_2 + 8);
      do {
        pbVar7 = *(undefined **)*puVar6;
        pbVar4 = pbVar8;
        do {
          bVar1 = *pbVar4;
          bVar9 = bVar1 < *pbVar7;
          if (bVar1 != *pbVar7) {
LAB_1003385e:
            iVar5 = (1 - (uint)bVar9) - (uint)(bVar9 != 0);
            goto LAB_10033863;
          }
          if (bVar1 == 0) break;
          bVar1 = pbVar4[1];
          bVar9 = bVar1 < pbVar7[1];
          if (bVar1 != pbVar7[1]) goto LAB_1003385e;
          pbVar4 = pbVar4 + 2;
          pbVar7 = pbVar7 + 2;
        } while (bVar1 != 0);
        iVar5 = 0;
LAB_10033863:
        if (iVar5 == 0) {
          return (undefined **)*puVar6;
        }
        iVar3 = iVar3 + 1;
        puVar6 = puVar6 + 1;
      } while (iVar3 < *(int *)(param_2 + 4));
    }
    local_8 = local_8 + 1;
    local_10 = local_10 + 8;
    pbVar8 = pbVar8 + 0x1e;
    if (*(int *)(&DAT_100581dc + iVar2) <= local_8) {
      return (undefined **)0x0;
    }
  } while( true );
}


