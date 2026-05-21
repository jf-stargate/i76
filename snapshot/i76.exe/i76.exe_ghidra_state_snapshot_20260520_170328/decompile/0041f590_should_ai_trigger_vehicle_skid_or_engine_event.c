/*
 * Program: i76.exe
 * Function: should_ai_trigger_vehicle_skid_or_engine_event
 * Entry: 0041f590
 * Signature: bool __cdecl should_ai_trigger_vehicle_skid_or_engine_event(int param_1, int param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v6 ai vehicle behavior cluster: Randomized predicate based on vehicle speed, tire
   contact/friction, and target object suitability. */

bool __cdecl should_ai_trigger_vehicle_skid_or_engine_event(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  bool bVar8;
  float local_18;
  
  if (*(int *)(param_1 + 0x6c) == 9) {
    bVar8 = false;
  }
  else {
    iVar5 = is_vehicle_or_actor_runtime_world_object(param_2);
    if (iVar5 == 0) {
      bVar8 = false;
    }
    else {
      get_ai_vehicle_behavior_state_block(param_1);
      iVar5 = rand();
      iVar6 = ftol();
      if (iVar5 % (iVar6 + 8) == 0) {
        iVar5 = get_vehicle_runtime_context(param_1);
        if (_DAT_004bcb9c <= *(float *)(iVar5 + 0xac)) {
          iVar6 = get_vehicle_front_left_tire_runtime_component(iVar5);
          iVar7 = get_vehicle_front_right_tire_runtime_component(iVar5);
          fVar1 = *(float *)(iVar6 + 0xc);
          fVar2 = *(float *)(iVar7 + 0xc);
          iVar6 = get_vehicle_rear_left_tire_runtime_component(iVar5);
          fVar3 = *(float *)(iVar6 + 0xc);
          iVar6 = get_vehicle_rear_right_tire_runtime_component(iVar5);
          fVar4 = *(float *)(iVar6 + 0xc);
          get_vehicle_effective_terrain_friction_scalar(iVar5);
          fVar2 = _DAT_004bcba4 * (fVar1 + fVar2 + fVar3 + fVar4);
          fVar1 = *(float *)(iVar5 + 0xac);
          if (*(float *)(iVar5 + 0x110) * fVar1 * fVar1 <= fVar2) {
            local_18 = *(float *)(iVar5 + 0xe0) * *(float *)(iVar5 + 0x110) * fVar1;
          }
          else {
            local_18 = (*(float *)(iVar5 + 0xe0) * fVar2) / fVar1;
          }
          bVar8 = _DAT_004bcba8 < ABS(local_18 * fVar1);
        }
        else {
          bVar8 = false;
        }
      }
      else {
        bVar8 = false;
      }
    }
  }
  return bVar8;
}


