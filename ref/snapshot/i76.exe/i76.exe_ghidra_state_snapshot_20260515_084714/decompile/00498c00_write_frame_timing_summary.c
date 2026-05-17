/*
 * Program: i76.exe
 * Function: write_frame_timing_summary
 * Entry: 00498c00
 * Signature: undefined __stdcall write_frame_timing_summary(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* i76 second-pass rename
   old_name: FUN_00498c00
   suggested_name: write_frame_timing_summary
   basis: Writes median FPS and average jerk timing diagnostics. */

void write_frame_timing_summary(void)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  undefined8 local_8;
  
  iVar2 = DAT_005a7c90;
  if (DAT_005a7c90 != 0) {
    if (DAT_005a7c5c != 0) {
      qsort(&DAT_005a6cb8,DAT_005a7c5c,4,(_PtFuncCompare *)&LAB_00498d50);
      local_8 = 0.0;
      if (0 < *(int *)(&DAT_005a6cb8 + (DAT_005a7c5c >> 1) * 4)) {
        local_8 = _DAT_004be948 / (double)*(int *)(&DAT_005a6cb8 + (DAT_005a7c5c >> 1) * 4);
      }
      fprintf((FILE *)iVar2,s_Median_of_last__d_frames_is__3_2_004fde18,DAT_005a7c5c,
              (undefined4)local_8,local_8._4_4_);
      DAT_005a6c38 = DAT_005a6c38 + DAT_005a7c5c;
      DAT_005a7c5c = 0;
    }
    iVar2 = 0;
    piVar3 = &DAT_005a6ae0;
    do {
      iVar1 = *piVar3;
      piVar3 = piVar3 + 1;
      iVar2 = iVar2 + iVar1;
    } while ((int)piVar3 < 0x5a6af0);
    if (DAT_005a7c8c == 0) {
      fprintf((FILE *)DAT_005a7c90,s_Average_of_biggest_jerks_is__d_m_004fddf0,
              (DAT_005a6af0 + iVar2) / 5);
    }
    else {
      fprintf((FILE *)DAT_005a7c90,s_Average_of_biggest_jerks_is__d_m_004fddf0,
              (int)(iVar2 + (iVar2 >> 0x1f & 3U)) >> 2);
      DAT_005a7c8c = 0;
    }
    DAT_005a6ae0 = 0;
    DAT_005a6ae4 = 0;
    DAT_005a6ae8 = 0;
    _DAT_005a6aec = 0;
    DAT_005a6af0 = 0;
    fclose((FILE *)DAT_005a7c90);
    DAT_005a7c90 = 0;
  }
  return;
}


