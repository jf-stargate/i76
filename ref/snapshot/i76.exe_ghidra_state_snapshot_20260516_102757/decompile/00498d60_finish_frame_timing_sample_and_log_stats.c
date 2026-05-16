/*
 * Program: i76.exe
 * Function: finish_frame_timing_sample_and_log_stats
 * Entry: 00498d60
 * Signature: undefined __stdcall finish_frame_timing_sample_and_log_stats(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe runtime loop refinement v23; confidence=HIGH] End-of-frame timing sampler/logger.
   Maintains ring buffers, median frame timing, jerk statistics, and optional timing log output. */

void finish_frame_timing_sample_and_log_stats(void)

{
  undefined4 uVar1;
  DWORD DVar2;
  int *piVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  undefined4 *puVar7;
  int iVar8;
  int iVar9;
  undefined *puVar10;
  undefined8 local_c;
  
  if (DAT_005a7c90 != 0) {
    DVar2 = timeGetTime();
    iVar6 = DVar2 - DAT_005a7c58;
    uVar4 = DAT_005a6c38 + DAT_005a7c5c;
    *(int *)(&DAT_005a6cb8 + DAT_005a7c5c * 4) = iVar6;
    if (uVar4 == 0) {
      fprintf((FILE *)DAT_005a7c90,&DAT_004c3dd0);
      iVar6 = 0;
      if (0 < DAT_005a6c3c) {
        puVar10 = &DAT_005a6178;
        do {
          fprintf((FILE *)DAT_005a7c90,s__s_004fde60,puVar10);
          iVar6 = iVar6 + 1;
          puVar10 = puVar10 + 0x50;
        } while (iVar6 < DAT_005a6c3c);
      }
      fprintf((FILE *)DAT_005a7c90,s_tot_004fde58);
      iVar6 = 0;
      do {
        fprintf((FILE *)DAT_005a7c90,s_p_d_004fde4c,iVar6);
        iVar6 = iVar6 + 1;
      } while (iVar6 < 4);
      fprintf((FILE *)DAT_005a7c90,&DAT_004f25c0);
      DAT_005a6ad8 = 0;
      DAT_005a7c60 = 0;
    }
    else {
      *(int *)(&DAT_005a7c68 + (uVar4 & 7) * 4) = iVar6;
      if (2 < (int)(uVar4 - 3)) {
        iVar9 = *(int *)(&DAT_005a7c68 + (uVar4 - 3 & 7) * 4);
        for (uVar5 = uVar4 - 5; (int)uVar5 <= (int)(uVar4 - 1); uVar5 = uVar5 + 1) {
          if (*(int *)(&DAT_005a6cb8 + (uVar5 & 7) * 4) < iVar9) {
            iVar9 = *(int *)(&DAT_005a6cb8 + (uVar5 & 7) * 4);
          }
        }
        iVar9 = *(int *)(&DAT_005a7c68 + (uVar4 - 3 & 7) * 4) - iVar9;
        if (DAT_005a6ae0 < iVar9) {
          iVar8 = 1;
          piVar3 = &DAT_005a6ae4;
          do {
            if (iVar9 <= *piVar3) break;
            piVar3[-1] = *piVar3;
            piVar3 = piVar3 + 1;
            iVar8 = iVar8 + 1;
          } while ((int)piVar3 < 0x5a6af4);
          *(int *)(iVar8 * 4 + 0x5a6adc) = iVar9;
        }
      }
      DAT_005a6ad8 = DAT_005a6ad8 + iVar6;
    }
    iVar6 = DAT_005a7c90;
    iVar9 = 0;
    local_c._0_4_ = -1;
    uVar1 = *(undefined4 *)(&DAT_005a6cb8 + DAT_005a7c5c * 4);
    if (0 < DAT_005a6c3c) {
      puVar7 = &DAT_005a6c40;
      do {
        fprintf((FILE *)iVar6,(char *)&PTR_DAT_004fde48,*puVar7);
        iVar9 = iVar9 + 1;
        puVar7 = puVar7 + 1;
      } while (iVar9 < DAT_005a6c3c);
    }
    fprintf((FILE *)iVar6,(char *)&PTR_DAT_004fde48,uVar1);
    iVar9 = 0;
    piVar3 = &DAT_00654a00;
    do {
      if (*piVar3 != 0) {
        local_c._0_4_ = iVar9;
      }
      piVar3 = piVar3 + 1;
      iVar9 = iVar9 + 1;
    } while ((int)piVar3 < 0x654a10);
    if (-1 < (int)local_c) {
      puVar7 = &DAT_00654a00;
      local_c._0_4_ = (int)local_c + 1;
      do {
        fprintf((FILE *)iVar6,(char *)&PTR_DAT_004fde44,*puVar7);
        *puVar7 = 0;
        puVar7 = puVar7 + 1;
        local_c._0_4_ = (int)local_c + -1;
      } while ((int)local_c != 0);
    }
    fprintf((FILE *)iVar6,&DAT_004f25c0);
    iVar6 = DAT_005a7c90;
    DAT_005a7c5c = DAT_005a7c5c + 1;
    if (1999 < DAT_005a6ad8) {
      if (DAT_005a7c5c != 0) {
        qsort(&DAT_005a6cb8,DAT_005a7c5c,4,(_PtFuncCompare *)&LAB_00498d50);
        local_c = 0.0;
        if (0 < *(int *)(&DAT_005a6cb8 + (DAT_005a7c5c >> 1) * 4)) {
          local_c = _DAT_004be948 / (double)*(int *)(&DAT_005a6cb8 + (DAT_005a7c5c >> 1) * 4);
        }
        fprintf((FILE *)iVar6,s_Median_of_last__d_frames_is__3_2_004fde18,DAT_005a7c5c,(int)local_c,
                local_c._4_4_);
        DAT_005a6c38 = DAT_005a6c38 + DAT_005a7c5c;
        DAT_005a7c5c = 0;
      }
      DAT_005a6ad8 = DAT_005a6ad8 + -2000;
      DAT_005a7c60 = DAT_005a7c60 + 2000;
      if (17999 < DAT_005a7c60) {
        iVar6 = 0;
        piVar3 = &DAT_005a6ae0;
        do {
          iVar9 = *piVar3;
          piVar3 = piVar3 + 1;
          iVar6 = iVar6 + iVar9;
        } while ((int)piVar3 < 0x5a6af0);
        if (DAT_005a7c8c == 0) {
          fprintf((FILE *)DAT_005a7c90,s_Average_of_biggest_jerks_is__d_m_004fddf0,
                  (DAT_005a6af0 + iVar6) / 5);
        }
        else {
          fprintf((FILE *)DAT_005a7c90,s_Average_of_biggest_jerks_is__d_m_004fddf0,
                  (int)(iVar6 + (iVar6 >> 0x1f & 3U)) >> 2);
          DAT_005a7c8c = 0;
        }
        DAT_005a6ae0 = 0;
        DAT_005a7c60 = DAT_005a7c60 + -18000;
        DAT_005a6ae4 = 0;
        DAT_005a6ae8 = 0;
        _DAT_005a6aec = 0;
        DAT_005a6af0 = 0;
      }
    }
  }
  return;
}


