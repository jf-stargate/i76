/*
 * Program: i76.exe
 * Function: parse_salv_vehicle_salvage_state_chunk
 * Entry: 004b0680
 * Signature: undefined4 __cdecl parse_salv_vehicle_salvage_state_chunk(int param_1, int param_2)
 */


/* [cgpt i76.exe vehicle asset chunk callback renames v17; confidence=medium-high] SALV callback for
   saved/trip salvage/state data. */

undefined4 __cdecl parse_salv_vehicle_salvage_state_chunk(int param_1,int param_2)

{
  code *pcVar1;
  
  pcVar1 = *(code **)(*(int *)(param_2 + 4) + 0xb8);
  if (pcVar1 != (code *)0x0) {
    (*pcVar1)(param_1 + 8,*(undefined4 *)(param_1 + 0x18),*(undefined4 *)(param_1 + 0x1c));
  }
  return 1;
}


