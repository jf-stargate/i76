/*
 * Program: i76.exe
 * Function: parse_wlst_vehicle_weapon_list_state_chunk
 * Entry: 004b05e0
 * Signature: undefined4 __cdecl parse_wlst_vehicle_weapon_list_state_chunk(int param_1, int param_2)
 */


/* [cgpt i76.exe vehicle asset chunk callback renames v17; confidence=medium-high] WLST callback for
   saved/trip vehicle weapon list state. */

undefined4 __cdecl parse_wlst_vehicle_weapon_list_state_chunk(int param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  puVar2 = (undefined4 *)(param_1 + 8);
  puVar3 = (undefined4 *)(*(int *)(param_2 + 4) + 0x4c);
  for (iVar1 = 6; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  return 1;
}


