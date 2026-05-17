/*
 * Program: i76.exe
 * Function: play_clockon_audio
 * Entry: 00442f20
 * Signature: undefined __cdecl play_clockon_audio(int param_1, int param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: references clockon.wav */

void __cdecl play_clockon_audio(int param_1,int param_2)

{
  float *pfVar1;
  int *piVar2;
  int iVar3;
  float *pfVar4;
  float10 fVar5;
  undefined8 uVar6;
  float local_bc [4];
  undefined4 local_ac;
  float local_7c;
  int local_78;
  
  if (param_2 == 2) {
    pfVar1 = (float *)build_vehicle_ordnance_runtime_context(&local_7c,param_1);
    pfVar4 = &local_7c;
    for (iVar3 = 0x1f; iVar3 != 0; iVar3 = iVar3 + -1) {
      *pfVar4 = *pfVar1;
      pfVar1 = pfVar1 + 1;
      pfVar4 = pfVar4 + 1;
    }
    piVar2 = (int *)get_active_player_or_camera_world_object_entry();
    if ((piVar2 != (int *)0x0) && (local_78 == *piVar2)) {
      iVar3 = get_vehicle_runtime_context(*piVar2);
      if ((*(uint *)(iVar3 + 0x454) & 0x40000) == 0) {
        play_sound_if_object_tree_is_audible(s_clockon_wav_004f1edc,*piVar2,(undefined4 *)0x0);
      }
    }
  }
  if ((param_2 < 7) && (DAT_0052bae8 != (undefined4 *)0x0)) {
    DAT_0052bae8[6] = 0;
    DAT_0052bae8[7] = 0;
    DAT_0052bae8[2] = param_1;
    iVar3 = rand();
    DAT_0052bae8[5] = (float)iVar3 * _DAT_004bd2d0;
    DAT_0052bae8[4] = 0;
    DAT_0052bae8[9] = param_2;
    DAT_0052bae8[10] = 0;
    DAT_0052bae8[0xb] = 0;
    DAT_0052bae8[0xc] = 0;
    DAT_0052bae8[0xd] = *(undefined4 *)(param_1 + 0x30);
    DAT_0052bae8[0xe] = *(undefined4 *)(param_1 + 0x34);
    DAT_0052bae8[0xf] = *(undefined4 *)(param_1 + 0x38);
    DAT_0052bae8[0x10] = *(undefined4 *)(param_1 + 0x40);
    DAT_0052bae8[0x11] = *(undefined4 *)(param_1 + 0x44);
    DAT_0052bae8[0x12] = *(undefined4 *)(param_1 + 0x48);
    DAT_0052bae8[0x13] = *(undefined4 *)(param_1 + 0x4c);
    DAT_0052bae8[0x14] = *(undefined4 *)(param_1 + 0x50);
    DAT_0052bae8[0x15] = *(undefined4 *)(param_1 + 0x54);
    DAT_0052bae8[1] = DAT_0052ba50;
    DAT_0052ba50 = DAT_0052ba50 + 1;
    fVar5 = get_multiplayer_or_runtime_seconds();
    DAT_0052bae8[3] = (float)(fVar5 - (float10)_DAT_004bd2c8);
    pfVar1 = (float *)&DAT_004faed8;
    pfVar4 = local_bc;
    for (iVar3 = 0x10; uVar6 = CONCAT44(local_bc[0],local_bc[1]), iVar3 != 0; iVar3 = iVar3 + -1) {
      *pfVar4 = *pfVar1;
      pfVar1 = pfVar1 + 1;
      pfVar4 = pfVar4 + 1;
    }
    if (param_2 < 3) {
      uVar6 = mission_flow_map_context_helper_0049d400((float)DAT_0052bae8[5]);
      local_ac = (undefined4)((ulonglong)uVar6 >> 0x20);
      local_bc[3] = -(float)uVar6;
    }
    local_bc[0] = (float)((ulonglong)uVar6 >> 0x20);
    local_bc[1] = (float)uVar6;
    pfVar1 = compose_matrix_or_transform_a(&local_7c,local_bc,(float *)(param_1 + 0x18));
    pfVar4 = local_bc;
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      *pfVar4 = *pfVar1;
      pfVar1 = pfVar1 + 1;
      pfVar4 = pfVar4 + 1;
    }
    transform_vec3_array_by_matrix((float *)(DAT_0052bae8 + 0x16),(float *)&DAT_004f1c88,3,local_bc)
    ;
    DAT_0052bae8 = (undefined4 *)*DAT_0052bae8;
  }
  return;
}


