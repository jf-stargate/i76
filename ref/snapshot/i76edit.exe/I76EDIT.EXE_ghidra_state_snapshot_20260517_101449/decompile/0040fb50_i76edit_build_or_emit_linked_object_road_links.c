/*
 * Program: I76EDIT.EXE
 * Function: i76edit_build_or_emit_linked_object_road_links
 * Entry: 0040fb50
 * Signature: undefined4 __cdecl i76edit_build_or_emit_linked_object_road_links(undefined4 * param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt_i76edit_level_renames_v5:low] Walks linked-object/road adjacency state and calls
   geometry/link helpers 004100f0/004103c0. Provisional. */

undefined4 __cdecl i76edit_build_or_emit_linked_object_road_links(undefined4 *param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  ushort uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  undefined4 *puVar7;
  uint uVar8;
  bool bVar9;
  float10 fVar10;
  float10 extraout_ST0;
  longlong lVar11;
  ushort local_44;
  ushort uStack_42;
  ushort local_40;
  int local_38;
  float local_34;
  float local_30;
  float local_2c;
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
  
  local_24 = DAT_00434970;
  local_20 = DAT_00434974;
  local_1c = DAT_00434978;
  local_18 = DAT_00434980;
  local_14 = DAT_00434984;
  local_10 = DAT_00434988;
  local_c = DAT_00434990;
  local_8 = DAT_00434994;
  DAT_00439eb8 = 0;
  local_4 = DAT_00434998;
  DAT_00439ea8 = (undefined4 *)0x0;
  for (puVar7 = param_1; puVar7 != (undefined4 *)0x0; puVar7 = (undefined4 *)*puVar7) {
    *(uint *)(puVar7[2] + 0x50) = *(uint *)(puVar7[2] + 0x50) & 0xfffffffe;
  }
  local_38 = 0;
  do {
    DAT_00434970 = local_24;
    DAT_00434974 = local_20;
    DAT_00434978 = local_1c;
    DAT_00434980 = local_18;
    DAT_00434984 = local_14;
    DAT_00434988 = local_10;
    DAT_00434990 = local_c;
    DAT_00434994 = local_8;
    DAT_00439eb4 = local_38;
    local_34 = 0.0;
    DAT_00434998 = local_4;
    DAT_0043499c = 0;
    bVar9 = *(int *)(param_1[2] + 0x44) == 0;
    puVar7 = param_1;
    if (local_38 == 1) {
      for (; puVar7 != (undefined4 *)0x0; puVar7 = (undefined4 *)*puVar7) {
        *(uint *)(puVar7[2] + 0x50) = *(uint *)(puVar7[2] + 0x50) & 0xfffffffe;
      }
      DAT_00439ea8 = _malloc((DAT_00439eb8 * 3 + 3) * 4);
      puVar7 = DAT_00439ea8;
      for (uVar5 = DAT_00439eb8 * 3 + 3 & 0x3fffffff; uVar5 != 0; uVar5 = uVar5 - 1) {
        *puVar7 = 0;
        puVar7 = puVar7 + 1;
      }
      for (iVar4 = 0; iVar4 != 0; iVar4 = iVar4 + -1) {
        *(undefined1 *)puVar7 = 0;
        puVar7 = (undefined4 *)((int)puVar7 + 1);
      }
      DAT_00439eb8 = 0;
    }
    else {
      uVar5 = DAT_00439eb8;
      if ((local_38 == 2) || (local_38 == 3)) {
        for (; DAT_00439eb8 = uVar5, puVar7 != (undefined4 *)0x0; puVar7 = (undefined4 *)*puVar7) {
          *(uint *)(puVar7[2] + 0x50) = *(uint *)(puVar7[2] + 0x50) & 0xfffffffe;
          uVar5 = DAT_00439eb8;
        }
        if ((DAT_00439eb4 == 2) && (uVar8 = uVar5 - 1, uVar8 != 0)) {
          uStack_42 = *(ushort *)(DAT_00439ea8 + 2);
          local_2c = (float)uStack_42;
          uVar3 = *(ushort *)(DAT_00439ea8 + uVar8 * 3 + 2);
          local_30 = (float)uVar3;
          local_44 = uVar3;
          if (uStack_42 < uVar3) {
            local_44 = uStack_42;
            uStack_42 = uVar3;
          }
          uVar6 = 0;
          if (uVar5 != 0) {
            local_30 = local_30 - local_2c;
            iVar4 = 0;
            local_28 = (float)uVar8;
            do {
              fVar10 = (float10)uVar6 / (float10)local_28;
              lVar11 = __ftol();
              local_40 = (ushort)lVar11;
              local_34 = (float)(extraout_ST0 - (float10)local_40);
              if (((float10)_DAT_004320f4 <= extraout_ST0 - (float10)local_40) ||
                 (0xbeffffff < (uint)local_34)) {
                fVar10 = fVar10 + (float10)_DAT_004320fc;
              }
              if ((float10)_DAT_004320e4 <= fVar10) {
                uVar3 = local_44;
                if (((float10)local_44 <= fVar10) &&
                   (uVar3 = uStack_42, fVar10 <= (float10)uStack_42)) {
                  lVar11 = __ftol();
                  uVar3 = (ushort)lVar11;
                }
                *(ushort *)((int)DAT_00439ea8 + iVar4 + 8) = uVar3;
              }
              else {
                *(undefined2 *)((int)DAT_00439ea8 + iVar4 + 8) = 0;
              }
              iVar4 = iVar4 + 0xc;
              uVar6 = uVar6 + 1;
            } while (uVar6 < uVar5);
          }
        }
        DAT_00439eb8 = 0;
      }
    }
    puVar7 = param_1;
    if (param_1 != (undefined4 *)0x0) {
      while( true ) {
        uVar5 = (uint)bVar9;
        piVar1 = (int *)puVar7[2];
        if ((piVar1[0x14] & 1U) != 0) break;
        piVar1[0x14] = piVar1[0x14] | 1;
        bVar9 = (piVar1[2] & 0x7fffffffU) != 0;
        if (bVar9) {
          DAT_004349ac = DAT_004349ac + 1;
        }
        DAT_004349a8 = (uint)bVar9;
        if (*piVar1 == 0) {
          FUN_004100f0((int)piVar1,uVar5,1.0,&local_34);
        }
        else if (*piVar1 == 1) {
          FUN_004103c0((int)piVar1,uVar5,1.0,&local_34);
        }
        puVar2 = (undefined4 *)piVar1[0x11 - uVar5];
        if (puVar2 == (undefined4 *)0x0) goto LAB_0040ff90;
        bVar9 = *(undefined4 **)(puVar2[2] + 0x40) != puVar7;
        puVar7 = puVar2;
      }
      if (DAT_00439eb4 == 2) {
        *(undefined2 *)(DAT_00439ea8 + DAT_00439eb8 * 3 + -1) = *(undefined2 *)(DAT_00439ea8 + 2);
        DAT_00439ea8[DAT_00439eb8 * 3 + -3] = 1;
      }
    }
LAB_0040ff90:
    local_38 = local_38 + 1;
    if (3 < local_38) {
      _free(DAT_00439ea8);
      DAT_00439ea8 = (undefined4 *)0x0;
      return 0;
    }
  } while( true );
}


