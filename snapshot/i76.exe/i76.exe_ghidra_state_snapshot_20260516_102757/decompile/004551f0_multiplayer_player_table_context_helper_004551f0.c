/*
 * Program: i76.exe
 * Function: multiplayer_player_table_context_helper_004551f0
 * Entry: 004551f0
 * Signature: uint __cdecl multiplayer_player_table_context_helper_004551f0(int param_1)
 */


/* cgpt label refinement v18: was multiplayer_network_multiplayer_player_table_helper_004551f0.
   Remove duplicated multiplayer wording from readability label. */

uint __cdecl multiplayer_player_table_context_helper_004551f0(int param_1)

{
  uint in_EAX;
  int iVar1;
  
  if (param_1 != 0) {
    iVar1 = is_vehicle_or_actor_runtime_world_object(param_1);
    if (iVar1 != 0) {
      return CONCAT22((short)((uint)*(int *)(param_1 + 0x70) >> 0x10),
                      *(undefined2 *)(*(int *)(param_1 + 0x70) + 0x480));
    }
    in_EAX = 0;
    if (*(int *)(param_1 + 0x6c) == 0x33) {
      iVar1 = *(int *)(*(int *)(*(int *)(param_1 + 0x70) + 4) + 0x70);
      return CONCAT22((short)((uint)iVar1 >> 0x10),*(undefined2 *)(iVar1 + 0x480));
    }
  }
  return in_EAX & 0xffff0000;
}


