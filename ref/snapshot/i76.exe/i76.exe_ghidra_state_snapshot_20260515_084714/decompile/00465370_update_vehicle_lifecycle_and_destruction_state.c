/*
 * Program: i76.exe
 * Function: update_vehicle_lifecycle_and_destruction_state
 * Entry: 00465370
 * Signature: undefined __cdecl update_vehicle_lifecycle_and_destruction_state(int param_1, float param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe vehicle mainloop physics rename v30; confidence=high] Per-frame vehicle
   lifecycle/state update under the class frame callback. Handles delayed destruction flags,
   sound/effect transitions, refcount cleanup, loaded-vehicle removal, and child part cleanup. */

void __cdecl update_vehicle_lifecycle_and_destruction_state(int param_1,float param_2)

{
  float fVar1;
  undefined4 *puVar2;
  LPVOID pvVar3;
  float fVar4;
  int *piVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  float10 fVar9;
  
  puVar2 = *(undefined4 **)(param_1 + 0x70);
  uVar7 = puVar2[0x115];
  if (((uVar7 & 0x8000) != 0) && ((uVar7 & 0x4000) == 0)) {
    apply_vehicle_catastrophic_damage_breakup(param_1,0);
  }
  if ((uVar7 & 0x20) == 0) {
    set_vehicle_current_damage_or_effect_object(param_1,puVar2[0x40]);
    puVar2[0x40] = 0;
    if (puVar2[0x3b] != 0) {
      iVar6 = *(int *)(param_1 + 0x70);
      if ((uVar7 & 1) == 0) {
        if ((*(byte *)(iVar6 + 0x454) & 9) == 0) {
          fVar9 = start_vehicle_engine_damage_state_sound(param_1);
          *(float *)(iVar6 + 0x450) = (float)fVar9;
          uVar8 = *(uint *)(iVar6 + 0x454) | 0x80000008;
          goto LAB_00465432;
        }
      }
      else if ((*(byte *)(iVar6 + 0x454) & 1) != 0) {
        dispatch_vehicle_runtime_sound_event(2,param_1,(undefined4 *)0x0);
        uVar8 = *(uint *)(iVar6 + 0x454) & 0xfffffffe;
LAB_00465432:
        *(uint *)(iVar6 + 0x454) = uVar8;
      }
    }
    puVar2[0x3b] = 0;
  }
  else {
    iVar6 = *(int *)(param_1 + 0x70);
    if ((*(byte *)(iVar6 + 0x454) & 1) != 0) {
      dispatch_vehicle_runtime_sound_event(2,param_1,(undefined4 *)0x0);
      *(uint *)(iVar6 + 0x454) = *(uint *)(iVar6 + 0x454) & 0xfffffffe;
    }
    uVar7 = uVar7 & 0xfffffff6;
  }
  fVar4 = _g_float_zero;
  if ((uVar7 & 0x80000000) != 0) {
    fVar1 = (float)puVar2[0x114];
    puVar2[0x114] = fVar1 - param_2;
    if (fVar1 - param_2 <= fVar4) {
      uVar8 = uVar7 & 0x7fffffff;
      puVar2[0x114] = 0;
      if ((uVar7 & 0x8c08) == 8) {
        dispatch_vehicle_runtime_sound_event(0xf,param_1,(undefined4 *)0x0);
        dispatch_vehicle_runtime_sound_event(1,param_1,(undefined4 *)0x0);
        restart_vehicle_runtime_sound_state(param_1);
        uVar8 = uVar8 | 1;
      }
      else if ((uVar7 & 0x8c08) == 0x8000) {
        uVar8 = uVar7 & 0x7fff7fff;
        if ((uVar7 & 0x100000) != 0) {
          multiplayer_respawn_state_context_helper_00451570(0);
          return;
        }
        piVar5 = get_active_world_object_entry_object(param_1);
        iVar6 = world_object_has_optional_runtime_flag(param_1);
        if (iVar6 == 0) {
          if ((puVar2[0x115] & 0x4000) != 0) {
            unregister_world_object_smoke_emitter(*(LPVOID *)*puVar2);
            puVar2[0x115] = puVar2[0x115] & 0xffffffbf;
            set_vehicle_current_damage_or_effect_object(param_1,0);
            if ((*(uint *)(param_1 + 0x10) & 0x800) != 0) {
              release_world_object_light_runtime(param_1);
            }
          }
          iVar6 = is_network_or_trip_runtime_mode();
          if (iVar6 != 0) {
LAB_00465599:
            pvVar3 = (LPVOID)*piVar5;
            stop_vehicle_engine_loop_sound((int)pvVar3);
            stop_vehicle_secondary_runtime_sounds((int)pvVar3);
            entity_instance_id_lookup_or_update(piVar5);
            remove_loaded_vehicle_runtime_and_weapon_slots((int)pvVar3);
            unlink_and_release_world_object_node_refcounted(pvVar3,s_vhcl_004f8124);
            puVar2[0x115] = uVar7 & 0x7fff73f7;
            return;
          }
          iVar6 = is_damage_side_effects_suppressed();
          if (iVar6 != 0) {
            iVar6 = multiplayer_player_count_context_helper_00454620
                              (*(short *)(puVar2 + 0x120),(uchar *)0x0);
            if (iVar6 == 0) goto LAB_00465599;
          }
          iVar6 = *piVar5;
          stop_vehicle_engine_loop_sound(iVar6);
          stop_vehicle_secondary_runtime_sounds(iVar6);
          get_world_object_class_id(iVar6,1);
          unregister_effect_target_record(piVar5);
          clear_world_object_geometry_binding_and_refresh_textures(iVar6);
          iVar6 = *(int *)(iVar6 + 100);
          if (iVar6 != 0) {
            do {
              vehicle_specials_display_state_helper_00467660(iVar6);
              iVar6 = *(int *)(iVar6 + 0x60);
            } while (iVar6 != 0);
            puVar2[0x115] = uVar7 & 0x7fff73f7;
            return;
          }
        }
      }
      uVar7 = uVar8 & 0xffff73f7;
    }
    puVar2[0x115] = uVar7;
  }
  return;
}


