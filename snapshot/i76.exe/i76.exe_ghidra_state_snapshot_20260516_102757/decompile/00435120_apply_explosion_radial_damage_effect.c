/*
 * Program: i76.exe
 * Function: apply_explosion_radial_damage_effect
 * Entry: 00435120
 * Signature: undefined __cdecl apply_explosion_radial_damage_effect(float param_1, float param_2, float param_3, undefined4 param_4, int param_5, int param_6)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe mission/world/effects rename v16; confidence=MEDIUM_HIGH] Iterates live
   world/entity lists around an explosion center, checks radius/range, computes impulse/direction,
   and dispatches damage/force effect to affected objects. */

void __cdecl
apply_explosion_radial_damage_effect
          (float param_1,float param_2,float param_3,undefined4 param_4,int param_5,int param_6)

{
  double dVar1;
  LPVOID pvVar2;
  float fVar3;
  float *pfVar4;
  int *piVar5;
  int *piVar6;
  float10 fVar7;
  float local_b0;
  float local_ac;
  float local_a8;
  float local_a4;
  float local_a0;
  float local_9c;
  float local_98;
  float local_94;
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  double local_80;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  undefined4 local_20;
  undefined4 local_1c;
  float local_18 [5];
  
  if (param_5 == 0) {
    return;
  }
  local_44 = (float)*(double *)(param_5 + 0x40);
  local_40 = (float)*(double *)(param_5 + 0x48);
  local_3c = (float)*(double *)(param_5 + 0x50);
  if (g_effect_target_primary_list == (int *)0x0) {
    g_effect_target_scan_current_list_head = &g_effect_target_secondary_list;
    g_effect_target_scan_current_node = g_effect_target_secondary_list;
  }
  else {
    g_effect_target_scan_current_list_head = &g_effect_target_primary_list;
    g_effect_target_scan_current_node = g_effect_target_primary_list;
  }
  piVar5 = g_effect_target_scan_current_node;
  if (g_effect_target_scan_current_node == (int *)0x0) {
    piVar6 = (int *)0x0;
  }
  else {
    piVar6 = (int *)g_effect_target_scan_current_node[2];
  }
joined_r0x0043518e:
  do {
    if (piVar6 == (int *)0x0) {
      return;
    }
    if (*piVar6 != param_6) {
      pfVar4 = (float *)get_effect_target_transformed_position_radius(local_18,piVar6);
      local_78 = *pfVar4;
      local_74 = pfVar4[1];
      local_70 = pfVar4[2];
      local_6c = pfVar4[3];
      local_34 = local_70 - param_2;
      fVar3 = local_6c + param_3;
      local_80 = (double)CONCAT44(local_80._4_4_,fVar3);
      piVar5 = g_effect_target_scan_current_node;
      if (local_34 * local_34 + (local_78 - param_1) * (local_78 - param_1) <= fVar3 * fVar3) {
        local_b0 = local_78 - local_44;
        local_ac = local_74 - local_40;
        local_a8 = local_70 - local_3c;
        pvVar2 = (LPVOID)*piVar6;
        if (((_DAT_004bcff0 <= local_b0 * local_b0) || (_DAT_004bcff0 <= local_ac * local_ac)) ||
           (_DAT_004bcff0 <= local_a8 * local_a8)) {
          dVar1 = (double)(local_a8 * local_a8 + local_ac * local_ac + local_b0 * local_b0);
          fVar7 = zone_satellite_map_context_helper_00495000
                            (SUB84(dVar1,0),(uint)((ulonglong)dVar1 >> 0x20));
          local_80 = (double)fVar7;
          local_64 = local_ac * (float)fVar7;
          local_60 = local_a8 * (float)fVar7;
          local_68 = local_b0 * (float)fVar7;
          local_b0 = -local_68;
          local_ac = -local_64;
          local_a8 = -local_60;
          local_98 = local_b0;
          local_94 = local_ac;
          local_90 = local_a8;
        }
        else {
          local_5c = 0;
          local_58 = 0;
          local_54 = 0x3f800000;
          local_a8 = 1.0;
          local_b0 = 0.0;
          local_ac = 0.0;
        }
        local_a4 = -local_b0;
        local_a0 = -local_ac;
        local_9c = -local_a8;
        local_8c = local_a4 * local_6c;
        local_50 = 0;
        local_88 = local_a0 * local_6c;
        local_4c = 0;
        local_84 = local_9c * local_6c;
        local_24 = 0.0;
        local_48 = 0;
        local_20 = 0;
        local_1c = 0;
        local_30 = local_8c;
        local_2c = local_88;
        local_28 = local_84;
        apply_radial_damage_and_impulse_to_target(pvVar2,param_5,&local_24,&local_b0,&local_30);
        piVar5 = g_effect_target_scan_current_node;
      }
    }
    piVar6 = (int *)0x0;
  } while (piVar5 == (int *)0x0);
  g_effect_target_scan_current_node = (int *)*piVar5;
  if (g_effect_target_scan_current_node == (int *)0x0) goto code_r0x0043547f;
  goto LAB_004354a3;
code_r0x0043547f:
  if ((int **)g_effect_target_scan_current_list_head == &g_effect_target_primary_list) {
    g_effect_target_scan_current_list_head = &g_effect_target_secondary_list;
    g_effect_target_scan_current_node = g_effect_target_secondary_list;
  }
  piVar5 = g_effect_target_scan_current_node;
  if (g_effect_target_scan_current_node != (int *)0x0) {
LAB_004354a3:
    piVar6 = (int *)g_effect_target_scan_current_node[2];
    piVar5 = g_effect_target_scan_current_node;
  }
  goto joined_r0x0043518e;
}


