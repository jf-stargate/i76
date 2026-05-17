/*
 * Program: i76.exe
 * Function: validate_hloc_vehicle_hardpoint_chunk_for_shell
 * Entry: 004b3cd0
 * Signature: undefined4 __cdecl validate_hloc_vehicle_hardpoint_chunk_for_shell(int param_1, int * param_2)
 */


/* [cgpt i76.exe vehicle asset chunk callback renames v17; confidence=medium-high] HLOC callback in
   the shell/default VDF descriptor table; validates hardpoint data during BWD2 descriptor parsing.
    */

undefined4 __cdecl validate_hloc_vehicle_hardpoint_chunk_for_shell(int param_1,int *param_2)

{
  if (6 < *param_2) {
    return 0;
  }
  (&DAT_005db190)[*param_2 * 0x3f] = *(undefined4 *)(param_1 + 0x18);
  *(undefined4 *)(&DAT_005db194 + *param_2 * 0xfc) = *(undefined4 *)(param_1 + 0x1c);
  *(undefined4 *)(&DAT_005db1d4 + *param_2 * 0xfc) = *(undefined4 *)(param_1 + 0x20);
  *param_2 = *param_2 + 1;
  return 1;
}


