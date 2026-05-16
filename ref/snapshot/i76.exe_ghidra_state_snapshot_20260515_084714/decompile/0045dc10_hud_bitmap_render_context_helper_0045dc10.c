/*
 * Program: i76.exe
 * Function: hud_bitmap_render_context_helper_0045dc10
 * Entry: 0045dc10
 * Signature: undefined __cdecl hud_bitmap_render_context_helper_0045dc10(uint param_1, int param_2)
 */


/* cgpt label refinement v19: was cockpit_hud_ui_hud_bitmap_render_helper_0045dc10. Remove
   duplicated HUD wording. */

void __cdecl hud_bitmap_render_context_helper_0045dc10(uint param_1,int param_2)

{
  int iVar1;
  bool bVar2;
  undefined3 extraout_var;
  int iVar3;
  uint *puVar4;
  uint local_400 [256];
  
  local_400[0] = 0;
  iVar3 = 1;
  if (param_1 != 0) {
    if (param_1 == 0) goto LAB_0045dca1;
    do {
      puVar4 = local_400 + iVar3;
      do {
        if (((((*(byte *)(param_1 + 0x10) & 1) == 0) &&
             (bVar2 = ensure_world_object_geometry_variant_binding(param_1,param_2),
             CONCAT31(extraout_var,bVar2) != 0)) && (iVar1 = *(int *)(param_1 + 0x5c), iVar1 != 0))
           && (*(int *)(iVar1 + 4) != 0)) {
          for (iVar1 = *(int *)(iVar1 + 0x14); iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x30)) {
            if (*(char *)(iVar1 + 0x20) != '\0') {
              bind_or_load_texture_set_for_object
                        (param_1,(byte *)(iVar1 + 0x20),g_geo_render_matrix_or_context);
            }
          }
        }
        if (*(uint *)(param_1 + 0x60) != 0) {
          *puVar4 = *(uint *)(param_1 + 0x60);
          iVar3 = iVar3 + 1;
          puVar4 = puVar4 + 1;
        }
        param_1 = *(uint *)(param_1 + 100);
      } while (param_1 != 0);
LAB_0045dca1:
      param_1 = local_400[iVar3 + -1];
      iVar3 = iVar3 + -1;
    } while (param_1 != 0);
  }
  return;
}


