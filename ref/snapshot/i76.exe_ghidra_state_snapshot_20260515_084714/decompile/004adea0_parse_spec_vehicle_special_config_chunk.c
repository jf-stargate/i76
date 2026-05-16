/*
 * Program: i76.exe
 * Function: parse_spec_vehicle_special_config_chunk
 * Entry: 004adea0
 * Signature: undefined4 __cdecl parse_spec_vehicle_special_config_chunk(int param_1, int param_2)
 */


/* [cgpt i76.exe vehicle asset chunk callback renames v17; confidence=medium-high] SPEC callback in
   VCFC table; parses special/config subrecords for vehicle config resources. */

undefined4 __cdecl parse_spec_vehicle_special_config_chunk(int param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = 0;
  piVar2 = (int *)(*(int *)(param_2 + 4) + 0xa70);
  do {
    if (*piVar2 == 0) {
      *(undefined4 *)(*(int *)(param_2 + 4) + 0xa70 + iVar1 * 4) = *(undefined4 *)(param_1 + 8);
      return 1;
    }
    iVar1 = iVar1 + 1;
    piVar2 = piVar2 + 1;
  } while (iVar1 < 3);
  return 0;
}


