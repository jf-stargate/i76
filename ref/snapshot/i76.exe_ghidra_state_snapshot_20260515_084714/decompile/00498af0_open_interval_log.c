/*
 * Program: i76.exe
 * Function: open_interval_log
 * Entry: 00498af0
 * Signature: undefined __stdcall open_interval_log(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* i76 second-pass rename
   old_name: FUN_00498af0
   suggested_name: open_interval_log
   basis: Opens interval.txt. */

void open_interval_log(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  DAT_005a7c90 = fopen(s_interval_txt_004fdde0,s_w_004c2298);
  DAT_005a7c5c = 0;
  DAT_005a6c38 = 0;
  DAT_005a6ad8 = 0;
  DAT_005a7c60 = 0;
  DAT_005a6ae0 = 0;
  DAT_005a6ae4 = 0;
  DAT_005a6ae8 = 0;
  _DAT_005a6aec = 0;
  DAT_005a7c8c = 1;
  puVar2 = &DAT_005a6af8;
  for (iVar1 = 0x50; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  DAT_005a6af0 = 0;
  return;
}


