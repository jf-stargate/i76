/*
 * Program: i76.exe
 * Function: system_cutscene_memory_context_helper_00499b00
 * Entry: 00499b00
 * Signature: undefined __cdecl system_cutscene_memory_context_helper_00499b00(undefined4 * param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v20: was
   system_virtual_memory_cutscene_virtual_memory_or_cutscene_helper_00499b00. Shorten readability
   label for system/cutscene/virtual-memory context. */

void __cdecl system_cutscene_memory_context_helper_00499b00(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  _MEMORYSTATUS *p_Var3;
  _MEMORYSTATUS local_20;
  
  p_Var3 = &local_20;
  for (iVar1 = 8; iVar1 != 0; iVar1 = iVar1 + -1) {
    p_Var3->dwLength = 0;
    p_Var3 = (_MEMORYSTATUS *)&p_Var3->dwMemoryLoad;
  }
  local_20.dwLength = 0x20;
  GlobalMemoryStatus(&local_20);
  DAT_005a7ca4 = system_cutscene_memory_context_helper_00499950();
  if (DAT_005a7ca4 == 0xfffffd66) {
    DAT_005a7ca4 = 0;
  }
  else if (DAT_005a7ca4 == 0xffffffff) {
    DAT_005a7ca4 = 200;
  }
  DAT_005a7ca8 = local_20.dwTotalPhys;
  _DAT_005a7cbc = local_20.dwAvailPageFile;
  puVar2 = &DAT_005a7ca0;
  for (iVar1 = 8; iVar1 != 0; iVar1 = iVar1 + -1) {
    *param_1 = *puVar2;
    puVar2 = puVar2 + 1;
    param_1 = param_1 + 1;
  }
  return;
}


