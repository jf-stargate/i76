/*
 * Program: i76.exe
 * Function: ai_vehicle_has_usable_weapon_or_nonvehicle_target
 * Entry: 0041c450
 * Signature: undefined4 __cdecl ai_vehicle_has_usable_weapon_or_nonvehicle_target(int param_1, int param_2)
 */


/* cgpt readability rename v13 set A: Predicate over target type and AI weapon slot metadata to
   decide whether weapon/combat behavior can proceed. */

undefined4 __cdecl ai_vehicle_has_usable_weapon_or_nonvehicle_target(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  int local_68;
  undefined4 local_64 [17];
  int local_20;
  int local_c;
  undefined4 local_8;
  
  iVar1 = is_vehicle_or_actor_runtime_world_object(param_2);
  if (iVar1 == 0) {
    uVar2 = 1;
  }
  else {
    local_c = get_ai_vehicle_behavior_state_block(param_1);
    for (local_68 = 0; local_68 < *(int *)(local_c + 0xa6f4); local_68 = local_68 + 1) {
      if (*(int *)(local_c + 0xa73c + local_68 * 0x20) == 4) {
        switch(*(undefined4 *)(local_c + 0xa738 + local_68 * 0x20)) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 0x65:
        case 0x66:
        case 0x67:
          local_8 = extract_weapon_runtime_state_to_vsf_record
                              (*(int *)(local_c + 0xa71c + local_68 * 4),local_64);
          if (local_20 != 0) {
            return 1;
          }
        }
      }
      else if (*(int *)(local_c + 0xa73c + local_68 * 0x20) == 3) {
        return 1;
      }
    }
    uVar2 = 0;
  }
  return uVar2;
}


