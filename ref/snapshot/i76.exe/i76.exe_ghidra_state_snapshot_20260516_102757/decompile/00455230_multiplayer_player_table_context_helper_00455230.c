/*
 * Program: i76.exe
 * Function: multiplayer_player_table_context_helper_00455230
 * Entry: 00455230
 * Signature: undefined __stdcall multiplayer_player_table_context_helper_00455230(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v18: was multiplayer_network_multiplayer_player_table_helper_00455230.
   Remove duplicated multiplayer wording from readability label. */

void multiplayer_player_table_context_helper_00455230(void)

{
  uint *puVar1;
  float *pfVar2;
  float fVar3;
  float fVar4;
  bool bVar5;
  undefined3 extraout_var;
  int iVar6;
  uint uVar7;
  int *piVar8;
  float10 fVar9;
  float local_5c;
  float local_58;
  float local_54;
  undefined1 local_50;
  char local_4f;
  
  fVar9 = get_network_or_session_runtime_seconds();
  local_58 = (float)fVar9;
  fVar9 = get_gameplay_runtime_seconds();
  local_54 = (float)fVar9;
  if (_DAT_004bdf7c < local_58 - _DAT_0054106c) {
    network_vehicle_message_context_helper_00456410(0);
    _DAT_0054106c = local_58;
  }
  piVar8 = &DAT_00541098;
  do {
    if ((((short)piVar8[-10] != 0) && ((short)piVar8[-10] != DAT_00541028)) &&
       ((*(byte *)(piVar8 + -3) & 1) == 0)) {
      if (piVar8[1] == -0x40800000) {
        piVar8[1] = (int)local_58;
      }
      pfVar2 = (float *)*piVar8;
      if (pfVar2 != (float *)0x0) {
        local_5c = local_54 - (float)piVar8[4];
        if (_DAT_004bdf80 < local_5c) {
          if (pfVar2[0x1b] == 1.26117e-44) {
            create_building_world_object((int)pfVar2,local_5c);
          }
          else {
            fVar3 = pfVar2[0x1c];
            bVar5 = vehicle_damage_system_context_helper_00465350((int)pfVar2);
            fVar4 = local_5c;
            if (CONCAT31(extraout_var,bVar5) == 0) {
              if ((*(uint *)((int)fVar3 + 0x454) & 0x20000) != 0) {
                update_inactive_vehicle_ground_recovery_and_suspension_visuals((float)pfVar2);
              }
              mission_flow_map_context_helper_0049cc60((int)fVar3 + 0x444,local_5c);
              fVar9 = get_fixedstep_accumulator_seconds((int)fVar3 + 0x444);
              local_5c = (float)fVar9;
              if ((float10)_DAT_004bdf64 < fVar9) {
                do {
                  fVar4 = local_5c;
                  update_vehicle_lifecycle_and_destruction_state((int)pfVar2,local_5c);
                  update_vehicle_wheel_contact_physics_and_terrain_response(pfVar2,fVar4);
                  if (*(short *)(pfVar2 + 2) != 0) goto LAB_004553de;
                  fVar9 = get_fixedstep_accumulator_seconds((int)fVar3 + 0x444);
                  local_5c = (float)fVar9;
                } while ((float10)_DAT_004bdf64 < fVar9);
              }
            }
            else {
              update_vehicle_lifecycle_and_destruction_state((int)pfVar2,local_5c);
              update_vehicle_wheel_contact_physics_and_terrain_response(pfVar2,fVar4);
              initialize_fixedstep_accumulator_interval((float *)((int)fVar3 + 0x444),0.05);
            }
            if ((*(uint *)((int)fVar3 + 0x454) & 0x200000) != 0) {
              play_vehicle_engine_event_sound((int)pfVar2,0);
            }
            update_vehicle_skid_collision_damage_audio
                      ((int)pfVar2,*(uint *)((int)fVar3 + 0x454),*(int *)((int)fVar3 + 0x45c));
          }
        }
LAB_004553de:
        piVar8[4] = (int)local_54;
      }
    }
    if ((*(byte *)(piVar8 + -3) & 2) == 0) {
      local_5c = 1.12104e-43;
      iVar6 = dpGetPlayerData(DAT_00541024,(short)piVar8[-10],1,&local_50,&local_5c,0);
      if (iVar6 != 2) {
        iVar6 = multiplayer_chat_ui_context_helper_00452e10();
        if (iVar6 != 0) {
          uVar7 = (local_4f + 0xffff) * 0x10000;
          piVar8[-3] = piVar8[-3] | uVar7;
          if (*piVar8 != 0) {
            puVar1 = (uint *)(*piVar8 + 0x10);
            *puVar1 = *puVar1 | uVar7;
          }
        }
        piVar8[-3] = piVar8[-3] | 2;
      }
    }
    piVar8 = piVar8 + 0x12;
    if (0x541517 < (int)piVar8) {
      return;
    }
  } while( true );
}


