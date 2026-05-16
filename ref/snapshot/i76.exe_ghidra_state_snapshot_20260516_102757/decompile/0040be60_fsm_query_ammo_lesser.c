/*
 * Program: i76.exe
 * Function: fsm_query_ammo_lesser
 * Entry: 0040be60
 * Signature: bool __cdecl fsm_query_ammo_lesser(int param_1, int * param_2, uint * param_3)
 */


/* cgpt whole-binary semantic rename v1: string evidence: ammoLesser nonVehicle / hard point */

bool __cdecl fsm_query_ammo_lesser(int param_1,int *param_2,uint *param_3)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  undefined4 local_58 [17];
  uint local_14;
  int local_8;
  
  iVar1 = is_vehicle_or_actor_runtime_world_object(param_1);
  if (iVar1 == 0) {
    report_chunk_parse_error();
    return false;
  }
  iVar1 = get_vehicle_runtime_context(param_1);
  iVar1 = get_vehicle_damage_event_state_block(iVar1);
  iVar2 = 0;
  if (0 < *(int *)(iVar1 + 0xa718)) {
    piVar3 = (int *)(iVar1 + 0xa71c);
    do {
      extract_weapon_runtime_state_to_vsf_record(*piVar3,local_58);
      if (local_8 == *param_2) {
        return local_14 < *param_3;
      }
      iVar2 = iVar2 + 1;
      piVar3 = piVar3 + 1;
    } while (iVar2 < *(int *)(iVar1 + 0xa718));
  }
  report_chunk_parse_error();
  return false;
}


