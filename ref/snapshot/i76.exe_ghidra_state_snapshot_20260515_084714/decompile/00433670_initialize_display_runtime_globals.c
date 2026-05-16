/*
 * Program: i76.exe
 * Function: initialize_display_runtime_globals
 * Entry: 00433670
 * Signature: undefined __stdcall initialize_display_runtime_globals(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v3: Zeros display/runtime mode tables and initializes default DirectDraw/D3D display
   state globals. */

void initialize_display_runtime_globals(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = &DAT_005fde40;
  for (iVar1 = 0x2984; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  puVar2 = &DAT_005fcea0;
  for (iVar1 = 0xf; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  DAT_005fcea8 = 2;
  DAT_005fceb4 = 2;
  DAT_005fceb8 = 3;
  DAT_005fced0 = 3;
  puVar2 = &DAT_005fd520;
  for (iVar1 = 0x100; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  puVar2 = &DAT_005fd100;
  for (iVar1 = 0x100; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  puVar2 = &DAT_005fdb00;
  for (iVar1 = 0x40; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  _DAT_00608438 = 1;
  DAT_005fcea0 = 1;
  DAT_005fceb0 = 1;
  DAT_005fceac = 1;
  DAT_005fcec0 = 1;
  DAT_005fcea4 = 0;
  DAT_005fcebc = 0;
  DAT_005fcec4 = 0;
  DAT_005fcec8 = 0;
  DAT_005fcecc = 0;
  DAT_005fced4 = 0x40c00000;
  DAT_005fced8 = 0x41300000;
  DAT_005fd0e8 = 0;
  DAT_005fd0e0 = 0;
  _DAT_005fdc08 = 0;
  _DAT_005fdc10 = 0;
  _DAT_005fd500 = 0;
  DAT_005fdc0c = 0;
  DAT_005fdc00 = 0;
  _DAT_005fdc04 = 0;
  DAT_005fcee8 = 0;
  _DAT_005fde20 = 0;
  return;
}


