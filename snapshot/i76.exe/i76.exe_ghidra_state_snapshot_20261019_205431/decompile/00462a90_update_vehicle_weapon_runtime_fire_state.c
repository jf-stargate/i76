/*
 * Program: i76.exe
 * Function: update_vehicle_weapon_runtime_fire_state
 * Entry: 00462a90
 * Signature: undefined __stdcall update_vehicle_weapon_runtime_fire_state(void)
 */


/* [cgpt i76.exe weapon/projectile v27; confidence=high] Updates vehicle weapon runtime fire state,
   including artillery/carrier diagnostics and weapon ordering checks. */

void update_vehicle_weapon_runtime_fire_state(void)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  bool bVar4;
  int iVar5;
  uint *puVar6;
  int iVar7;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  int iVar8;
  undefined4 *puVar9;
  int local_5c;
  undefined4 local_58 [22];
  
                    /* I76 semantic baseline: update_vehicle_weapon_runtime_fire_state
                       Updates vehicle weapon runtime firing state. */
  iVar5 = is_damage_side_effects_suppressed();
  if (iVar5 == 0) {
    puVar6 = (uint *)get_active_player_or_camera_world_object_entry();
    iVar5 = 0;
    if (puVar6 != (uint *)0x0) {
      if (g_network_weapon_runtime_actor_table_dirty != 0) {
        if (0 < g_network_weapon_runtime_actor_count) {
          puVar9 = &g_network_weapon_runtime_actor_entries;
          do {
            iVar8 = *(int *)*puVar9;
            iVar1 = *(int *)(*(int *)(iVar8 + 0x70) + 0x508);
            iVar7 = collect_vehicle_weapon_runtime_slots(iVar8,(int *)(iVar1 + 0xc));
            if (iVar7 != 1) {
              report_error();
            }
            iVar7 = copy_weapon_runtime_state_summary
                              (*(int *)(iVar1 + 0x10),(undefined4 *)(iVar1 + 0x2c));
            if (iVar7 != 1) {
              report_error();
            }
            set_weapon_runtime_state_field_04(iVar8,*(int *)(iVar1 + 0x10),0);
            bVar4 = weapon_runtime_slot_belongs_to_world_object(*(int *)(iVar1 + 0x10),iVar8);
            if (CONCAT31(extraout_var,bVar4) == 0) {
              report_error();
            }
            iVar5 = iVar5 + 1;
            puVar9 = puVar9 + 1;
          } while (iVar5 < g_network_weapon_runtime_actor_count);
        }
        g_network_weapon_runtime_actor_table_dirty = 0;
      }
      uVar2 = *puVar6;
      local_5c = 0;
      if (0 < g_network_weapon_runtime_actor_count) {
        puVar9 = &g_network_weapon_runtime_actor_entries;
        do {
          uVar3 = *(uint *)*puVar9;
          iVar5 = *(int *)(*(int *)(uVar3 + 0x70) + 0x508);
          if (((*(uint *)(uVar3 + 0x10) & 0x200) == 0) && (*(int *)(iVar5 + 0x4c) != 0)) {
            bVar4 = weapon_runtime_slot_belongs_to_world_object(*(int *)(iVar5 + 0x10),uVar3);
            if (CONCAT31(extraout_var_00,bVar4) == 0) {
              report_error();
            }
            extract_weapon_runtime_state_to_vsf_record(*(int *)(iVar5 + 0x10),local_58);
            if (*(int *)(iVar5 + 0x50) == 1) {
              iVar8 = test_weapon_fire_solution_against_target
                                (uVar3,uVar2,1.0,1.0,0,iVar5 + 0xc,(int *)(iVar5 + 0x2c),
                                 (int)local_58);
              if (iVar8 != 0) {
                iVar5 = *(int *)(iVar5 + 0x10);
LAB_00462c50:
                set_weapon_runtime_fire_request_flag(iVar5,1);
              }
            }
            else {
              iVar8 = rand();
              if ((iVar8 % (*(int *)(iVar5 + 0x50) * 2 + -2) == 0) &&
                 (iVar8 = test_weapon_fire_solution_against_target
                                    (uVar3,uVar2,1.0,1.0,0,iVar5 + 0xc,(int *)(iVar5 + 0x2c),
                                     (int)local_58), iVar8 != 0)) {
                iVar5 = *(int *)(iVar5 + 0x10);
                goto LAB_00462c50;
              }
            }
          }
          local_5c = local_5c + 1;
          puVar9 = puVar9 + 1;
        } while (local_5c < g_network_weapon_runtime_actor_count);
      }
    }
  }
  return;
}


