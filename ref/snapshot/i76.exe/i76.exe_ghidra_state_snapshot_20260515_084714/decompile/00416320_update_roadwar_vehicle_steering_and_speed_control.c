/*
 * Program: i76.exe
 * Function: update_roadwar_vehicle_steering_and_speed_control
 * Entry: 00416320
 * Signature: undefined __cdecl update_roadwar_vehicle_steering_and_speed_control(float param_1, float param_2, float param_3, float param_4, int * param_5, int * param_6, float param_7, int param_8)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v4: Advances roadwar steering target, applies steering control, then adjusts
   throttle/speed command based on path offset. */

void __cdecl
update_roadwar_vehicle_steering_and_speed_control
          (float param_1,float param_2,float param_3,float param_4,int *param_5,int *param_6,
          float param_7,int param_8)

{
  int *piVar1;
  int iVar2;
  float10 fVar3;
  
  piVar1 = param_6;
  if (_DAT_004bc860 <= (float)param_6[5]) {
    if ((float)param_6[5] <= _DAT_004bc868) {
      param_6 = (int *)((float)param_6[5] - _DAT_004bc870);
    }
    else {
      param_6 = (int *)0x41a00000;
    }
  }
  else {
    param_6 = (int *)0xc1200000;
  }
  roadwar_advance_to_next_road_segment
            ((int)param_1,param_2,param_3,param_4,param_5,param_7,(float)param_6,(float *)&param_6);
  update_ai_vehicle_steering_control((int)param_1,(float)param_6);
  iVar2 = get_vehicle_runtime_context((int)param_1);
  if ((float)_DAT_004bc878 < ABS(*(float *)(iVar2 + 0xe0))) {
    fVar3 = get_ai_vehicle_damage_state_speed_scalar((int)param_1);
    set_ai_vehicle_throttle_brake_toward_speed(param_1,(float)fVar3);
    return;
  }
  iVar2 = get_vehicle_runtime_context(param_8);
  set_ai_vehicle_throttle_brake_toward_speed
            (param_1,*(float *)(iVar2 + 0xac) - ABS((float)(*piVar1 - *param_5)) * _DAT_004bc880);
  return;
}


