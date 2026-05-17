/*
 * Program: i76.exe
 * Function: submit_d3d_lit_indexed_primitive_batch_b
 * Entry: 004282e0
 * Signature: undefined __cdecl submit_d3d_lit_indexed_primitive_batch_b(undefined4 * param_1, int param_2, int param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v8 display/d3d cluster: Submits the alternate lit indexed-color primitive batch form,
   sharing execute-buffer growth/state logic with the mode-a submitter. */

void __cdecl submit_d3d_lit_indexed_primitive_batch_b(undefined4 *param_1,int param_2,int param_3)

{
  float fVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  byte bVar5;
  short sVar6;
  int iVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  short *psVar10;
  uint uVar11;
  uint uVar12;
  int iVar13;
  uint uVar14;
  bool bVar15;
  undefined1 local_498 [2];
  uint uStack_496;
  int iStack_490;
  int local_488 [2];
  undefined1 local_480 [4];
  undefined4 local_47c [287];
  
  if (DAT_00504be8 != 0) {
    if (0 < param_2) {
      iVar13 = param_3 * 3;
      uVar2 = (&DAT_00608680)[iVar13];
      uVar3 = (&DAT_00608681)[iVar13];
      uVar4 = (&DAT_00608682)[iVar13];
      puVar9 = local_47c;
      iVar13 = param_2;
      do {
        fVar1 = (float)param_1[5];
        puVar9[-1] = *param_1;
        *puVar9 = param_1[1];
        puVar9[1] = 0x3f800000;
        puVar9[2] = 0x3f800000;
        _local_498 = SUB84((double)((float)_DAT_004faf18 - fVar1 * _DAT_004bcd34),0);
        iVar13 = iVar13 + -1;
        puVar9[3] = (&DAT_00526790)[_local_498 + DAT_005280b0] & 0xff;
        *(undefined1 *)(puVar9 + 4) = uVar2;
        *(undefined1 *)((int)puVar9 + 0x11) = uVar3;
        *(undefined1 *)((int)puVar9 + 0x12) = uVar4;
        *(undefined1 *)((int)puVar9 + 0x13) = 0xff;
        puVar9[5] = 0xff000000;
        puVar9[6] = 0;
        puVar9[7] = 0;
        puVar9 = puVar9 + 9;
        param_1 = param_1 + 6;
      } while (iVar13 != 0);
    }
    (*DAT_00608bb0)(0xf,0,local_480,param_2,local_488);
    return;
  }
  iVar13 = DAT_00526770 * 0x20;
  if (DAT_005268a0 < *(int *)(&DAT_00524780 + iVar13) + param_2) {
LAB_00428421:
    iVar13 = finalize_d3d_execute_buffer_and_set_execute_data(&DAT_00524768 + DAT_00526770 * 8);
    if (iVar13 != 0) {
      (**(code **)(*DAT_005fde48 + 0x20))
                (DAT_005fde48,(&DAT_00524768)[DAT_00526770 * 8],DAT_005fde4c,1);
    }
    if (0xff < DAT_0052689c) {
      bVar15 = false;
      goto LAB_00428568;
    }
    if ((&DAT_0052477c)[DAT_0052689c * 8] == 0) {
      if (DAT_00526770 < 0xff) {
        _DAT_00526780 = 0;
        DAT_00526770 = DAT_0052689c;
        _DAT_00526788 = 0;
        _DAT_00526778 = 0x14;
        _DAT_0052677c = 1;
        _DAT_00526784 = 0x2000;
        if (DAT_005fe578 != 0) {
          _DAT_00526784 = DAT_005fe578;
        }
        iVar13 = DAT_0052689c * 8;
        DAT_0052689c = DAT_0052689c + 1;
        iVar7 = (**(code **)(*DAT_00526768 + 0x18))
                          (DAT_00526768,&DAT_00526778,&DAT_00524768 + iVar13,0);
        iVar13 = DAT_00526770;
        if (iVar7 == 0) {
          (&DAT_0052477c)[DAT_00526770 * 8] = 1;
          iVar13 = lock_and_begin_d3d_execute_buffer_batch(&DAT_00524768 + iVar13 * 8);
        }
        else {
          iVar13 = 0;
        }
      }
      else {
        iVar13 = 0;
      }
      if (iVar13 == 0) {
        bVar15 = false;
        goto LAB_00428568;
      }
    }
    else {
      DAT_00526770 = DAT_0052689c;
      iVar13 = DAT_0052689c * 8;
      DAT_0052689c = DAT_0052689c + 1;
      lock_and_begin_d3d_execute_buffer_batch(&DAT_00524768 + iVar13);
    }
  }
  else {
    uVar11 = DAT_005fe578;
    if (DAT_005fe578 == 0) {
      uVar11 = 0x2000;
    }
    if (uVar11 < (uint)((*(int *)(&DAT_00524778 + iVar13) - *(int *)(&DAT_0052476c + iVar13)) + 0x70
                       + param_2 * 8)) goto LAB_00428421;
  }
  bVar15 = (&DAT_0052477c)[DAT_00526770 * 8] == 2;
LAB_00428568:
  if (bVar15) {
    append_d3d_render_state_changes_to_execute_buffer(0,0xb);
    **(undefined1 **)(&DAT_00524778 + DAT_00526770 * 0x20) = 3;
    *(undefined1 *)(*(int *)(&DAT_00524778 + DAT_00526770 * 0x20) + 1) = 8;
    *(short *)(*(int *)(&DAT_00524778 + DAT_00526770 * 0x20) + 2) = (short)param_2 + -2;
    iVar13 = DAT_00526770;
    iVar7 = DAT_00526770 * 0x20;
    *(int *)(&DAT_00524778 + iVar7) = *(int *)(&DAT_00524778 + iVar7) + 4;
    puVar9 = *(undefined4 **)(&DAT_00524770 + iVar7);
    if (0 < param_2) {
      iStack_490 = param_2;
      puVar8 = puVar9;
      do {
        *puVar8 = *param_1;
        puVar8[1] = param_1[1];
        puVar8[2] = 0x3f800000;
        puVar8[3] = 0x3f800000;
        puVar9 = puVar8 + 8;
        bVar5 = (&DAT_00608682)[param_3 * 3];
        stack0xfffffb69 = (uint)(ushort)(*(uint3 *)(&DAT_00608680 + param_3 * 3) >> 8);
        local_488[0] = SUB84((double)((float)_DAT_004faf18 - (float)param_1[5] * _DAT_004bcd34),0);
        uVar14 = stack0xfffffb69 & 0xff;
        _local_498 = (uint)*(uint3 *)(&DAT_00608680 + param_3 * 3);
        uVar12 = _local_498 & 0xff;
        uVar11 = (&DAT_00526790)[local_488[0] + DAT_005280b0];
        puVar8[5] = 0;
        uVar11 = uVar11 & 0xff;
        puVar8[6] = 0;
        puVar8[7] = 0;
        uStack_496 = (uint)bVar5;
        iStack_490 = iStack_490 + -1;
        puVar8[4] = (uVar12 * uVar11 & 0xffffff00 | 0xffff0000) << 8 | uVar14 * uVar11 & 0xffffff00
                    | uStack_496 * uVar11 >> 8;
        puVar8 = puVar9;
        iVar13 = DAT_00526770;
        param_1 = param_1 + 6;
      } while (iStack_490 != 0);
    }
    iVar13 = iVar13 * 0x20;
    *(undefined4 **)(&DAT_00524770 + iVar13) = puVar9;
    sVar6 = *(short *)(&DAT_00524780 + iVar13);
    psVar10 = *(short **)(&DAT_00524778 + iVar13);
    iVar13 = 1;
    psVar10[3] = 0;
    *psVar10 = sVar6;
    psVar10[1] = sVar6 + 1;
    psVar10[2] = sVar6 + 2;
    psVar10 = psVar10 + 4;
    if (1 < param_2 + -2) {
      do {
        *psVar10 = sVar6;
        psVar10[1] = (short)iVar13 + sVar6 + 1;
        psVar10[2] = (short)iVar13 + sVar6 + 2;
        psVar10[3] = 0x1f;
        psVar10 = psVar10 + 4;
        iVar13 = iVar13 + 1;
      } while (iVar13 < param_2 + -2);
    }
    iVar13 = DAT_00526770 * 0x20;
    *(short **)(&DAT_00524778 + iVar13) = psVar10;
    *(int *)(&DAT_00524780 + iVar13) = *(int *)(&DAT_00524780 + iVar13) + param_2;
  }
  return;
}


