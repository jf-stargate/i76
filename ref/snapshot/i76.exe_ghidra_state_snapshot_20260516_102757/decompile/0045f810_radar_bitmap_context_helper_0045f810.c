/*
 * Program: i76.exe
 * Function: radar_bitmap_context_helper_0045f810
 * Entry: 0045f810
 * Signature: undefined __cdecl radar_bitmap_context_helper_0045f810(uint param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set B v14: Readability pass set B: radar bitmap context helper based on
   prior focused closure context. */

void __cdecl radar_bitmap_context_helper_0045f810(uint param_1)

{
  int iVar1;
  undefined4 uVar2;
  int *piVar3;
  undefined4 *puVar4;
  byte *pbVar5;
  
  iVar1 = *(int *)(param_1 + 0x70);
  _DAT_0054b16c = 0;
  uVar2 = get_root_ancestor_world_object(param_1);
  *(undefined4 *)(iVar1 + 0x78) = uVar2;
  *(uint *)(iVar1 + 0x7c) = param_1;
  world_object_geometry_context_helper_00458860(param_1,1);
  *(uint *)(*(int *)(*(int *)(iVar1 + 0x78) + 0x70) + 0x434) = param_1;
  piVar3 = (int *)get_active_player_or_camera_world_object_entry();
  if ((piVar3 != (int *)0x0) && (*(int *)(iVar1 + 0x78) == *piVar3)) {
    puVar4 = HeapAlloc(DAT_0054b1f4,0,0x10);
    *puVar4 = 0;
    puVar4[1] = 0x1d;
    puVar4[3] = 0;
    pbVar5 = (byte *)find_object_texture_slot_name(param_1,0);
    if ((pbVar5 != (byte *)0x0) && (*pbVar5 != 0)) {
      register_or_replace_texture_animation_timer(param_1,(char *)pbVar5,0x460310,(int)puVar4);
      set_texture_binding_frame_and_reload(param_1,pbVar5,1,0,0);
      set_texture_binding_frame_and_reload(param_1,pbVar5,0,puVar4[3],1);
    }
    *(undefined4 **)(iVar1 + 8) = puVar4;
    return;
  }
  puVar4 = HeapAlloc(DAT_0054b1f4,0,0x10);
  *puVar4 = 0;
  puVar4[1] = 0x1d;
  puVar4[3] = 0;
  *(undefined4 **)(iVar1 + 8) = puVar4;
  return;
}


