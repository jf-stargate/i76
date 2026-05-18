/*
 * Program: i76.exe
 * Function: radar_render_context_helper_00461680
 * Entry: 00461680
 * Signature: bool __cdecl radar_render_context_helper_00461680(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v19: was radar_classifier_specials_radar_render_helper_00461680. Shorten
   readability label. */

bool __cdecl radar_render_context_helper_00461680(int param_1)

{
  int iVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  float10 fVar6;
  
  if (param_1 != 0) {
    iVar3 = is_vehicle_or_actor_runtime_world_object(param_1);
    if (iVar3 != 0) {
      iVar3 = get_vehicle_runtime_context(param_1);
      if ((*(uint *)(iVar3 + 0x454) & 0x40000) != 0) {
        iVar4 = is_damage_side_effects_suppressed();
        if (iVar4 != 0) {
          piVar5 = (int *)get_active_player_or_camera_world_object_entry();
          if (piVar5 == (int *)0x0) {
            return true;
          }
          if (*piVar5 != param_1) {
            return true;
          }
        }
        iVar4 = find_active_special_equipment_component_by_index(*(int *)(param_1 + 0x70),1);
        if (iVar4 == 0) {
          iVar3 = is_damage_side_effects_suppressed();
          return iVar3 != 0;
        }
        iVar1 = *(int *)(iVar4 + 0x70);
        if (*(int *)(iVar1 + 0x10) != 0) {
          if (((*(uint *)(iVar4 + 0x10) & 0x200) == 0) && (0 < *(int *)(iVar1 + 8))) {
            fVar2 = *(float *)(iVar1 + 0x14) - _DAT_004be17c;
            fVar6 = get_gameplay_runtime_seconds();
            if (fVar6 <= (float10)fVar2) {
              return true;
            }
          }
          *(uint *)(iVar3 + 0x454) = *(uint *)(iVar3 + 0x454) & 0xfffbffff;
          mark_special_equipment_runtime_activated(iVar4);
          return false;
        }
        *(uint *)(iVar3 + 0x454) = *(uint *)(iVar3 + 0x454) & 0xfffbffff;
      }
    }
  }
  return false;
}


