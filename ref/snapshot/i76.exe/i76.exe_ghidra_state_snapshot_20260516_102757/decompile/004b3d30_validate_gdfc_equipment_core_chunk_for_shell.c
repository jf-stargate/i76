/*
 * Program: i76.exe
 * Function: validate_gdfc_equipment_core_chunk_for_shell
 * Entry: 004b3d30
 * Signature: undefined4 __cdecl validate_gdfc_equipment_core_chunk_for_shell(int param_1)
 */


/* [cgpt i76.exe vehicle asset chunk callback renames v17; confidence=medium] GDFC callback
   immediately following the shell/default VDF descriptor table; likely equipment/weapon definition
   validation path. */

undefined4 __cdecl validate_gdfc_equipment_core_chunk_for_shell(int param_1)

{
  DAT_005dacd8 = *(undefined4 *)(param_1 + 0x18);
  DAT_005db978 = *(undefined4 *)(param_1 + 0x1c);
  return 1;
}


