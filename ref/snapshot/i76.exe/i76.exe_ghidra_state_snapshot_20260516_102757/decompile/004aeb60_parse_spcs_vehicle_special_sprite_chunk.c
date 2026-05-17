/*
 * Program: i76.exe
 * Function: parse_spcs_vehicle_special_sprite_chunk
 * Entry: 004aeb60
 * Signature: undefined4 __cdecl parse_spcs_vehicle_special_sprite_chunk(int param_1, int param_2)
 */


/* [cgpt i76.exe vehicle asset chunk callback renames v17; confidence=medium] SPCS callback in
   runtime vehicle descriptor table; likely parses special/sprite metadata. */

undefined4 __cdecl parse_spcs_vehicle_special_sprite_chunk(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_2 + 4);
  *(undefined4 *)(iVar1 + 0xa64) = *(undefined4 *)(param_1 + 8);
  *(undefined4 *)(iVar1 + 0xa68) = *(undefined4 *)(param_1 + 0xc);
  *(undefined4 *)(iVar1 + 0xa6c) = *(undefined4 *)(param_1 + 0x10);
  return 1;
}


