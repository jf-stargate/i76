/*
 * Program: i76.exe
 * Function: start_ai_vehicle_reverse_position_offset_state
 * Entry: 0041e740
 * Signature: undefined __cdecl start_ai_vehicle_reverse_position_offset_state(int param_1, int param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v6 ai vehicle behavior cluster: Starts a reverse-mode AI state, stores a transformed
   offset position, and initializes movement state fields. */

void __cdecl start_ai_vehicle_reverse_position_offset_state(int param_1,int param_2)

{
  float10 fVar1;
  uint uVar2;
  float *pfVar3;
  uint uVar4;
  float10 fVar5;
  float local_28 [3];
  int local_1c;
  int *local_18;
  float local_14;
  float local_10;
  float local_c;
  int *local_8;
  
  local_1c = 0;
  local_18 = (int *)0x0;
  local_8 = (int *)0x0;
  local_1c = get_vehicle_runtime_context(param_1);
  *(int *)(*(int *)(local_1c + 0x108) + 0xa998) = param_2;
  local_8 = *(int **)(local_1c + 0x108);
  fVar5 = get_runtime_time_seconds();
  fVar1 = (float10)_DAT_004bcb30;
  uVar2 = rand();
  uVar4 = (int)uVar2 >> 0x1f;
  local_8[0x2a0b] =
       (int)((float)(int)(((uVar2 ^ uVar4) - uVar4 & 1 ^ uVar4) - uVar4) + (float)(fVar5 + fVar1));
  local_8[0x2a66] = param_2;
  *(undefined4 *)(local_1c + 0xf0) = 0;
  *(undefined4 *)(local_1c + 0xe8) = 0xbf800000;
  vehicle_specials_state_getter_helper_00467370(param_1,1);
  local_8[0x20] = 0x420c0000;
  local_18 = local_8 + 0x2a54;
  local_8[0x2a58] = 0;
  pfVar3 = (float *)copy_transform_position_vec3(local_28,*local_8);
  local_14 = *pfVar3;
  local_10 = pfVar3[1];
  local_c = pfVar3[2];
  project_point_to_ai_path_segment_state(local_14,local_10,local_c,local_18);
  if ((float)*local_18 <= (float)*(int *)(local_18[7] + 0x14) / _DAT_004bcb30) {
    local_18[1] = 1;
  }
  else {
    local_18[1] = -1;
  }
  return;
}


