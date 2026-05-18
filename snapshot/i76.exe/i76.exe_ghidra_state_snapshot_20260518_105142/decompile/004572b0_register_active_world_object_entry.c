/*
 * Program: i76.exe
 * Function: register_active_world_object_entry
 * Entry: 004572b0
 * Signature: int * __cdecl register_active_world_object_entry(int param_1, int param_2, int * param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe mission/world/effects rename v16; confidence=HIGH] Allocates/reuses an
   active-world-object entry, increments the object tree refcount, stores center/radius bounds,
   marks the active player/object entry when flagged, and invokes registered callbacks. */

int * __cdecl register_active_world_object_entry(int param_1,int param_2,int *param_3)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  undefined4 *puVar4;
  float10 fVar5;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  iVar1 = 0;
  piVar3 = (int *)0x0;
  if (0 < g_active_world_object_entry_count) {
    piVar2 = &g_active_world_object_entries;
    do {
      if (*piVar2 == 0) {
        piVar3 = &g_active_world_object_entries + iVar1 * 0x1e;
        break;
      }
      iVar1 = iVar1 + 1;
      piVar2 = piVar2 + 0x1e;
    } while (iVar1 < g_active_world_object_entry_count);
  }
  if (piVar3 == (int *)0x0) {
    if (g_active_world_object_entry_count == 0x100) {
      report_chunk_parse_error();
    }
    piVar3 = &g_active_world_object_entries + g_active_world_object_entry_count * 0x1e;
    g_active_world_object_entry_count = g_active_world_object_entry_count + 1;
  }
  increment_refcount_recursive_for_object_tree(param_1,s_ent_004f5d04);
  *piVar3 = param_1;
  piVar3[6] = 0;
  if (param_2 != 0) {
    piVar3[5] = 1;
    piVar3[6] = param_2;
  }
  if (param_3 != (int *)0x0) {
    piVar2 = piVar3 + 7;
    for (iVar1 = 5; iVar1 != 0; iVar1 = iVar1 + -1) {
      *piVar2 = *param_3;
      param_3 = param_3 + 1;
      piVar2 = piVar2 + 1;
    }
    piVar3[0xc] = 1;
  }
  compute_world_object_transformed_bounds(param_1,&local_18,&local_c);
  local_18 = (local_c + local_18) * _DAT_004bdf88;
  piVar3[1] = (int)local_18;
  local_14 = (local_8 + local_14) * _DAT_004bdf88;
  piVar3[2] = (int)local_14;
  local_10 = (local_4 + local_10) * _DAT_004bdf88;
  piVar3[3] = (int)local_10;
  fVar5 = compute_world_object_bounding_radius_from_point(param_1,local_18,local_14,local_10);
  piVar3[4] = (int)(float)fVar5;
  if ((*(byte *)(param_1 + 0x10) & 0x10) != 0) {
    g_active_player_or_camera_world_object_entry = piVar3;
  }
  iVar1 = 0;
  if (0 < g_world_object_entry_callback_count) {
    puVar4 = &g_world_object_entry_callbacks;
    do {
      (*(code *)*puVar4)(piVar3);
      iVar1 = iVar1 + 1;
      puVar4 = puVar4 + 1;
    } while (iVar1 < g_world_object_entry_callback_count);
  }
  return piVar3;
}


