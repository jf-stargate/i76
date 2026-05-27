/*
 * Program: i76.exe
 * Function: update_effect_target_collision_pairs
 * Entry: 004349c0
 * Signature: undefined __stdcall update_effect_target_collision_pairs(void)
 */


/* [cgpt i76.exe main runtime/FSM rename v21; confidence=MEDIUM_HIGH] Updates effect target
   transformed bounds, scans primary/secondary target lists, and dispatches target pair
   collision/effect checks.
   old_name: FUN_004349c0 */

void update_effect_target_collision_pairs(void)

{
  int *piVar1;
  int *piVar2;
  undefined4 *puVar3;
  float fVar4;
  float fVar5;
  int *piVar6;
  undefined4 *puVar7;
  float *pfVar8;
  int *piVar9;
  float10 fVar10;
  undefined4 local_30;
  float local_2c [2];
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10 [4];
  
                    /* I76 semantic baseline: update_effect_target_collision_pairs
                       Updates effect-target transformed bounds and collision/effect pairs. */
  piVar9 = g_effect_target_primary_list;
  if (g_effect_target_primary_list != (int *)0x0) {
    do {
      piVar1 = (int *)piVar9[2];
      fVar10 = get_runtime_update_delta_seconds();
      pfVar8 = (float *)get_effect_target_transformed_position_radius(local_10,piVar1);
      local_20 = *pfVar8;
      local_1c = pfVar8[1];
      local_18 = pfVar8[2];
      local_14 = pfVar8[3];
      get_world_object_damage_or_target_vectors(*piVar1,local_2c,&local_30);
      piVar1[0x14] = (int)local_20;
      fVar4 = local_2c[0] * (float)fVar10 + local_20;
      piVar1[0x16] = (int)local_18;
      piVar1[0x17] = (int)fVar4;
      fVar5 = local_24 * (float)fVar10 + local_18;
      piVar1[0x19] = (int)fVar5;
      if (fVar4 < local_20) {
        piVar1[0x14] = (int)fVar4;
        piVar1[0x17] = (int)local_20;
      }
      if (fVar5 < local_18) {
        piVar1[0x16] = (int)fVar5;
        piVar1[0x19] = (int)local_18;
      }
      piVar1[0x14] = (int)((float)piVar1[0x14] - (float)piVar1[4]);
      piVar1[0x16] = (int)((float)piVar1[0x16] - (float)piVar1[4]);
      piVar1[0x17] = (int)((float)piVar1[4] + (float)piVar1[0x17]);
      piVar1[0x19] = (int)((float)piVar1[4] + (float)piVar1[0x19]);
      piVar9 = (int *)*piVar9;
      piVar1 = g_effect_target_primary_list;
    } while (piVar9 != (int *)0x0);
    while (piVar9 = piVar1, piVar9 != (int *)0x0) {
      piVar1 = (int *)*piVar9;
      piVar6 = piVar1;
      while (puVar3 = g_effect_target_secondary_list, piVar6 != (int *)0x0) {
        piVar2 = (int *)*piVar6;
        preload_vehicle_voice_audio_clips((int *)piVar9[2],(int *)piVar6[2]);
        piVar6 = piVar2;
      }
      while (puVar7 = puVar3, puVar7 != (undefined4 *)0x0) {
        DAT_0052b924 = 0;
        puVar3 = (undefined4 *)*puVar7;
        DAT_0052b938 = 1;
        preload_vehicle_voice_audio_clips((int *)piVar9[2],(int *)puVar7[2]);
        if ((DAT_0052b924 != 0) && (DAT_0052b938 != 0)) {
          merge_system_log_tag((int *)puVar7[2],(int *)piVar9[2]);
        }
      }
    }
  }
  return;
}


