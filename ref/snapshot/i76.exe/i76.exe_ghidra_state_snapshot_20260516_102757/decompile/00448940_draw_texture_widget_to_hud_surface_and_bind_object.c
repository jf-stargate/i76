/*
 * Program: i76.exe
 * Function: draw_texture_widget_to_hud_surface_and_bind_object
 * Entry: 00448940
 * Signature: undefined __cdecl draw_texture_widget_to_hud_surface_and_bind_object(uint param_1, byte * param_2, char * param_3, char * param_4, int * param_5, int param_6)
 */


/* [cgpt i76.exe player weapon targeting rename v26; confidence=medium_high] Draws a named texture
   widget to the weapon HUD surface, then optionally binds the object texture-set state. */

void __cdecl
draw_texture_widget_to_hud_surface_and_bind_object
          (uint param_1,byte *param_2,char *param_3,char *param_4,int *param_5,int param_6)

{
  undefined4 *puVar1;
  int *piVar2;
  int *piVar3;
  uint *puVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined1 *puVar9;
  byte *pbVar10;
  int *local_a4;
  undefined4 *local_a0;
  byte *local_9c;
  byte local_98 [8];
  undefined1 auStack_90 [8];
  char local_88 [16];
  char local_78 [16];
  int local_68 [13];
  int local_34 [13];
  
  strncpy(local_78,param_4,0x10);
  _strlwr(local_78);
  strncpy(local_88,param_3,0x10);
  _strlwr(local_88);
  strncpy((char *)local_98,(char *)param_2,0x10);
  _strlwr((char *)local_98);
  for (puVar1 = DAT_00531d0c; puVar1 != (undefined4 *)0x0; puVar1 = (undefined4 *)*puVar1) {
    iVar8 = 0;
    if (0 < (int)puVar1[5]) {
      piVar3 = puVar1 + 6;
      puVar9 = auStack_90 + -(int)puVar1;
      do {
        iVar7 = 0;
        piVar2 = piVar3;
        do {
          iVar5 = *piVar2 - *(int *)((int)piVar2 + (int)puVar9);
          if (iVar5 != 0) goto LAB_004489e2;
          piVar2 = piVar2 + 1;
          iVar7 = iVar7 + 1;
        } while (iVar7 < 4);
        iVar5 = 0;
LAB_004489e2:
        if (iVar5 == 0) {
          local_a0 = puVar1 + iVar8 * 8 + 6;
          local_9c = (byte *)puVar1;
          goto LAB_00448a06;
        }
        iVar8 = iVar8 + 1;
        puVar9 = puVar9 + -0x20;
        piVar3 = piVar3 + 8;
      } while (iVar8 < (int)puVar1[5]);
    }
  }
  local_a0 = (undefined4 *)0x0;
LAB_00448a06:
  local_a4 = DAT_00531d08;
  if (DAT_00531d08 != (int *)0x0) {
    do {
      iVar8 = _stricmp((char *)(local_a4 + 1),(char *)local_98);
      if (iVar8 == 0) break;
      local_a4 = (int *)*local_a4;
    } while (local_a4 != (int *)0x0);
    if ((local_a4 != (int *)0x0) && (iVar8 = 0, 0 < local_a4[5])) {
      piVar3 = local_a4 + 6;
      iVar7 = (int)&local_a0 - (int)local_a4;
      do {
        iVar5 = 0;
        piVar2 = piVar3;
        do {
          iVar6 = *piVar2 - *(int *)((int)piVar2 + iVar7);
          if (iVar6 != 0) goto LAB_00448a5d;
          piVar2 = piVar2 + 1;
          iVar5 = iVar5 + 1;
        } while (iVar5 < 4);
        iVar6 = 0;
LAB_00448a5d:
        if (iVar6 == 0) {
          local_a4 = local_a4 + iVar8 * 8 + 6;
          goto LAB_00448a86;
        }
        iVar8 = iVar8 + 1;
        iVar7 = iVar7 + -0x20;
        piVar3 = piVar3 + 8;
      } while (iVar8 < local_a4[5]);
    }
  }
  local_a4 = (int *)0x0;
LAB_00448a86:
  if ((local_a4 != (int *)0x0) && (local_a0 != (undefined4 *)0x0)) {
    piVar3 = (int *)materialize_texture_binding_surface_context(local_34,param_1,param_2);
    piVar2 = param_5;
    for (iVar8 = 0xd; iVar8 != 0; iVar8 = iVar8 + -1) {
      *piVar2 = *piVar3;
      piVar3 = piVar3 + 1;
      piVar2 = piVar2 + 1;
    }
    local_9c = (byte *)((int)local_9c + 4);
    puVar4 = load_texture_resource_resolving_vqm_cbk_to_cache(local_9c);
    if ((puVar4 != (uint *)0x0) && (param_5[5] != 0)) {
      piVar3 = (int *)construct_bitmap_surface_context
                                (local_34,*puVar4,(int)(puVar4[1] << 3) >> 3,(int)(puVar4 + 2),0);
      puVar1 = local_a0;
      piVar2 = local_68;
      for (iVar8 = 0xd; iVar8 != 0; iVar8 = iVar8 + -1) {
        *piVar2 = *piVar3;
        piVar3 = piVar3 + 1;
        piVar2 = piVar2 + 1;
      }
      iVar8 = ((int)(puVar4[1] << 3) >> 3) - local_a0[5];
      set_bitmap_surface_clip_rect
                (local_68,local_a0[4],iVar8,local_a0[6] + -1 + local_a0[4],(iVar8 - local_a0[7]) + 1
                );
      blit_bitmap_surface_context_clipped_with_palette_blend
                (param_5,local_68,local_a4[4],
                 (uint *)((((param_5[1] << 3) >> 3) - local_a4[5]) - puVar1[7]),(uint *)0x1);
      release_vqm_texture_cache_reference_by_name((char *)local_9c);
      if (param_6 != 0) {
        pbVar10 = local_98;
        piVar3 = (int *)bind_or_load_texture_set_for_object(param_1,local_98,0);
        mark_texture_set_binding_dirty_or_track_special_view(piVar3,(char *)pbVar10);
      }
    }
  }
  return;
}


