/*
 * Program: i76shell.dll
 * Function: populate_equipped_vehicle_part_selection_list
 * Entry: 10033d90
 * Signature: undefined __cdecl populate_equipped_vehicle_part_selection_list(undefined * param_1, int param_2, int param_3)
 */


void __cdecl
populate_equipped_vehicle_part_selection_list(undefined *param_1,int param_2,int param_3)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  byte *pbVar4;
  byte *pbVar5;
  bool bVar6;
  char *_Str1;
  undefined **ppuVar7;
  int local_10;
  int iStack_c;
  int local_8;
  int local_4;
  
  local_4 = 0;
  iVar2 = *(int *)(DAT_100c5ad8 + 0x38) * 0x8c4;
  if (*(int *)(&DAT_100581dc + iVar2) != -3 && -1 < *(int *)(&DAT_100581dc + iVar2) + 3) {
    local_10 = 0;
    local_8 = 0;
    do {
      iVar2 = (*(code *)param_1)(*(undefined4 *)(&DAT_100581e0 + iVar2 + local_8));
      if (iVar2 != 0) {
        iVar2 = _stricmp(&DAT_100585a0 + *(int *)(DAT_100c5ad8 + 0x38) * 0x8c4 + local_10,
                         s_EMPTY_1004ce04);
        if (iVar2 == 0) {
          ppuVar7 = &PTR_DAT_100432c0;
LAB_10033f17:
          insert_pointer_list_item_sorted_or_append(param_2,(int)ppuVar7,(undefined *)0x0);
        }
        else {
          iStack_c = 0;
          if (0 < *(int *)(param_3 + 4)) {
            do {
              ppuVar7 = *(undefined ***)(*(int *)(param_3 + 8) + iStack_c * 4);
              iVar2 = *(int *)(DAT_100c5ad8 + 0x38) * 0x8c4;
              pbVar4 = &DAT_100585a0 + iVar2 + local_10;
              pbVar5 = *ppuVar7;
              do {
                bVar1 = *pbVar4;
                bVar6 = bVar1 < *pbVar5;
                if (bVar1 != *pbVar5) {
LAB_10033ea2:
                  iVar3 = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
                  goto LAB_10033ea7;
                }
                if (bVar1 == 0) break;
                bVar1 = pbVar4[1];
                bVar6 = bVar1 < pbVar5[1];
                if (bVar1 != pbVar5[1]) goto LAB_10033ea2;
                pbVar4 = pbVar4 + 2;
                pbVar5 = pbVar5 + 2;
              } while (bVar1 != 0);
              iVar3 = 0;
LAB_10033ea7:
              if (iVar3 == 0) {
                if (*(int *)(param_2 + 4) < 2) {
                  _Str1 = &DAT_100589da + iVar2;
                }
                else {
                  _Str1 = &DAT_100589f4 + iVar2;
                  if ((&DAT_100589f4)[iVar2] == '\0') {
                    _Str1 = &DAT_100589da + iVar2;
                  }
                }
                iVar2 = _strnicmp(_Str1,*ppuVar7 + 0x3b,7);
                if (iVar2 == 0) goto LAB_10033f17;
              }
              iStack_c = iStack_c + 1;
            } while (iStack_c < *(int *)(param_3 + 4));
          }
        }
      }
      local_8 = local_8 + 0x20;
      local_4 = local_4 + 1;
      local_10 = local_10 + 0x1e;
      iVar2 = *(int *)(DAT_100c5ad8 + 0x38) * 0x8c4;
    } while (local_4 < *(int *)(&DAT_100581dc + iVar2) + 3);
  }
  return;
}


