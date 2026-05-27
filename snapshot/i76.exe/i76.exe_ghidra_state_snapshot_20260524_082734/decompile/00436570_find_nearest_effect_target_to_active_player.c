/*
 * Program: i76.exe
 * Function: find_nearest_effect_target_to_active_player
 * Entry: 00436570
 * Signature: undefined4 __stdcall find_nearest_effect_target_to_active_player(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename v13 set A: Scans secondary effect-target list around the active
   player/camera object and returns/updates nearest target information. */

undefined4 find_nearest_effect_target_to_active_player(void)

{
  int *piVar1;
  float *pfVar2;
  int iVar3;
  float10 fVar4;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_3c;
  float local_38;
  float local_34 [3];
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18 [3];
  float local_c;
  
  piVar1 = (int *)get_active_player_or_camera_world_object_entry();
  if (piVar1 != (int *)0x0) {
    effect_target_list_scan_context_helper_004387b0(local_18,piVar1);
    pfVar2 = (float *)get_effect_target_transformed_position_radius(local_18,piVar1);
    local_28 = *pfVar2;
    local_24 = pfVar2[1];
    local_20 = pfVar2[2];
    local_1c = pfVar2[3];
    g_effect_target_scan_current_list_head = &g_effect_target_secondary_list;
    g_effect_target_scan_current_node = g_effect_target_secondary_list;
    piVar1 = (int *)0x0;
    if (g_effect_target_secondary_list != (int *)0x0) {
      piVar1 = (int *)g_effect_target_secondary_list[2];
    }
    if (piVar1 != (int *)0x0) {
      do {
        iVar3 = target_reticle_context_helper_00458f40(*piVar1,0x5c);
        if (iVar3 != 0) {
          compute_world_object_transformed_bounds(iVar3,&local_70,&local_4c);
          local_70 = (local_4c + local_70) * _DAT_004bd020;
          local_6c = (local_48 + local_6c) * _DAT_004bd020;
          local_68 = (local_44 + local_68) * _DAT_004bd020;
          fVar4 = compute_world_object_bounding_radius_from_point(iVar3,local_70,local_6c,local_68);
          local_c = (float)fVar4;
          pfVar2 = (float *)compose_world_object_runtime_transform(local_34,iVar3);
          local_58 = *pfVar2;
          local_54 = pfVar2[1];
          local_50 = pfVar2[2];
          local_3c = local_54 + local_6c;
          local_38 = local_50 + local_68;
          local_64 = local_28 - (local_58 + local_70);
          local_60 = local_24 - local_3c;
          local_5c = local_20 - local_38;
          if (local_5c * local_5c + local_60 * local_60 + local_64 * local_64 < local_c * local_c) {
            return 1;
          }
        }
        if (g_effect_target_scan_current_node == (int *)0x0) {
LAB_00436726:
          piVar1 = (int *)0x0;
        }
        else {
          g_effect_target_scan_current_node = (int *)*g_effect_target_scan_current_node;
          if (g_effect_target_scan_current_node == (int *)0x0) goto LAB_00436726;
          piVar1 = (int *)g_effect_target_scan_current_node[2];
        }
        if (piVar1 == (int *)0x0) {
          return 0;
        }
      } while( true );
    }
  }
  return 0;
}


