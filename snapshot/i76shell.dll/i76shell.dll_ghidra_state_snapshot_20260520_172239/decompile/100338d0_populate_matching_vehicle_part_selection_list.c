/*
 * Program: i76shell.dll
 * Function: populate_matching_vehicle_part_selection_list
 * Entry: 100338d0
 * Signature: undefined __cdecl populate_matching_vehicle_part_selection_list(undefined * param_1, int * param_2, int param_3)
 */


void __cdecl
populate_matching_vehicle_part_selection_list(undefined *param_1,int *param_2,int param_3)

{
  byte bVar1;
  int iVar2;
  byte *pbVar3;
  int iVar4;
  byte *pbVar5;
  undefined4 *puVar6;
  bool bVar7;
  int local_10;
  int local_c;
  int iStack_8;
  int local_4;
  
  local_4 = 0;
  iVar2 = *(int *)(DAT_100c5ad8 + 0x38) * 0x8c4;
  if (*(int *)(&DAT_100581dc + iVar2) != -3 && -1 < *(int *)(&DAT_100581dc + iVar2) + 3) {
    local_10 = 0;
    local_c = 0;
    do {
      iVar2 = (*(code *)param_1)(*(undefined4 *)(&DAT_100581e0 + iVar2 + local_c));
      if (iVar2 != 0) {
        iVar2 = _stricmp(&DAT_100585a0 + *(int *)(DAT_100c5ad8 + 0x38) * 0x8c4 + local_10,
                         s_EMPTY_1004cdec);
        if (iVar2 == 0) {
          insert_pointer_list_item_sorted_or_append((int)param_2,0x100432c0,(undefined *)0x0);
        }
        else {
          iVar2 = 0;
          if (0 < *(int *)(param_3 + 4)) {
            do {
              puVar6 = *(undefined4 **)(*(int *)(param_3 + 8) + iVar2 * 4);
              pbVar5 = (byte *)*puVar6;
              pbVar3 = &DAT_100585a0 + *(int *)(DAT_100c5ad8 + 0x38) * 0x8c4 + local_10;
              do {
                bVar1 = *pbVar3;
                bVar7 = bVar1 < *pbVar5;
                if (bVar1 != *pbVar5) {
LAB_100339d9:
                  iVar4 = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
                  goto LAB_100339de;
                }
                if (bVar1 == 0) break;
                bVar1 = pbVar3[1];
                bVar7 = bVar1 < pbVar5[1];
                if (bVar1 != pbVar5[1]) goto LAB_100339d9;
                pbVar3 = pbVar3 + 2;
                pbVar5 = pbVar5 + 2;
              } while (bVar1 != 0);
              iVar4 = 0;
LAB_100339de:
              if ((iVar4 == 0) &&
                 (iVar4 = find_pointer_list_item_index(param_2,(int)puVar6), iVar4 == -1)) {
                insert_pointer_list_item_sorted_or_append((int)param_2,(int)puVar6,(undefined *)0x0)
                ;
                break;
              }
              iVar2 = iVar2 + 1;
            } while (iVar2 < *(int *)(param_3 + 4));
          }
          if ((iVar2 == *(int *)(param_3 + 4)) && (iStack_8 = 0, 0 < *(int *)(param_3 + 4))) {
            puVar6 = *(undefined4 **)(param_3 + 8);
            do {
              pbVar3 = *(byte **)*puVar6;
              pbVar5 = &DAT_100585a0 + *(int *)(DAT_100c5ad8 + 0x38) * 0x8c4 + local_10;
              do {
                bVar1 = *pbVar5;
                bVar7 = bVar1 < *pbVar3;
                if (bVar1 != *pbVar3) {
LAB_10033a76:
                  iVar2 = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
                  goto LAB_10033a7b;
                }
                if (bVar1 == 0) break;
                bVar1 = pbVar5[1];
                bVar7 = bVar1 < pbVar3[1];
                if (bVar1 != pbVar3[1]) goto LAB_10033a76;
                pbVar5 = pbVar5 + 2;
                pbVar3 = pbVar3 + 2;
              } while (bVar1 != 0);
              iVar2 = 0;
LAB_10033a7b:
              if (iVar2 == 0) {
                insert_pointer_list_item_sorted_or_append
                          ((int)param_2,(int)*puVar6,(undefined *)0x0);
                break;
              }
              iStack_8 = iStack_8 + 1;
              puVar6 = puVar6 + 1;
            } while (iStack_8 < *(int *)(param_3 + 4));
          }
        }
      }
      local_4 = local_4 + 1;
      local_c = local_c + 0x20;
      local_10 = local_10 + 0x1e;
      iVar2 = *(int *)(DAT_100c5ad8 + 0x38) * 0x8c4;
    } while (local_4 < *(int *)(&DAT_100581dc + iVar2) + 3);
  }
  return;
}


