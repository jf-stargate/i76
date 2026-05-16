/*
 * Program: i76.exe
 * Function: initialize_vehicle_suspension_or_wheel_damage_visual
 * Entry: 0046f2b0
 * Signature: undefined __cdecl initialize_vehicle_suspension_or_wheel_damage_visual(uint param_1)
 */


/* [cgpt i76.exe vehicle mainloop physics rename v30; confidence=medium] Initializes a vehicle part
   texture animation using ZSWLS*.tmt and object texture-slot names. Likely suspension/wheel damage
   visual state. */

void __cdecl initialize_vehicle_suspension_or_wheel_damage_visual(uint param_1)

{
  byte bVar1;
  undefined4 *puVar2;
  int iVar3;
  int *piVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  uint uVar7;
  uint uVar8;
  byte *pbVar9;
  byte *pbVar10;
  byte local_10 [16];
  
  puVar2 = *(undefined4 **)(param_1 + 0x70);
  iVar3 = get_root_ancestor_world_object(param_1);
  piVar4 = (int *)get_active_player_or_camera_world_object_entry();
  if ((piVar4 == (int *)0x0) || (iVar3 != *piVar4)) {
    puVar5 = radar_context_helper_0045f3b0(0x10);
    *puVar5 = 0x24;
    puVar5[1] = 9;
    puVar5[2] = 9;
    *puVar2 = puVar5;
    puVar5[2] = 9;
    puVar5[1] = 9;
    puVar5[3] = 9;
    return;
  }
  puVar5 = radar_context_helper_0045f3b0(0x10);
  *puVar5 = 0x24;
  puVar5[1] = 9;
  puVar5[2] = 9;
  find_object_texture_slot_name(param_1,0);
  uVar6 = mission_flow_map_context_helper_0049ccc0();
  sprintf((char *)local_10,s_vehicle_suspension_wheel_damage_tmt_fmt,uVar6);
  if (((*(int *)(param_1 + 0x5c) != 0) &&
      (iVar3 = *(int *)(*(int *)(param_1 + 0x5c) + 0x14), iVar3 != 0)) &&
     (iVar3 = _stricmp((char *)(iVar3 + 0x20),(char *)local_10), iVar3 != 0)) {
    uVar7 = 0xffffffff;
    pbVar9 = local_10;
    do {
      pbVar10 = pbVar9;
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      pbVar10 = pbVar9 + 1;
      bVar1 = *pbVar9;
      pbVar9 = pbVar10;
    } while (bVar1 != 0);
    uVar7 = ~uVar7;
    pbVar9 = pbVar10 + -uVar7;
    pbVar10 = (byte *)(*(int *)(*(int *)(param_1 + 0x5c) + 0x14) + 0x20);
    for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
      *(undefined4 *)pbVar10 = *(undefined4 *)pbVar9;
      pbVar9 = pbVar9 + 4;
      pbVar10 = pbVar10 + 4;
    }
    for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
      *pbVar10 = *pbVar9;
      pbVar9 = pbVar9 + 1;
      pbVar10 = pbVar10 + 1;
    }
  }
  iVar3 = bind_texture_resource_to_object_slot(param_1,local_10,local_10);
  if (iVar3 != 0) {
    register_or_replace_texture_animation_timer(param_1,(char *)local_10,0x46f490,(int)puVar5);
  }
  *puVar2 = puVar5;
  puVar5[2] = 9;
  puVar5[1] = 9;
  puVar5[3] = 9;
  return;
}


