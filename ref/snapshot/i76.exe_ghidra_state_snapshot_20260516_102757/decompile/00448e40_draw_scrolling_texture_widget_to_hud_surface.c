/*
 * Program: i76.exe
 * Function: draw_scrolling_texture_widget_to_hud_surface
 * Entry: 00448e40
 * Signature: undefined __cdecl draw_scrolling_texture_widget_to_hud_surface(int * param_1, uint param_2, char * param_3, char * param_4, char * param_5, char * param_6)
 */


/* [cgpt i76.exe player weapon targeting rename v26; confidence=medium_high] Draws a split/scrolling
   texture widget region into the HUD surface, used by rolling ammo digit wheels. */

void __cdecl
draw_scrolling_texture_widget_to_hud_surface
          (int *param_1,uint param_2,char *param_3,char *param_4,char *param_5,char *param_6)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int *piVar3;
  int *piVar4;
  uint *puVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  undefined4 *puVar10;
  undefined1 *puVar11;
  byte *pbVar12;
  undefined4 *local_f0;
  undefined4 *local_ec;
  int *local_e8;
  undefined4 *local_e4;
  byte *local_e0;
  byte local_dc [8];
  undefined1 auStack_d4 [8];
  char local_cc [8];
  undefined1 auStack_c4 [8];
  char local_bc [16];
  char local_ac [16];
  int local_9c [5];
  int local_88;
  int local_68 [13];
  int local_34 [13];
  
  strncpy(local_ac,param_5,0x10);
  _strlwr(local_ac);
  strncpy(local_bc,param_6,0x10);
  _strlwr(local_bc);
  strncpy(local_cc,param_4,0x10);
  _strlwr(local_cc);
  strncpy((char *)local_dc,param_3,0x10);
  _strlwr((char *)local_dc);
  for (local_ec = DAT_00531d0c; local_f0 = DAT_00531d0c, local_ec != (undefined4 *)0x0;
      local_ec = (undefined4 *)*local_ec) {
    iVar9 = 0;
    if (0 < (int)local_ec[5]) {
      piVar4 = local_ec + 6;
      puVar11 = auStack_c4 + -(int)local_ec;
      do {
        iVar8 = 0;
        piVar3 = piVar4;
        do {
          iVar6 = *piVar3 - *(int *)((int)piVar3 + (int)puVar11);
          if (iVar6 != 0) goto LAB_00448f00;
          piVar3 = piVar3 + 1;
          iVar8 = iVar8 + 1;
        } while (iVar8 < 4);
        iVar6 = 0;
LAB_00448f00:
        if (iVar6 == 0) {
          local_e4 = local_ec;
          local_ec = local_ec + iVar9 * 8 + 6;
          goto joined_r0x00448f30;
        }
        iVar9 = iVar9 + 1;
        puVar11 = puVar11 + -0x20;
        piVar4 = piVar4 + 8;
      } while (iVar9 < (int)local_ec[5]);
    }
  }
  local_ec = (undefined4 *)0x0;
joined_r0x00448f30:
  do {
    if (local_f0 == (undefined4 *)0x0) break;
    iVar9 = 0;
    if (0 < (int)local_f0[5]) {
      piVar4 = local_f0 + 6;
      puVar11 = auStack_d4 + -(int)local_f0;
      do {
        iVar8 = 0;
        piVar3 = piVar4;
        do {
          iVar6 = *piVar3 - *(int *)((int)piVar3 + (int)puVar11);
          if (iVar6 != 0) goto LAB_00448f63;
          piVar3 = piVar3 + 1;
          iVar8 = iVar8 + 1;
        } while (iVar8 < 4);
        iVar6 = 0;
LAB_00448f63:
        if (iVar6 == 0) {
          local_f0 = local_f0 + iVar9 * 8 + 6;
          goto LAB_00448f9b;
        }
        iVar9 = iVar9 + 1;
        puVar11 = puVar11 + -0x20;
        piVar4 = piVar4 + 8;
      } while (iVar9 < (int)local_f0[5]);
    }
    local_f0 = (undefined4 *)*local_f0;
  } while( true );
  local_f0 = (undefined4 *)0x0;
LAB_00448f9b:
  local_e8 = DAT_00531d08;
  if (DAT_00531d08 != (int *)0x0) {
    do {
      iVar9 = _stricmp((char *)(local_e8 + 1),(char *)local_dc);
      if (iVar9 == 0) break;
      local_e8 = (int *)*local_e8;
    } while (local_e8 != (int *)0x0);
    if ((local_e8 != (int *)0x0) && (iVar9 = 0, 0 < local_e8[5])) {
      piVar4 = local_e8 + 6;
      iVar8 = (int)&local_e4 - (int)local_e8;
      do {
        iVar6 = 0;
        piVar3 = piVar4;
        do {
          iVar7 = *piVar3 - *(int *)((int)piVar3 + iVar8);
          if (iVar7 != 0) goto LAB_00448ff3;
          piVar3 = piVar3 + 1;
          iVar6 = iVar6 + 1;
        } while (iVar6 < 4);
        iVar7 = 0;
LAB_00448ff3:
        if (iVar7 == 0) {
          local_e8 = local_e8 + iVar9 * 8 + 6;
          goto LAB_0044901c;
        }
        iVar9 = iVar9 + 1;
        iVar8 = iVar8 + -0x20;
        piVar4 = piVar4 + 8;
      } while (iVar9 < local_e8[5]);
    }
  }
  local_e8 = (int *)0x0;
LAB_0044901c:
  if (((local_ec != (undefined4 *)0x0) && (local_f0 != (undefined4 *)0x0)) &&
     (local_e8 != (int *)0x0)) {
    piVar4 = (int *)materialize_texture_binding_surface_context(local_68,param_2,local_dc);
    pbVar12 = local_dc;
    piVar3 = local_9c;
    for (iVar9 = 0xd; iVar9 != 0; iVar9 = iVar9 + -1) {
      *piVar3 = *piVar4;
      piVar4 = piVar4 + 1;
      piVar3 = piVar3 + 1;
    }
    piVar4 = (int *)bind_or_load_texture_set_for_object(param_2,local_dc,0);
    mark_texture_set_binding_dirty_or_track_special_view(piVar4,(char *)pbVar12);
    local_e0 = (byte *)(local_e4 + 1);
    puVar5 = load_texture_resource_resolving_vqm_cbk_to_cache(local_e0);
    if ((puVar5 != (uint *)0x0) && (local_88 != 0)) {
      puVar1 = (undefined4 *)local_f0[5];
      puVar2 = (undefined4 *)local_ec[5];
      local_e4 = puVar1;
      iVar9 = ftol();
      puVar10 = (undefined4 *)(iVar9 + (int)puVar2);
      if (puVar10 == puVar2) {
        puVar10 = puVar1;
      }
      piVar4 = (int *)construct_bitmap_surface_context
                                (local_68,*puVar5,(int)(puVar5[1] << 3) >> 3,(int)(puVar5 + 2),0);
      piVar3 = local_34;
      for (iVar9 = 0xd; iVar9 != 0; iVar9 = iVar9 + -1) {
        *piVar3 = *piVar4;
        piVar4 = piVar4 + 1;
        piVar3 = piVar3 + 1;
      }
      iVar9 = (int)(puVar5[1] << 3) >> 3;
      set_bitmap_surface_clip_rect
                (local_34,local_ec[4],(iVar9 - (int)puVar10) - local_ec[7],local_ec[6] + local_ec[4]
                 ,iVar9 - (int)puVar10);
      blit_bitmap_surface_context_clipped_with_palette_blend
                (local_9c,local_34,local_e8[4],
                 (uint *)(((local_9c[1] * 8 >> 3) - local_e8[5]) - local_ec[7]),(uint *)0x0);
      release_vqm_texture_cache_reference_by_name((char *)local_e0);
      piVar4 = local_9c;
      for (iVar9 = 0xd; iVar9 != 0; iVar9 = iVar9 + -1) {
        *param_1 = *piVar4;
        piVar4 = piVar4 + 1;
        param_1 = param_1 + 1;
      }
      return;
    }
  }
  piVar4 = (int *)construct_bitmap_surface_context(local_68,0,0,0,0);
  for (iVar9 = 0xd; iVar9 != 0; iVar9 = iVar9 + -1) {
    *param_1 = *piVar4;
    piVar4 = piVar4 + 1;
    param_1 = param_1 + 1;
  }
  return;
}


