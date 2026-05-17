/*
 * Program: i76.exe
 * Function: apply_flat_tire_damage_from_hazard_collision
 * Entry: 00466eb0
 * Signature: undefined __cdecl apply_flat_tire_damage_from_hazard_collision(float param_1, int * param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe vehicle engine/suspension rename v28; confidence=high] Vehicle/hazard collision
   path that finds nearest wheel/part slot, applies flat tire damage, and updates flat tire texture
   frames. */

void __cdecl apply_flat_tire_damage_from_hazard_collision(float param_1,int *param_2)

{
  bool bVar1;
  float *pfVar2;
  int iVar3;
  int *piVar4;
  uint uVar5;
  int iVar6;
  float fVar7;
  int iVar8;
  int *piVar9;
  uint uVar10;
  byte *pbVar11;
  int local_3c;
  undefined4 local_38;
  uint local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  undefined4 local_c [3];
  
  piVar9 = param_2;
  if ((*(int *)((int)param_1 + 0x6c) == 1) && (param_2[0x1b] == 0x33)) {
    piVar4 = *(int **)((int)param_1 + 0x70);
    param_2 = piVar4;
    pfVar2 = (float *)compose_world_object_runtime_transform(&local_18,(int)piVar9);
    local_30 = *pfVar2;
    iVar6 = 0;
    iVar8 = 0;
    local_2c = pfVar2[1];
    param_1 = 3.4028235e+38;
    local_28 = pfVar2[2];
    piVar4 = piVar4 + 0xea;
    do {
      iVar3 = *piVar4;
      if (iVar3 != 0) {
        pfVar2 = (float *)get_tire_world_position_minus_contact_offset(local_c,iVar3);
        local_24 = *pfVar2;
        local_20 = pfVar2[1];
        local_1c = pfVar2[2];
        local_14 = local_2c - local_20;
        local_10 = local_28 - local_1c;
        fVar7 = local_10 * local_10 +
                local_14 * local_14 + (local_30 - local_24) * (local_30 - local_24);
        if (fVar7 < param_1) {
          iVar6 = iVar3;
          param_1 = fVar7;
          local_3c = iVar8;
        }
      }
      iVar8 = iVar8 + 1;
      piVar4 = piVar4 + 1;
    } while (iVar8 < 6);
    if (iVar6 != 0) {
      bVar1 = false;
      iVar8 = 3;
      piVar9 = param_2 + 0xfb;
      do {
        iVar3 = get_special_equipment_runtime_index(*piVar9);
        if (iVar3 == 0xb) {
          bVar1 = true;
        }
        piVar9 = piVar9 + 1;
        iVar8 = iVar8 + -1;
      } while (iVar8 != 0);
      if (bVar1) {
        extract_part_damage_state_pair(iVar6,&param_1,&local_38);
        param_1 = (float)ftol();
        set_damageable_part_state_pair(iVar6,param_1,local_38);
        iVar6 = local_3c;
        piVar9 = param_2;
        if (((int)param_1 < 0x1a) && (param_2[local_3c + 0xea] != 0)) {
          extract_part_damage_state_pair(param_2[local_3c + 0xea],&local_3c,&param_2);
          fVar7 = _g_float_zero;
          if (param_2 != (int *)0x0) {
            fVar7 = (float)local_3c / (float)(int)param_2;
          }
          if (fVar7 <= _DAT_004be1e8) {
            if (fVar7 <= _DAT_004be1dc) {
              uVar10 = 2;
              if (fVar7 <= _DAT_004be1ec) {
                uVar10 = 3;
              }
            }
            else {
              uVar10 = 1;
            }
          }
          else {
            uVar10 = 0;
          }
          uVar5 = iVar6 + 5;
          update_vehicle_damage_texture_state(piVar9,uVar5,uVar10);
          if (uVar5 < 5) {
            local_34 = piVar9[(&g_vehicle_damage_texture_slot_offsets)[uVar5] + 0x102];
            fVar7 = param_1;
            switch(uVar10) {
            case 0:
              fVar7 = 0.0;
              break;
            case 1:
            case 2:
              fVar7 = 1.4013e-45;
              break;
            case 3:
              fVar7 = 2.8026e-45;
            }
            iVar6 = 0;
            if (0 < (int)(&g_vehicle_damage_texture_region_counts)[uVar5]) {
              pbVar11 = (byte *)(g_vehicle_damage_texture_name_table + uVar5 * 0x82);
              do {
                set_texture_binding_frame_and_reload(local_34,pbVar11,0,(int)fVar7,1);
                iVar6 = iVar6 + 1;
                pbVar11 = pbVar11 + 0xd;
              } while (iVar6 < (int)(&g_vehicle_damage_texture_region_counts)[uVar5]);
              return;
            }
          }
        }
      }
      else {
        set_damageable_part_state_pair(iVar6,0x19,100);
        iVar6 = local_3c;
        piVar9 = param_2;
        if (param_2[local_3c + 0xea] != 0) {
          extract_part_damage_state_pair(param_2[local_3c + 0xea],&param_2,&param_1);
          fVar7 = _g_float_zero;
          if (param_1 != 0.0) {
            fVar7 = (float)(int)param_2 / (float)(int)param_1;
          }
          if (fVar7 <= _DAT_004be1e8) {
            if (fVar7 <= _DAT_004be1dc) {
              uVar10 = 2;
              if (fVar7 <= _DAT_004be1ec) {
                uVar10 = 3;
              }
            }
            else {
              uVar10 = 1;
            }
          }
          else {
            uVar10 = 0;
          }
          uVar5 = iVar6 + 5;
          update_vehicle_damage_texture_state(piVar9,uVar5,uVar10);
          if (uVar5 < 5) {
            local_34 = piVar9[(&g_vehicle_damage_texture_slot_offsets)[uVar5] + 0x102];
            fVar7 = param_1;
            switch(uVar10) {
            case 0:
              fVar7 = 0.0;
              break;
            case 1:
            case 2:
              fVar7 = 1.4013e-45;
              break;
            case 3:
              fVar7 = 2.8026e-45;
            }
            iVar6 = 0;
            if (0 < (int)(&g_vehicle_damage_texture_region_counts)[uVar5]) {
              pbVar11 = (byte *)(g_vehicle_damage_texture_name_table + uVar5 * 0x82);
              do {
                set_texture_binding_frame_and_reload(local_34,pbVar11,0,(int)fVar7,1);
                iVar6 = iVar6 + 1;
                pbVar11 = pbVar11 + 0xd;
              } while (iVar6 < (int)(&g_vehicle_damage_texture_region_counts)[uVar5]);
            }
          }
        }
      }
    }
  }
  return;
}


