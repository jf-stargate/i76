/*
 * Program: i76.exe
 * Function: reset_bridge_validation_runtime_state
 * Entry: 0040c1a0
 * Signature: undefined __cdecl reset_bridge_validation_runtime_state(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v7 fsm predicate/bridge cluster: Resets bridge/path validation free-list state,
   counters, and per-vehicle bridge validation fields. */

void __cdecl reset_bridge_validation_runtime_state(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  
  iVar2 = DAT_0051f650 + 2;
  DAT_0051f65c = &DAT_005dd780;
  if (999 < DAT_005244bc) {
    iVar2 = 999;
  }
  if (0 < iVar2) {
    puVar1 = &DAT_005dd7e0;
    do {
      *puVar1 = puVar1 + 8;
      puVar1 = puVar1 + 0x20;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  }
  DAT_005244bc = 0;
  DAT_0051f650 = 0;
  _DAT_005fcb60 = 0;
  _DAT_0051f664 = 0;
  *(undefined4 *)(param_1 + 0x7c) = 0;
  *(undefined4 *)(param_1 + 0x9cf0) = 0;
  *(undefined4 *)(param_1 + 0x9cf4) = 0;
  return;
}


