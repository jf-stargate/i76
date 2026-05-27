/*
 * Program: i76.exe
 * Function: update_ai_turn_state
 * Entry: 0041e970
 * Signature: undefined __cdecl update_ai_turn_state(float param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: string evidence: unkown turn state */

void __cdecl update_ai_turn_state(float param_1)

{
  undefined4 *puVar1;
  uint uVar2;
  float *pfVar3;
  int iVar4;
  uint uVar5;
  float10 fVar6;
  undefined4 local_54;
  undefined4 local_34 [3];
  undefined4 local_28 [3];
  int local_1c;
  float local_18;
  float local_14;
  float local_10;
  int local_8;
  
  local_1c = 0;
  local_8 = 0;
  local_1c = get_vehicle_runtime_context((int)param_1);
  local_8 = get_ai_vehicle_behavior_state_block((int)param_1);
  switch(*(undefined4 *)(local_8 + 0xa97c)) {
  case 0:
    if (_DAT_004bcb54 <= *(float *)(local_1c + 0xac)) {
      *(int *)(local_8 + 0xa97c) = *(int *)(local_8 + 0xa97c) + 1;
      puVar1 = (undefined4 *)copy_object_local_translation_vec3(local_28,(int)param_1 + 0x18);
      *(undefined4 *)(local_8 + 0xa970) = *puVar1;
      *(undefined4 *)(local_8 + 0xa974) = puVar1[1];
      *(undefined4 *)(local_8 + 0xa978) = puVar1[2];
      uVar2 = rand();
      uVar5 = (int)uVar2 >> 0x1f;
      if (((uVar2 ^ uVar5) - uVar5 & 1 ^ uVar5) == uVar5) {
        local_54 = 0xbf800000;
      }
      else {
        local_54 = 0x3f800000;
      }
      *(undefined4 *)(local_1c + 0xe0) = local_54;
      *(undefined4 *)(local_1c + 0xf0) = 1;
      increase_vehicle_throttle_toward_max_safe_drive(param_1);
    }
    else {
      clear_vehicle_throttle_brake_command((int)param_1);
      increase_vehicle_throttle_toward_max_safe_drive(param_1);
    }
    break;
  case 1:
    if (_DAT_004bcae4 <= *(float *)(local_1c + 0xac)) {
      pfVar3 = (float *)copy_object_local_translation_vec3(local_34,(int)param_1 + 0x18);
      local_18 = *pfVar3;
      local_14 = pfVar3[1];
      local_10 = pfVar3[2];
      fVar6 = dot_product_vec3(&local_18,(float *)(local_8 + 0xa970));
      if (fVar6 < (float10)_DAT_004bcb58) {
        *(int *)(local_8 + 0xa97c) = *(int *)(local_8 + 0xa97c) + 1;
        *(undefined4 *)(local_1c + 0xf0) = 0;
      }
    }
    else {
      *(int *)(local_8 + 0xa97c) = *(int *)(local_8 + 0xa97c) + 1;
      *(undefined4 *)(local_1c + 0xf0) = 0;
    }
    break;
  case 2:
    if (*(float *)(local_1c + 0xac) <= _DAT_004bcae4) {
      *(int *)(local_8 + 0xa97c) = *(int *)(local_8 + 0xa97c) + 1;
      *(float *)(local_1c + 0xe0) = *(float *)(local_1c + 0xe0) * _DAT_004bcb5c;
      iVar4 = is_float_nearly_zero_1e_minus4(*(float *)(local_1c + 0xe8) - _DAT_004bcae4);
      if (iVar4 == 0) {
        *(undefined4 *)(local_1c + 0xe8) = 0x3f800000;
        vehicle_specials_state_getter_helper_00467370((int)param_1,3);
      }
      else {
        *(undefined4 *)(local_1c + 0xe8) = 0xbf800000;
        vehicle_specials_state_getter_helper_00467370((int)param_1,1);
      }
    }
    else {
      set_vehicle_brake_to_max_safe_value(param_1);
    }
    break;
  case 3:
    fVar6 = get_ai_vehicle_damage_state_speed_scalar((int)param_1);
    set_ai_vehicle_throttle_brake_toward_speed(param_1,(float)fVar6);
    break;
  default:
    report_error();
  }
  return;
}


