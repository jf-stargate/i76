/*
 * Program: i76.exe
 * Function: trigger_vehicle_forced_damage_or_actor_cleanup
 * Entry: 004652b0
 * Signature: undefined __cdecl trigger_vehicle_forced_damage_or_actor_cleanup(int param_1)
 */


/* [cgpt i76.exe vehicle physics integrator rename v31; confidence=medium] Late physics helper that
   marks vehicle damage state or dispatches actor cleanup when runtime damage flags indicate a
   forced destruction/cleanup path. */

void __cdecl trigger_vehicle_forced_damage_or_actor_cleanup(int param_1)

{
  uint uVar1;
  int iVar2;
  
  if (param_1 != 0) {
    iVar2 = is_vehicle_or_actor_runtime_world_object(param_1);
    if (iVar2 != 0) {
      uVar1 = *(uint *)(*(int *)(param_1 + 0x70) + 0x454);
      if ((uVar1 & 0x8020) == 0) {
        if (*(int *)(param_1 + 0x6c) == 1) {
          *(uint *)(*(int *)(param_1 + 0x70) + 0x454) = uVar1 | 0x20;
          apply_player_vehicle_damage_context_and_death(param_1,(int *)0x0,(float *)0x0);
        }
        else if (*(int *)(param_1 + 0x6c) == 9) {
          create_building_child_object(param_1);
          return;
        }
      }
    }
  }
  return;
}


