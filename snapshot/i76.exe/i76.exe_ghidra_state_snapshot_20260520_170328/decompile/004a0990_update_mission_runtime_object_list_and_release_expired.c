/*
 * Program: i76.exe
 * Function: update_mission_runtime_object_list_and_release_expired
 * Entry: 004a0990
 * Signature: undefined __cdecl update_mission_runtime_object_list_and_release_expired(int * param_1, float param_2, int param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe vehicle engine/suspension rename v28; confidence=high] Updates mission runtime
   object linked lists, decrements timers, runs object updates, and releases expired
   records/lights/ordnance children. */

void __cdecl
update_mission_runtime_object_list_and_release_expired(int *param_1,float param_2,int param_3)

{
  int *piVar1;
  bool bVar2;
  int *piVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  
  while (piVar3 = param_1, piVar3 != (int *)0x0) {
    piVar1 = (int *)piVar3[0x1c];
    param_1 = (int *)piVar3[0x18];
    iVar4 = find_selected_mission_runtime_index(*piVar1);
    *(float *)(piVar3[0x1c] + 4) = *(float *)(piVar3[0x1c] + 4) - param_2;
    if ((DAT_005a8108 != 0) || (*(float *)(piVar3[0x1c] + 4) < _DAT_004bea34)) {
      bVar2 = true;
    }
    else {
      bVar2 = false;
    }
    if (bVar2) {
      iVar6 = world_object_has_optional_runtime_flag(piVar1[3]);
      uVar5 = 0;
      if (iVar6 != 0) {
        ordnance_runtime_flag_get_context_helper_004a7130((int)piVar3);
      }
    }
    else {
      uVar5 = ordnance_projectile_update_context_helper_004a0800(piVar3,param_2);
    }
    if (uVar5 == 0) {
      if ((((&g_mission_runtime_vehicle_table)[iVar4 * 0x34] == 0x11) ||
          ((&g_mission_runtime_vehicle_table)[iVar4 * 0x34] == 0x15)) &&
         (*(char *)(&DAT_006552c8 + iVar4 * 0x34) != '\0')) {
        release_texture_animation_record((int)piVar3,(char *)(&DAT_006552c8 + iVar4 * 0x34));
      }
      if ((&g_mission_runtime_vehicle_table)[iVar4 * 0x34] == 0x16) {
        unregister_world_object_smoke_emitter(piVar3);
      }
      finalize_released_world_object_after_damage((LPVOID)piVar1[3],s_ordnc_004fe6f0);
      finalize_released_world_object_after_damage((LPVOID)piVar1[4],s_ordnc_004fe6f0);
      if ((&DAT_006552c0)[iVar4 * 0x34] == 1) {
        release_world_object_light_runtime((int)piVar3);
      }
      ordnance_projectile_update_context_helper_004a06f0(iVar4,param_3,(int)piVar3);
      ordnance_object_release_context_helper_004a05f0(iVar4,2,(int)piVar3);
    }
  }
  return;
}


