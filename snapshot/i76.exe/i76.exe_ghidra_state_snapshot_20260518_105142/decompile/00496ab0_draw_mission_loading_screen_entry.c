/*
 * Program: i76.exe
 * Function: draw_mission_loading_screen_entry
 * Entry: 00496ab0
 * Signature: undefined __cdecl draw_mission_loading_screen_entry(uint * param_1, int param_2)
 */


/* [cgpt i76.exe mission/world/effects rename v16; confidence=HIGH] Draws a single loading-screen
   entry, including optional border, label, tick/progress marks, string value, or numeric value. */

void __cdecl draw_mission_loading_screen_entry(uint *param_1,int param_2)

{
  byte bVar1;
  byte *lpString;
  uint uVar2;
  uint uVar3;
  HGDIOBJ pvVar4;
  int iVar5;
  uint *puVar6;
  uint *puVar7;
  byte *pbVar8;
  int iVar9;
  uint *puVar10;
  tagSIZE local_28;
  uint local_20;
  uint *local_1c;
  uint local_18;
  uint local_14;
  uint local_10 [4];
  
  puVar10 = param_1;
  uVar3 = *param_1 & 0x3ff;
  if (uVar3 < 9) {
    if (uVar3 != 8) {
      pvVar4 = g_loading_font_primary;
      if (((uVar3 == 1) || (pvVar4 = g_loading_font_secondary, uVar3 == 2)) || (uVar3 == 4))
      goto LAB_00496b38;
LAB_00496b1c:
      pvVar4 = (HGDIOBJ)0x0;
      goto LAB_00496b38;
    }
  }
  else if (uVar3 < 0x21) {
    pvVar4 = g_loading_font_large;
    if (uVar3 == 0x20) goto LAB_00496b38;
    if (uVar3 != 0x10) {
      pvVar4 = (HGDIOBJ)0x0;
      goto LAB_00496b38;
    }
  }
  else {
    pvVar4 = g_loading_font_large_alt;
    if (uVar3 < 0x81) {
      if (uVar3 == 0x80) goto LAB_00496b38;
      if (uVar3 != 0x40) {
        pvVar4 = (HGDIOBJ)0x0;
        goto LAB_00496b38;
      }
    }
    else {
      if (uVar3 == 0x100) goto LAB_00496b38;
      if (uVar3 != 0x200) goto LAB_00496b1c;
    }
  }
  pvVar4 = g_loading_font_progress;
  if ((*param_1 & 0x400) != 0) {
    pvVar4 = g_loading_font_progress_alt;
  }
LAB_00496b38:
  if (pvVar4 != (HGDIOBJ)0x0) {
    SelectObject(g_loading_screen_hdc,pvVar4);
  }
  local_20 = param_1[7];
  local_1c = (uint *)param_1[8];
  local_18 = param_1[9];
  local_14 = param_1[10];
  if ((*param_1 & 0x40) != 0) {
    local_20 = local_20 + 2 + *g_loading_x1_map_texture_handle;
  }
  if (param_2 != 0) {
    Rectangle(g_loading_screen_hdc,local_20,(int)local_1c,local_18,local_14);
  }
  lpString = (byte *)param_1[1];
  if (lpString != (byte *)0x0) {
    if (g_display_mode_variant_index < 6) {
      local_20 = local_20 + 3;
      iVar5 = 0x18;
      local_1c = (uint *)((int)local_1c + 3);
    }
    else {
      local_20 = local_20 + 1;
      iVar5 = 0xb;
    }
    uVar3 = param_1[3];
    if (((uVar3 == 0xf) || (uVar3 == 0x10)) ||
       ((uVar3 == 0x11 || ((uVar3 == 0x1b || (uVar3 == 0x1d)))))) {
      uVar3 = 0xffffffff;
      pbVar8 = lpString;
      do {
        if (uVar3 == 0) break;
        uVar3 = uVar3 - 1;
        bVar1 = *pbVar8;
        pbVar8 = pbVar8 + 1;
      } while (bVar1 != 0);
      GetTextExtentPoint32A(g_loading_screen_hdc,(LPCSTR)lpString,~uVar3 - 1,&local_28);
      local_20 = local_20 + (int)((local_18 - local_20) - local_28.cx) / 2;
    }
    draw_wrapped_text_to_hdc_with_optional_underline
              (g_loading_screen_hdc,(int *)&local_20,lpString,iVar5,0,(int *)0x0);
  }
  local_20 = param_1[0xb];
  local_1c = (uint *)param_1[0xc];
  local_18 = param_1[0xd];
  local_14 = param_1[0xe];
  uVar3 = *param_1;
  puVar7 = (uint *)0x0;
  if (((uVar3 & 0x60) == 0) || (param_1[6] == 0)) {
    if ((uVar3 & 0x180) == 0) {
      if (param_1[5] != 0) {
        puVar7 = *(uint **)(param_1[5] + param_1[6] * 4);
      }
    }
    else {
      uVar2 = param_1[6];
      if ((uVar2 == 0) || ((((uVar3 & 0x1000) != 0 && (uVar2 == 1)) && ((uVar3 & 0x4000) == 0)))) {
        param_1 = (uint *)StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,
                                        &PTR_DAT_004fd8cc);
      }
      else {
        param_1 = local_10;
        sprintf((char *)local_10,s__d_00_004fd8d0,uVar2);
      }
      puVar7 = param_1;
      if ((*puVar10 & 0x100) == 0) {
        if (g_display_mode_variant_index < 6) {
          iVar5 = puVar10[7] + 5;
          puVar6 = (uint *)(puVar10[8] + 0x1c);
          param_2 = 0x11;
        }
        else {
          iVar5 = puVar10[7] + 1;
          puVar6 = (uint *)(puVar10[8] + 0xd);
          param_2 = 7;
        }
        iVar9 = 0;
        if (0 < (int)puVar10[6]) {
          do {
            blit_bitmap_surface_context_clipped_with_palette_blend
                      (&DAT_00654aa0,&DAT_00654ad4,iVar5,puVar6,(uint *)0x1);
            iVar9 = iVar9 + 1;
            iVar5 = iVar5 + param_2;
          } while (iVar9 < (int)puVar10[6]);
        }
      }
    }
  }
  else {
    if ((uVar3 & 0x40) != 0) {
      if (g_display_mode_variant_index < 6) {
        iVar5 = local_20 + 5;
        local_1c = (uint *)((int)local_1c + 3);
      }
      else {
        iVar5 = local_20 + 2;
        local_1c = (uint *)((int)local_1c + 1);
      }
      local_20 = iVar5 + *g_loading_x1_map_texture_handle;
    }
    blit_bitmap_surface_context_clipped_with_palette_blend
              (&DAT_00654aa0,&DAT_00654ad4,local_20,local_1c,(uint *)0x1);
  }
  if (puVar7 != (uint *)0x0) {
    uVar3 = 0xffffffff;
    puVar10 = puVar7;
    do {
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      uVar2 = *puVar10;
      puVar10 = (uint *)((int)puVar10 + 1);
    } while ((char)uVar2 != '\0');
    GetTextExtentPoint32A(g_loading_screen_hdc,(LPCSTR)puVar7,~uVar3 - 1,&local_28);
    if ((int)(local_18 - local_20) < local_28.cx) {
      local_20 = local_18 - local_28.cx;
    }
    uVar3 = 0xffffffff;
    puVar10 = puVar7;
    do {
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      uVar2 = *puVar10;
      puVar10 = (uint *)((int)puVar10 + 1);
    } while ((char)uVar2 != '\0');
    TextOutA(g_loading_screen_hdc,local_20,(int)local_1c,(LPCSTR)puVar7,~uVar3 - 1);
  }
  return;
}


