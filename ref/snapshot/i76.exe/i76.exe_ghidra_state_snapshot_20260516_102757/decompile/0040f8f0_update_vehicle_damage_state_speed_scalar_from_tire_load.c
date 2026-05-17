/*
 * Program: i76.exe
 * Function: update_vehicle_damage_state_speed_scalar_from_tire_load
 * Entry: 0040f8f0
 * Signature: undefined __cdecl update_vehicle_damage_state_speed_scalar_from_tire_load(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v11 astar/ai/fsm-loader cluster: Computes and stores a vehicle damage-state
   speed/load scalar from tire compression/load and vehicle mass. */

void __cdecl update_vehicle_damage_state_speed_scalar_from_tire_load(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  iVar4 = get_vehicle_runtime_context(param_1);
  iVar5 = get_vehicle_damage_event_state_block(iVar4);
  iVar6 = get_vehicle_rear_left_tire_runtime_component(iVar4);
  iVar7 = get_vehicle_rear_right_tire_runtime_component(iVar4);
  fVar1 = *(float *)(iVar6 + 0xc);
  fVar2 = *(float *)(iVar7 + 0xc);
  iVar6 = get_vehicle_front_left_tire_runtime_component(iVar4);
  fVar3 = *(float *)(iVar6 + 0xc);
  iVar6 = get_vehicle_front_right_tire_runtime_component(iVar4);
  fVar1 = (fVar1 + fVar2 + fVar3 + *(float *)(iVar6 + 0xc)) * _DAT_004bc738;
  if (fVar1 < _DAT_004bc710) {
    *(undefined4 *)(iVar5 + 0xa994) = 0x3f800000;
    return;
  }
  *(float *)(iVar5 + 0xa994) = SQRT(fVar1 / *(float *)(iVar4 + 0x110));
  return;
}


