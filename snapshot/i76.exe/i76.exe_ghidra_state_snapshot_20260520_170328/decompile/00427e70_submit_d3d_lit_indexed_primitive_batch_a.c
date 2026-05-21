/*
 * Program: i76.exe
 * Function: submit_d3d_lit_indexed_primitive_batch_a
 * Entry: 00427e70
 * Signature: undefined __cdecl submit_d3d_lit_indexed_primitive_batch_a(undefined4 * param_1, int param_2, int param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v8 display/d3d cluster: Submits a lit indexed-color primitive batch, using game
   palette shade lookup and falling back to the immediate callback path when available. */

void __cdecl submit_d3d_lit_indexed_primitive_batch_a(undefined4 *param_1,int param_2,int param_3)

{
  float fVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  short sVar5;
  uint3 uVar6;
  float *pfVar7;
  uint uVar8;
  int iVar9;
  undefined4 *puVar10;
  short *psVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  int iVar15;
  bool bVar16;
  undefined1 local_490 [2];
  uint uStack_48e;
  double local_488;
  undefined1 local_480 [1152];
  
  if (g_cmdline_hardware_raster_requested != 0) {
    if (0 < param_2) {
      iVar15 = param_3 * 3;
      uVar2 = (&DAT_00608680)[iVar15];
      uVar3 = (&DAT_00608681)[iVar15];
      uVar4 = (&DAT_00608682)[iVar15];
      iVar15 = param_2;
      puVar10 = (undefined4 *)&stack0xfffffb60;
      do {
        fVar1 = (float)param_1[5];
        puVar10[8] = *param_1;
        puVar10[9] = param_1[1];
        puVar10[10] = 0x3f800000;
        puVar10[0xb] = 0x3f800000;
        _local_490 = SUB84((double)((float)_DAT_004faf18 - fVar1 * _DAT_004bcd34),0);
        iVar15 = iVar15 + -1;
        puVar10[0xc] = (&DAT_00526790)[_local_490 + DAT_005280b0] & 0xff;
        *(undefined1 *)(puVar10 + 0xd) = uVar2;
        *(undefined1 *)((int)puVar10 + 0x35) = uVar3;
        *(undefined1 *)((int)puVar10 + 0x36) = uVar4;
        *(undefined1 *)((int)puVar10 + 0x37) = 0xff;
        puVar10[0xe] = 0xff000000;
        puVar10[0xf] = 0;
        puVar10[0x10] = 0;
        param_1 = param_1 + 6;
        puVar10 = puVar10 + 9;
      } while (iVar15 != 0);
    }
    (*DAT_00608bb0)(0xf,0,local_480,param_2,&local_488);
    return;
  }
  fVar1 = (float)param_1[5];
  if (1 < param_2) {
    pfVar7 = (float *)(param_1 + 0xb);
    iVar15 = param_2 + -1;
    do {
      fVar1 = fVar1 + *pfVar7;
      pfVar7 = pfVar7 + 6;
      iVar15 = iVar15 + -1;
    } while (iVar15 != 0);
  }
  uVar6 = *(uint3 *)(&DAT_00608680 + param_3 * 3);
  _local_490 = (uint)uVar6;
  uVar13 = _local_490 & 0xff;
  local_488 = (double)((float)_DAT_004faf18 - (fVar1 / (float)param_2) * _DAT_004bcd34);
  stack0xfffffb71 = (uint)(ushort)(uVar6 >> 8);
  uVar12 = stack0xfffffb71 & 0xff;
  uVar8 = (&DAT_00526790)[local_488._0_4_ + DAT_005280b0] & 0xff;
  uStack_48e = (uint)(byte)(uVar6 >> 0x10);
  iVar15 = DAT_00526770 * 0x20;
  if (DAT_005268a0 < *(int *)(&DAT_00524780 + iVar15) + param_2) {
LAB_00428060:
    iVar15 = finalize_d3d_execute_buffer_and_set_execute_data(&DAT_00524768 + DAT_00526770 * 8);
    if (iVar15 != 0) {
      (**(code **)(*DAT_005fde48 + 0x20))
                (DAT_005fde48,(&DAT_00524768)[DAT_00526770 * 8],DAT_005fde4c,1);
    }
    if (0xff < DAT_0052689c) {
      bVar16 = false;
      goto LAB_004281aa;
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
        iVar15 = DAT_0052689c * 8;
        DAT_0052689c = DAT_0052689c + 1;
        iVar9 = (**(code **)(*DAT_00526768 + 0x18))
                          (DAT_00526768,&DAT_00526778,&DAT_00524768 + iVar15,0);
        iVar15 = DAT_00526770;
        if (iVar9 == 0) {
          (&DAT_0052477c)[DAT_00526770 * 8] = 1;
          iVar15 = lock_and_begin_d3d_execute_buffer_batch(&DAT_00524768 + iVar15 * 8);
        }
        else {
          iVar15 = 0;
        }
      }
      else {
        iVar15 = 0;
      }
      if (iVar15 == 0) {
        bVar16 = false;
        goto LAB_004281aa;
      }
    }
    else {
      DAT_00526770 = DAT_0052689c;
      iVar15 = DAT_0052689c * 8;
      DAT_0052689c = DAT_0052689c + 1;
      lock_and_begin_d3d_execute_buffer_batch(&DAT_00524768 + iVar15);
    }
  }
  else {
    uVar14 = DAT_005fe578;
    if (DAT_005fe578 == 0) {
      uVar14 = 0x2000;
    }
    if (uVar14 < (uint)((*(int *)(&DAT_00524778 + iVar15) - *(int *)(&DAT_0052476c + iVar15)) + 0x70
                       + param_2 * 8)) goto LAB_00428060;
  }
  bVar16 = (&DAT_0052477c)[DAT_00526770 * 8] == 2;
LAB_004281aa:
  if (bVar16) {
    append_d3d_render_state_changes_to_execute_buffer(0,10);
    **(undefined1 **)(&DAT_00524778 + DAT_00526770 * 0x20) = 3;
    *(undefined1 *)(*(int *)(&DAT_00524778 + DAT_00526770 * 0x20) + 1) = 8;
    *(short *)(*(int *)(&DAT_00524778 + DAT_00526770 * 0x20) + 2) = (short)param_2 + -2;
    iVar15 = DAT_00526770;
    iVar9 = DAT_00526770 * 0x20;
    *(int *)(&DAT_00524778 + iVar9) = *(int *)(&DAT_00524778 + iVar9) + 4;
    puVar10 = *(undefined4 **)(&DAT_00524770 + iVar9);
    iVar9 = param_2;
    if (0 < param_2) {
      do {
        *puVar10 = *param_1;
        puVar10[1] = param_1[1];
        puVar10[2] = 0x3f800000;
        puVar10[3] = 0x3f800000;
        puVar10[4] = (uVar8 * uVar13 & 0xffffff00 | 0xffff0000 | uVar8 * uVar12 >> 8) << 8 |
                     uVar8 * uStack_48e >> 8;
        puVar10[5] = 0;
        puVar10[6] = 0;
        puVar10[7] = 0;
        puVar10 = puVar10 + 8;
        iVar9 = iVar9 + -1;
        iVar15 = DAT_00526770;
        param_1 = param_1 + 6;
      } while (iVar9 != 0);
    }
    iVar15 = iVar15 * 0x20;
    *(undefined4 **)(&DAT_00524770 + iVar15) = puVar10;
    sVar5 = *(short *)(&DAT_00524780 + iVar15);
    psVar11 = *(short **)(&DAT_00524778 + iVar15);
    iVar15 = 1;
    psVar11[3] = 0;
    *psVar11 = sVar5;
    psVar11[1] = sVar5 + 1;
    psVar11[2] = sVar5 + 2;
    psVar11 = psVar11 + 4;
    if (1 < param_2 + -2) {
      do {
        *psVar11 = sVar5;
        psVar11[1] = (short)iVar15 + sVar5 + 1;
        psVar11[2] = (short)iVar15 + sVar5 + 2;
        psVar11[3] = 0x1f;
        psVar11 = psVar11 + 4;
        iVar15 = iVar15 + 1;
      } while (iVar15 < param_2 + -2);
    }
    iVar15 = DAT_00526770 * 0x20;
    *(short **)(&DAT_00524778 + iVar15) = psVar11;
    *(int *)(&DAT_00524780 + iVar15) = *(int *)(&DAT_00524780 + iVar15) + param_2;
  }
  return;
}


