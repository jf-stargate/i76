/*
 * Program: i76.exe
 * Function: update_distance_culled_world_object_render_state
 * Entry: 004066e0
 * Signature: undefined __stdcall update_distance_culled_world_object_render_state(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe runtime loop refinement v23; confidence=MEDIUM_HIGH] Per-frame camera/distance
   culling pass over active world-object entries. Releases or marks far object/child render state
   outside configured radii. */

void update_distance_culled_world_object_render_state(void)

{
  int iVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int *piVar5;
  
                    /* I76 semantic baseline: update_distance_culled_world_object_render_state
                       Per-frame camera/distance culling over active world-object entries. */
  entity_instance_table_context_helper_00457560();
  piVar5 = (int *)entity_instance_id_table_context_helper_004574e0();
  while (piVar5 != (int *)0x0) {
    iVar1 = *piVar5;
    if ((*(uint *)(iVar1 + 0x10) & 0x100) == 0) {
      fVar2 = (float)*(double *)(iVar1 + 0x40) - (float)_DAT_004c2890;
      fVar4 = (float)*(double *)(iVar1 + 0x48) - (float)_DAT_004c2898;
      fVar3 = (float)*(double *)(iVar1 + 0x50) - (float)_DAT_004c28a0;
      fVar2 = fVar3 * fVar3 + fVar4 * fVar4 + fVar2 * fVar2;
      if ((DAT_004c2748 * DAT_004c2748 < fVar2) || (_DAT_004c2744 * _DAT_004c2744 < fVar2)) {
        if (piVar5[0xd] == 0) {
          if (iVar1 != 0) {
            clear_world_object_geometry_binding_and_refresh_textures(iVar1);
            for (iVar1 = *(int *)(iVar1 + 100); iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x60)) {
              recursive_clear_world_object_geometry_bindings(iVar1);
            }
          }
          piVar5[0xd] = 1;
        }
      }
      else {
        piVar5[0xd] = 0;
      }
    }
    piVar5 = (int *)entity_instance_id_table_context_helper_004574e0();
  }
  return;
}


