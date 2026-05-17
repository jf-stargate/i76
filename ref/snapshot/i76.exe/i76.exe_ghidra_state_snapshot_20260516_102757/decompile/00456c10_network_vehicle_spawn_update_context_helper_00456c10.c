/*
 * Program: i76.exe
 * Function: network_vehicle_spawn_update_context_helper_00456c10
 * Entry: 00456c10
 * Signature: undefined __cdecl network_vehicle_spawn_update_context_helper_00456c10(uint param_1, float * param_2)
 */


/* cgpt readability rename set B v14: Readability pass set B: network vehicle spawn update context
   helper based on prior focused closure context. */

void __cdecl network_vehicle_spawn_update_context_helper_00456c10(uint param_1,float *param_2)

{
  int iVar1;
  uint uVar2;
  longlong lVar3;
  short sVar4;
  size_t local_21c;
  float local_218;
  float local_214;
  float local_210;
  float local_20c;
  float local_208;
  float local_204;
  undefined1 local_200 [512];
  
  sVar4 = (short)param_1;
  iVar1 = multiplayer_player_table_context_helper_004548a0(sVar4,*param_2);
  if (iVar1 != 0) {
    uVar2 = multiplayer_player_table_context_helper_004547c0(sVar4);
    if ((uVar2 != 0) &&
       ((((uint)param_2[0x12] & 8) != 0 || ((*(byte *)(*(int *)(uVar2 + 0x70) + 0x454) & 0x20) == 0)
        ))) {
      if (*(int *)(uVar2 + 0x6c) != 9) {
        apply_network_vehicle_state_and_damage_update(uVar2,param_2);
        return;
      }
      format_kill_message(uVar2,param_2);
      return;
    }
    lVar3 = multiplayer_player_table_context_helper_00454800(sVar4);
    if (lVar3 == 0) {
      local_21c = 0x200;
      iVar1 = dpGetPlayerData(DAT_00541024,param_1,0,local_200,&local_21c,0);
      if (iVar1 != 0) {
        return;
      }
      lVar3 = reject_hacked_vehicle_join(param_1,local_200,local_21c);
    }
    if (lVar3 != 0) {
      load_or_create_player_vehicle_entity(param_1,0,0,(void *)0x0,0);
      uVar2 = multiplayer_player_table_context_helper_004547c0(sVar4);
      if (uVar2 != 0) {
        *(short *)(*(int *)(uVar2 + 0x70) + 0x480) = sVar4;
        if (*(int *)(uVar2 + 0x6c) == 9) {
          format_kill_message(uVar2,param_2);
        }
        else {
          apply_network_vehicle_state_and_damage_update(uVar2,param_2);
        }
        local_218 = (float)*(double *)(uVar2 + 0x40);
        local_214 = (float)*(double *)(uVar2 + 0x48);
        local_210 = (float)*(double *)(uVar2 + 0x50);
        local_20c = local_218;
        local_208 = local_214;
        local_204 = local_210;
        chunk_manager_lookup_or_remove_entry(&local_20c,20.0);
      }
    }
  }
  return;
}


