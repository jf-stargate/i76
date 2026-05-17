/*
 * Program: i76.exe
 * Function: network_vehicle_message_context_helper_00456320
 * Entry: 00456320
 * Signature: undefined __stdcall network_vehicle_message_context_helper_00456320(void)
 */


/* cgpt label refinement v19: was multiplayer_network_network_vehicle_message_helper_00456320.
   Remove duplicated network wording. */

void network_vehicle_message_context_helper_00456320(void)

{
  int iVar1;
  undefined2 uVar2;
  int *piVar3;
  undefined2 extraout_var;
  float10 fVar4;
  undefined4 uVar5;
  undefined2 *puVar6;
  undefined4 uVar7;
  undefined2 local_74;
  undefined1 local_72;
  float local_70;
  float local_6c [27];
  
  piVar3 = (int *)get_active_player_or_camera_world_object_entry();
  fVar4 = get_runtime_time_seconds();
  local_70 = (float)fVar4;
  if (piVar3 != (int *)0x0) {
    local_74 = 0x5453;
    local_72 = 0;
    iVar1 = *piVar3;
    if (*(int *)(iVar1 + 0x6c) == 9) {
      building_child_piece_context_helper_0046cc50(iVar1,local_6c);
    }
    else {
      vehicle_damage_network_context_helper_004644d0(iVar1,local_6c);
    }
    puVar6 = &local_74;
    uVar7 = 0x68;
    uVar5 = 0;
    uVar2 = get_multiplayer_mission_sync_player_id();
    dpSend(DAT_00541024,CONCAT22(extraout_var,DAT_00541028),uVar2,uVar5,puVar6,uVar7);
  }
  return;
}


