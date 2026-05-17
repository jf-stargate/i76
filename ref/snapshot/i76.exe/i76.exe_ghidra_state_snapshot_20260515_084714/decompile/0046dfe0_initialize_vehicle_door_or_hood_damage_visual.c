/*
 * Program: i76.exe
 * Function: initialize_vehicle_door_or_hood_damage_visual
 * Entry: 0046dfe0
 * Signature: undefined __cdecl initialize_vehicle_door_or_hood_damage_visual(uint param_1)
 */


/* [cgpt i76.exe vehicle mainloop physics rename v30; confidence=medium-high] Initializes damage
   visual state for class 0x20/0x21 child parts, records active vehicle part pointers, binds ZHR/ZHL
   texture animation resources for local-player vehicles. */

void __cdecl initialize_vehicle_door_or_hood_damage_visual(uint param_1)

{
  byte bVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  undefined4 *puVar6;
  undefined4 uVar7;
  uint uVar8;
  uint uVar9;
  byte *pbVar10;
  byte *pbVar11;
  float10 fVar12;
  byte local_10 [16];
  
  puVar2 = *(undefined4 **)(param_1 + 0x70);
  puVar2[2] = param_1;
  iVar3 = get_root_ancestor_world_object(param_1);
  iVar4 = is_vehicle_or_actor_runtime_world_object(iVar3);
  if (iVar4 != 0) {
    iVar4 = *(int *)(iVar3 + 0x70);
    piVar5 = (int *)get_active_player_or_camera_world_object_entry();
    if ((piVar5 != (int *)0x0) && (iVar3 == *piVar5)) {
      puVar2[1] = 1;
    }
    if (*(int *)(param_1 + 0x6c) == 0x20) {
      *(uint *)(iVar4 + 0x400) = param_1;
      puVar2[3] = 1;
      create_vehicle_damage_child_effect_objects(1,param_1,iVar3);
    }
    if (*(int *)(param_1 + 0x6c) == 0x21) {
      *(uint *)(iVar4 + 0x404) = param_1;
      puVar2[3] = 2;
      create_vehicle_damage_child_effect_objects(2,param_1,iVar3);
    }
    if (puVar2[1] == 1) {
      puVar6 = (undefined4 *)xalloc_global_heap(0x1c);
      if (puVar6 == (undefined4 *)0x0) {
        *puVar2 = 0;
        return;
      }
      puVar6[1] = 0;
      puVar6[2] = 0;
      puVar6[3] = 0;
      puVar6[4] = 0;
      fVar12 = get_multiplayer_or_runtime_seconds();
      puVar6[5] = (float)fVar12;
      *puVar6 = 0;
      find_object_texture_slot_name(param_1,0);
      if (*(int *)(param_1 + 0x6c) == 0x20) {
        uVar7 = mission_flow_map_context_helper_0049ccc0();
        sprintf((char *)local_10,s_vehicle_right_damage_tmt_fmt,uVar7);
      }
      if (*(int *)(param_1 + 0x6c) == 0x21) {
        uVar7 = mission_flow_map_context_helper_0049ccc0();
        sprintf((char *)local_10,s_vehicle_left_damage_tmt_fmt,uVar7);
      }
      if (((*(int *)(param_1 + 0x5c) != 0) &&
          (iVar3 = *(int *)(*(int *)(param_1 + 0x5c) + 0x14), iVar3 != 0)) &&
         (iVar3 = _stricmp((char *)(iVar3 + 0x20),(char *)local_10), iVar3 != 0)) {
        uVar8 = 0xffffffff;
        pbVar10 = local_10;
        do {
          pbVar11 = pbVar10;
          if (uVar8 == 0) break;
          uVar8 = uVar8 - 1;
          pbVar11 = pbVar10 + 1;
          bVar1 = *pbVar10;
          pbVar10 = pbVar11;
        } while (bVar1 != 0);
        uVar8 = ~uVar8;
        pbVar10 = pbVar11 + -uVar8;
        pbVar11 = (byte *)(*(int *)(*(int *)(param_1 + 0x5c) + 0x14) + 0x20);
        for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
          *(undefined4 *)pbVar11 = *(undefined4 *)pbVar10;
          pbVar10 = pbVar10 + 4;
          pbVar11 = pbVar11 + 4;
        }
        for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
          *pbVar11 = *pbVar10;
          pbVar10 = pbVar10 + 1;
          pbVar11 = pbVar11 + 1;
        }
      }
      iVar3 = bind_texture_resource_to_object_slot(param_1,local_10,local_10);
      if (iVar3 != 0) {
        register_or_replace_texture_animation_timer(param_1,(char *)local_10,0x46e5a0,(int)puVar6);
        set_texture_binding_frame_and_reload(param_1,local_10,1,0,0);
        set_texture_binding_frame_and_reload(param_1,local_10,0,0,1);
      }
      *puVar2 = puVar6;
    }
  }
  return;
}


