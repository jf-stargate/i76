/*
 * Program: i76.exe
 * Function: spawn_vehicle_chunk_debris_and_explosion
 * Entry: 00462660
 * Signature: undefined4 __cdecl spawn_vehicle_chunk_debris_and_explosion(int param_1, int param_2)
 */


/* [cgpt i76.exe vehicle mainloop physics rename v30; confidence=medium-high] Vehicle destruction
   helper. Spawns CHUNK1/CHUNK2 debris, explosion/chunk-manager effects, releases geometry variants,
   and applies radial damage/side effects. */

undefined4 __cdecl spawn_vehicle_chunk_debris_and_explosion(int param_1,int param_2)

{
  int *piVar1;
  bool bVar2;
  int iVar3;
  undefined3 extraout_var;
  int iVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  int *piVar9;
  int *piVar10;
  uint uVar11;
  uint local_20;
  uint local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c [3];
  
  local_20 = 0;
  local_1c = 0;
  iVar3 = get_root_ancestor_world_object(param_1);
  piVar1 = *(int **)(iVar3 + 0x70);
  piVar10 = (int *)piVar1[0x142];
  if ((param_2 == 0) || ((*(byte *)(piVar1 + 0x115) & 0x20) != 0)) {
    return 0;
  }
  iVar6 = 0;
  piVar9 = (int *)(param_2 + 8);
LAB_004626ab:
  if (((uint)*(ushort *)(param_2 + 4) & 1 << ((byte)iVar6 & 0x1f)) != 0) {
    if (*piVar10 < *piVar9) {
      *piVar10 = 0;
      get_world_object_class_id(iVar3,0x200);
      piVar1[0x115] = piVar1[0x115] | 0x20;
      copy_world_object_position_vector(iVar3);
      spawn_chC_runtime_effect(iVar3);
      local_18 = (float)*(double *)(iVar3 + 0x40);
      local_14 = (float)*(double *)(iVar3 + 0x48);
      local_10 = (float)*(double *)(iVar3 + 0x50);
      strncpy((char *)&local_20,s_x1_bldx1_004f7d34,8);
      spawn_cached_explosion_runtime_object
                (local_20,local_1c,iVar3,local_18,local_14,local_10,iVar3);
      dispatch_vehicle_runtime_sound_event(7,iVar3,(undefined4 *)0x0);
      piVar10 = &DAT_004f7d10;
      do {
        if ((piVar1[*piVar10 + 0x102] != 0) &&
           (bVar2 = release_or_detach_object_geometry_variant(piVar1[*piVar10 + 0x102],3),
           CONCAT31(extraout_var,bVar2) == 1)) {
          has_world_object_class_damage_handler(*piVar1);
        }
        piVar10 = piVar10 + 1;
      } while ((int)piVar10 < 0x4f7d24);
      get_world_object_class_id(iVar3,0x200);
      iVar6 = iVar3;
      if (iVar3 != 0) {
        while (*(int *)(iVar6 + 0x6c) != 0x32) {
          if (((*(int *)(iVar6 + 100) != 0) &&
              (iVar4 = weapon_hud_display_context_helper_00462600(*(int *)(iVar6 + 100)), iVar4 == 1
              )) || (piVar1 = (int *)(iVar6 + 0x60), iVar6 = *piVar1, *piVar1 == 0))
          goto LAB_004627ee;
        }
        get_world_object_class_id(iVar6,1);
      }
LAB_004627ee:
      for (iVar3 = *(int *)(iVar3 + 100); iVar3 != 0; iVar3 = *(int *)(iVar3 + 0x60)) {
        create_chunk_manager_geometry_runtime(iVar3);
      }
      param_1 = 10;
      do {
        local_c[0] = 0.0;
        local_c[1] = 0.0;
        local_c[2] = 0.0;
        uVar5 = rand();
        uVar7 = (int)uVar5 >> 0x1f;
        uVar8 = DAT_004f7d24;
        uVar11 = DAT_004f7d28;
        if (((uVar5 ^ uVar7) - uVar7 & 1 ^ uVar7) != uVar7) {
          uVar8 = DAT_004f7d2c;
          uVar11 = DAT_004f7d30;
        }
        destroy_chunk_manager_objects(uVar8,uVar11,local_18,local_14,local_10,local_c,15.0);
        param_1 = param_1 + -1;
      } while (param_1 != 0);
      return 1;
    }
    *piVar10 = *piVar10 - *piVar9;
  }
  iVar6 = iVar6 + 1;
  piVar9 = piVar9 + 1;
  if (3 < iVar6) {
    return 0;
  }
  goto LAB_004626ab;
}


