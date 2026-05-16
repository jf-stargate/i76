/*
 * Program: i76.exe
 * Function: elapsed_time_or_timer_update
 * Entry: 0049c7f0
 * Signature: undefined __stdcall elapsed_time_or_timer_update(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* i76 first-pass rename
   old_name: FUN_0049c7f0
   suggested_name: elapsed_time_or_timer_update
   basis: Timing/update helper using GetTickCount. */

void elapsed_time_or_timer_update(void)

{
  DWORD DVar1;
  float *pfVar2;
  float *pfVar3;
  int iVar4;
  
  _DAT_004fe420 = _DAT_004be99c;
  _DAT_004fe424 = _DAT_004be9a0;
  g_runtime_time_seconds = _DAT_004be998;
  _DAT_005a7e14 = 0;
  DAT_005a7e18 = 0;
  DAT_004fe428 = _DAT_004be99c;
  DAT_005a7e1c = 0;
  DAT_004fe42c = _DAT_004be9a0;
  _DAT_005a7e74 = _DAT_004be998;
  DVar1 = GetTickCount();
  iVar4 = 0;
  _DAT_005a7e10 = (float)DVar1 * _DAT_004be994;
  pfVar2 = (float *)&DAT_005a7e20;
  do {
    iVar4 = iVar4 + 1;
    pfVar3 = pfVar2 + 1;
    *pfVar2 = _DAT_004be9a4 / (float)iVar4;
    pfVar2 = pfVar3;
  } while ((int)pfVar3 < 0x5a7e70);
  return;
}


