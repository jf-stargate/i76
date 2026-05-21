/*
 * Program: i76shell.dll
 * Function: toggle_vehicle_part_dialog_selection
 * Entry: 1000ab10
 * Signature: undefined __cdecl toggle_vehicle_part_dialog_selection(int param_1, undefined4 param_2, int param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl toggle_vehicle_part_dialog_selection(int param_1,undefined4 param_2,int param_3)

{
  int *piVar1;
  int iVar2;
  double dVar3;
  double dVar4;
  int iVar5;
  int iVar6;
  LPVOID pvVar7;
  int iVar8;
  int *piVar9;
  int iVar10;
  
  iVar5 = ((param_3 - *(int *)(param_1 + 0xc)) - *(int *)(DAT_100533b8 + 4)) / DAT_10051cd0;
  if (iVar5 < *(int *)(*(int *)(param_1 + 0x14) + 4)) {
    piVar1 = *(int **)(*(int *)(*(int *)(param_1 + 0x14) + 8) + iVar5 * 4);
    iVar5 = *(int *)(*piVar1 + 0x4c);
    if (piVar1[3] != iVar5) {
      iVar8 = 0;
      iVar10 = DAT_100533b0;
      if (0 < *(int *)(DAT_100533c4 + 4)) {
        piVar9 = *(int **)(DAT_100533c4 + 8);
        do {
          iVar2 = *(int *)*piVar9;
          dVar4 = (double)((int *)*piVar9)[3];
          dVar3 = (double)*(int *)(iVar2 + 0x4c) * _DAT_100412c8;
          if (dVar3 <= dVar4) {
            iVar6 = 2;
            if (dVar3 + dVar3 <= dVar4) {
              iVar6 = 1;
            }
          }
          else {
            iVar6 = 3;
          }
          iVar10 = iVar10 + *(int *)(&DAT_10043558 + *(int *)(iVar2 + 0x1e) * 4) * iVar6;
          if ((DAT_10052098 <= iVar10) && (piVar1[4] != 3)) goto LAB_1000acf3;
          iVar8 = iVar8 + 1;
          piVar9 = piVar9 + 1;
        } while (iVar8 < *(int *)(DAT_100533c4 + 4));
      }
      if (piVar1[4] == 3) {
        pvVar7 = (LPVOID)piVar1[6];
        if (pvVar7 == (LPVOID)0x0) {
          pvVar7 = HeapAlloc(DAT_10051c50,1,0x20);
          piVar1[6] = (int)pvVar7;
          *(int *)((int)pvVar7 + 0x10) = piVar1[4];
          piVar1[4] = 2;
        }
        else {
          piVar1[4] = *(int *)((int)pvVar7 + 0x10);
          HeapFree(DAT_10051c50,1,pvVar7);
          piVar1[6] = 0;
        }
        iVar5 = remove_pointer_list_item(DAT_100533c4,(int)piVar1);
        if (iVar5 == 0) {
          dVar3 = (double)*(int *)(*piVar1 + 0x4c) * _DAT_100412c8;
          if (dVar3 <= (double)piVar1[3]) {
            iVar5 = 2;
            if (dVar3 + dVar3 <= (double)piVar1[3]) {
              iVar5 = 1;
            }
          }
          else {
            iVar5 = 3;
          }
          DAT_100533b0 = DAT_100533b0 -
                         *(int *)(&DAT_10043558 + *(int *)(*piVar1 + 0x1e) * 4) * iVar5;
        }
      }
      else {
        dVar4 = (double)piVar1[3];
        dVar3 = (double)iVar5 * _DAT_100412c8;
        if (dVar3 <= dVar4) {
          iVar5 = 2;
          if (dVar3 + dVar3 <= dVar4) {
            iVar5 = 1;
          }
        }
        else {
          iVar5 = 3;
        }
        if (DAT_10052098 < *(int *)(&DAT_10043558 + *(int *)(*piVar1 + 0x1e) * 4) * iVar5 + iVar10)
        {
LAB_1000acf3:
          show_vehicle_weight_limit_warning();
          return;
        }
        if (piVar1[6] == 0) {
          pvVar7 = HeapAlloc(DAT_10051c50,1,0x20);
          piVar1[6] = (int)pvVar7;
        }
        *(int *)(piVar1[6] + 0x10) = piVar1[4];
        piVar1[4] = 3;
        insert_pointer_list_item_sorted_or_append(DAT_100533c4,(int)piVar1,(undefined *)0x0);
      }
      redraw_vehicle_part_dialog_list_entries(param_1);
    }
  }
  return;
}


