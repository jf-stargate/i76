/*
 * Program: i76.exe
 * Function: parse_wpst_vehicle_weapon_part_state_chunk
 * Entry: 004b0640
 * Signature: undefined4 __cdecl parse_wpst_vehicle_weapon_part_state_chunk(int param_1, int param_2)
 */


/* [cgpt i76.exe vehicle asset chunk callback renames v17; confidence=medium-high] WPST callback for
   saved/trip weapon part state. */

undefined4 __cdecl parse_wpst_vehicle_weapon_part_state_chunk(int param_1,int param_2)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = *(int *)(param_2 + 4);
  iVar3 = *(int *)(iVar2 + 0xbc);
  *(int *)(iVar2 + 0xbc) = iVar3 + 1;
  puVar1 = (undefined4 *)(iVar2 + 100 + iVar3 * 0xc);
  *puVar1 = *(undefined4 *)(param_1 + 8);
  puVar1[1] = *(undefined4 *)(param_1 + 0xc);
  puVar1[2] = *(undefined4 *)(param_1 + 0x10);
  return 1;
}


