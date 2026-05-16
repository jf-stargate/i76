/*
 * Program: i76.exe
 * Function: validate_vdfc_vehicle_core_chunk_for_shell
 * Entry: 004b3cb0
 * Signature: undefined4 __cdecl validate_vdfc_vehicle_core_chunk_for_shell(int param_1)
 */


/* [cgpt i76.exe vehicle asset chunk callback renames v17; confidence=medium-high] VDFC callback in
   the shell/default VDF descriptor table; validates/copies core VDF fields during BWD2 descriptor
   parsing. */

undefined4 __cdecl validate_vdfc_vehicle_core_chunk_for_shell(int param_1)

{
  DAT_005db958 = *(undefined4 *)(param_1 + 0x20);
  DAT_005db7c4 = *(undefined4 *)(param_1 + 0x44);
  return 1;
}


