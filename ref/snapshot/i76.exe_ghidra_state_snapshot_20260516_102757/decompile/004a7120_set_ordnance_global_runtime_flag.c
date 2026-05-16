/*
 * Program: i76.exe
 * Function: set_ordnance_global_runtime_flag
 * Entry: 004a7120
 * Signature: undefined __cdecl set_ordnance_global_runtime_flag(undefined4 param_1)
 */


/* cgpt rename v2: Stores an ordnance/runtime global flag used by weapon/ordnance systems. */

void __cdecl set_ordnance_global_runtime_flag(undefined4 param_1)

{
  DAT_005da7a4 = param_1;
  return;
}


