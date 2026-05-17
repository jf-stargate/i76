/*
 * Program: i76.exe
 * Function: update_positional_audio_activation_by_distance
 * Entry: 00422b40
 * Signature: undefined __stdcall update_positional_audio_activation_by_distance(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename v13 set A: Moves positional audio objects between active and pending
   lists based on distance to active listener/camera object. */

void update_positional_audio_activation_by_distance(void)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  int *piVar7;
  float *pfVar8;
  int iVar9;
  uint local_34;
  undefined8 local_30;
  double local_28;
  float local_20;
  float local_1c;
  float local_18;
  float local_14 [4];
  
  if (((DAT_004c2908 != (int *)0x0) ||
      (DAT_004c2908 = (int *)get_active_player_or_camera_world_object_entry(),
      DAT_004c2908 != (int *)0x0)) && (iVar1 = *DAT_004c2908, iVar1 != 0)) {
    piVar2 = (int *)DAT_00524564[7];
    while (piVar7 = piVar2, piVar7 != (int *)0x0) {
      piVar2 = (int *)*piVar7;
      if (piVar7[0x17] != 0) {
        pfVar8 = (float *)compose_world_object_runtime_transform(local_14,piVar7[0x17]);
        local_20 = *pfVar8;
        local_1c = pfVar8[1];
        local_18 = pfVar8[2];
        fVar4 = local_20 - (float)*(double *)(iVar1 + 0x40);
        fVar6 = local_1c - (float)*(double *)(iVar1 + 0x48);
        fVar5 = local_18 - (float)*(double *)(iVar1 + 0x50);
        local_30 = (double)fVar4;
        local_28 = (double)fVar6;
        if ((float)_DAT_004bccf0 <= fVar5 * fVar5 + fVar6 * fVar6 + fVar4 * fVar4) {
          piVar3 = (int *)piVar7[0x15];
          if ((piVar3 != (int *)0x0) && (piVar7 != (int *)0x0)) {
            (**(code **)(*piVar3 + 0x24))(piVar3,&local_34);
            local_30 = (double)(CONCAT44(local_30._4_4_,local_34) & 0xffffffff00000001);
            if ((local_34 & 1) != 0) {
              (**(code **)(*(int *)piVar7[0x15] + 0x48))((int *)piVar7[0x15]);
              piVar7[0x1e] = piVar7[0x1e] & 0xfffffffb;
              piVar7[0x18] = piVar7[0x18] + -1;
            }
          }
          set_audio_object_playback_flags_and_queue(piVar7,0x40);
        }
      }
    }
    piVar2 = (int *)DAT_00524564[8];
    while (piVar7 = piVar2, piVar7 != (int *)0x0) {
      piVar2 = (int *)*piVar7;
      if ((((*(byte *)(piVar7 + 0x1e) & 0x40) != 0) && (piVar7[0xf] != 0)) && (piVar7[0x17] != 0)) {
        pfVar8 = (float *)compose_world_object_runtime_transform(local_14,piVar7[0x17]);
        local_20 = *pfVar8;
        local_1c = pfVar8[1];
        local_18 = pfVar8[2];
        fVar4 = local_20 - (float)*(double *)(iVar1 + 0x40);
        fVar6 = local_1c - (float)*(double *)(iVar1 + 0x48);
        fVar5 = local_18 - (float)*(double *)(iVar1 + 0x50);
        local_28 = (double)fVar4;
        local_30 = (double)fVar6;
        if ((fVar5 * fVar5 + fVar6 * fVar6 + fVar4 * fVar4 < (float)_DAT_004bccf0) &&
           (iVar9 = attach_audio_object_resource_and_buffers(DAT_00524564,piVar7,(int *)0x0),
           iVar9 == 1)) {
          piVar7[0x1e] = piVar7[0x1e] & 0xffffffbf;
        }
      }
    }
  }
  return;
}


