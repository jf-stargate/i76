/*
 * Program: i76.exe
 * Function: ai_vehicle_has_loaded_fireable_weapon_slot
 * Entry: 0041c3b0
 * Signature: undefined4 __cdecl ai_vehicle_has_loaded_fireable_weapon_slot(int param_1)
 */


/* cgpt readability rename v13 set A: Checks AI vehicle behavior weapon slots and returns true when
   any extracted weapon state reports usable ammo/state. */

undefined4 __cdecl ai_vehicle_has_loaded_fireable_weapon_slot(int param_1)

{
  int local_68;
  undefined4 local_64 [17];
  int local_20;
  int local_c;
  undefined4 local_8;
  
  local_c = get_ai_vehicle_behavior_state_block(param_1);
  local_68 = 0;
  while( true ) {
    if (*(int *)(local_c + 0xa6f4) <= local_68) {
      return 0;
    }
    local_8 = extract_weapon_runtime_state_to_vsf_record
                        (*(int *)(local_c + 0xa71c + *(int *)(local_c + 0xa6f8 + local_68 * 4) * 4),
                         local_64);
    if (local_20 != 0) break;
    local_68 = local_68 + 1;
  }
  return 1;
}


