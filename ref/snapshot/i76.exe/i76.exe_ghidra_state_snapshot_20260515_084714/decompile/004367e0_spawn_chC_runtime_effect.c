/*
 * Program: i76.exe
 * Function: spawn_chC_runtime_effect
 * Entry: 004367e0
 * Signature: undefined __cdecl spawn_chC_runtime_effect(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe damage runtime deeptrace v20; confidence=low-medium] Effect helper anchored by chC
   string; exact effect role needs later pass. */

void __cdecl spawn_chC_runtime_effect(int param_1)

{
  int iVar1;
  int *piVar2;
  float10 fVar3;
  undefined4 *puVar4;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  piVar2 = get_active_world_object_entry_object(param_1);
  if (piVar2 == (int *)0x0) {
    return;
  }
  if (piVar2[5] == 3) {
    for (iVar1 = *piVar2; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x60)) {
      if ((*(uint *)(iVar1 + 0x10) & 0xf000) == 0x3000) {
        release_effect_target_collision_payload(iVar1);
      }
      if (*(int *)(iVar1 + 100) != 0) {
        find_nearest_effect_target_in_scan_list_helper_00436980(*(int *)(iVar1 + 100));
      }
    }
  }
  free_effect_target_collision_link_chain((int)piVar2);
  effect_target_distance_filter_helper_004369c0(param_1);
  switch(*(undefined4 *)(*piVar2 + 0x6c)) {
  case 1:
  case 9:
    effect_target_scan_target_query_helper_00436d90((int)piVar2);
    goto switchD_0043685c_caseD_5;
  case 2:
  case 7:
  case 8:
  case 10:
    piVar2[5] = 3;
    DAT_0052b92c = 0x2000;
    puVar4 = (undefined4 *)*piVar2;
    break;
  case 3:
  case 0xb:
  case 0xc:
    piVar2[5] = 3;
    DAT_0052b92c = 0x3000;
    puVar4 = (undefined4 *)*piVar2;
    break;
  case 4:
    piVar2[5] = 3;
    DAT_0052b92c = 0x5000;
    puVar4 = (undefined4 *)*piVar2;
    break;
  default:
    goto switchD_0043685c_caseD_5;
  }
  effect_target_visibility_scan_helper_00436c60(puVar4,(float *)&DAT_004faed8);
switchD_0043685c_caseD_5:
  effect_target_object_has_collision_geometry(piVar2);
  compute_world_object_transformed_bounds(*piVar2,&local_18,&local_c);
  local_18 = (local_c + local_18) * _DAT_004bd020;
  piVar2[1] = (int)local_18;
  local_14 = (local_8 + local_14) * _DAT_004bd020;
  piVar2[2] = (int)local_14;
  local_10 = (local_4 + local_10) * _DAT_004bd020;
  piVar2[3] = (int)local_10;
  fVar3 = compute_world_object_bounding_radius_from_point(*piVar2,local_18,local_14,local_10);
  piVar2[4] = (int)(float)fVar3;
  return;
}


