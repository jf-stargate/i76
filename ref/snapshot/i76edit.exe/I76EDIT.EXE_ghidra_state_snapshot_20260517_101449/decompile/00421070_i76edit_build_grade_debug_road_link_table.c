/*
 * Program: I76EDIT.EXE
 * Function: i76edit_build_grade_debug_road_link_table
 * Entry: 00421070
 * Signature: undefined4 __cdecl i76edit_build_grade_debug_road_link_table(int param_1)
 */


/* [cgpt_i76edit_level_renames_v5:low] Grade/debug-side analogue to linked-object road link builder
   using globals 0043c110/0043c114/0043c12c/0043c130. */

undefined4 __cdecl i76edit_build_grade_debug_road_link_table(int param_1)

{
  ushort uVar1;
  ushort uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int *piVar6;
  undefined4 *puVar7;
  bool bVar8;
  int local_34;
  uint local_30;
  uint local_2c;
  float local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  local_24 = DAT_004379c8;
  local_20 = DAT_004379cc;
  local_1c = DAT_004379d0;
  local_18 = DAT_004379d8;
  local_14 = DAT_004379dc;
  local_10 = DAT_004379e0;
  local_c = DAT_004379e8;
  local_8 = DAT_004379ec;
  DAT_0043c130 = 0;
  local_4 = DAT_004379f0;
  DAT_0043c114 = (undefined4 *)0x0;
  FUN_00421530(param_1);
  switch(*(undefined2 *)(*(int *)(param_1 + 8) + 4)) {
  case 0:
  case 3:
    DAT_004379fc = 2;
    break;
  case 1:
    DAT_004379fc = 3;
    break;
  case 2:
    DAT_004379fc = 4;
  }
  local_2c = 0;
  do {
    DAT_004379c8 = local_24;
    DAT_004379cc = local_20;
    DAT_004379d0 = local_1c;
    DAT_004379d8 = local_18;
    DAT_004379dc = local_14;
    DAT_004379e0 = local_10;
    DAT_004379e8 = local_c;
    DAT_004379ec = local_8;
    DAT_0043c12c = local_2c;
    local_28 = 0.0;
    DAT_004379f0 = local_4;
    DAT_004379f4 = 0;
    bVar8 = *(int *)(*(int *)(param_1 + 8) + 0x44) == 0;
    if (local_2c == 1) {
      FUN_00421530(param_1);
      DAT_0043c114 = _malloc((DAT_0043c130 * 3 + 3) * 4);
      puVar7 = DAT_0043c114;
      for (uVar5 = DAT_0043c130 * 3 + 3 & 0x3fffffff; uVar5 != 0; uVar5 = uVar5 - 1) {
        *puVar7 = 0;
        puVar7 = puVar7 + 1;
      }
      for (iVar4 = 0; iVar4 != 0; iVar4 = iVar4 + -1) {
        *(undefined1 *)puVar7 = 0;
        puVar7 = (undefined4 *)((int)puVar7 + 1);
      }
      DAT_0043c130 = 0;
    }
    else if ((1 < (int)local_2c) && ((int)local_2c < 6)) {
      FUN_00421530(param_1);
      if ((DAT_0043c12c == 2) && (local_30 = 0, DAT_0043c130 != 0)) {
        local_34 = 0;
        do {
          if ((local_34 != 0) && (piVar6 = (int *)((int)DAT_0043c114 + local_34), *piVar6 == 0)) {
            uVar1 = *(ushort *)(piVar6 + 2);
            uVar2 = *(ushort *)(piVar6 + -1);
            uVar5 = (int)((uint)uVar1 - (uint)uVar2) >> 0x1f;
            if ((((uint)uVar1 - (uint)uVar2 ^ uVar5) - uVar5 == 1) && (local_30 + 1 < DAT_0043c130))
            {
              if (uVar2 < uVar1) {
                if (*(ushort *)(piVar6 + 5) <= uVar1) {
LAB_004212af:
                  *(ushort *)(piVar6 + 2) = uVar2;
                }
              }
              else if (uVar1 <= *(ushort *)(piVar6 + 5)) goto LAB_004212af;
            }
          }
          local_34 = local_34 + 0xc;
          local_30 = local_30 + 1;
        } while (local_30 < DAT_0043c130);
      }
      DAT_0043c130 = 0;
    }
    iVar4 = param_1;
    if (param_1 != 0) {
      while( true ) {
        uVar5 = (uint)bVar8;
        piVar6 = *(int **)(iVar4 + 8);
        if ((piVar6[0x14] & 1U) != 0) break;
        piVar6[0x14] = piVar6[0x14] | 1;
        bVar8 = (piVar6[2] & 0x7fffffffU) != 0;
        if (bVar8) {
          DAT_00437a04 = DAT_00437a04 + 1;
        }
        DAT_00437a00 = (uint)bVar8;
        if (*piVar6 == 0) {
          FUN_004215c0((int)piVar6,uVar5,1.0,&local_28);
        }
        else if (*piVar6 == 1) {
          FUN_00421830((int)piVar6,uVar5,1.0,&local_28);
        }
        iVar3 = piVar6[0x11 - uVar5];
        if (iVar3 == 0) goto LAB_004213b3;
        bVar8 = *(int *)(*(int *)(iVar3 + 8) + 0x40) != iVar4;
        iVar4 = iVar3;
      }
      if (DAT_0043c12c == 2) {
        *(undefined2 *)(DAT_0043c114 + DAT_0043c130 * 3 + -1) = *(undefined2 *)(DAT_0043c114 + 2);
        DAT_0043c114[DAT_0043c130 * 3 + -3] = 1;
      }
    }
LAB_004213b3:
    local_2c = local_2c + 1;
    if (5 < local_2c) {
      iVar4 = 0;
      uVar5 = 0;
      if (DAT_0043c130 != 0xffffffff) {
        do {
          iVar3 = iVar4 + 8;
          iVar4 = iVar4 + 0xc;
          uVar5 = uVar5 + 1;
          _fprintf(DAT_0043c110,&DAT_00437ae0,(uint)*(ushort *)((int)DAT_0043c114 + iVar3));
        } while (uVar5 < DAT_0043c130 + 1);
      }
      _free(DAT_0043c114);
      DAT_0043c114 = (undefined4 *)0x0;
      return 0;
    }
  } while( true );
}


