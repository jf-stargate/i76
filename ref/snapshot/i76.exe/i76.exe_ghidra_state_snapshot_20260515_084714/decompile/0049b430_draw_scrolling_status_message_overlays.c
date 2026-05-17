/*
 * Program: i76.exe
 * Function: draw_scrolling_status_message_overlays
 * Entry: 0049b430
 * Signature: undefined __stdcall draw_scrolling_status_message_overlays(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe runtime loop refinement v23; confidence=HIGH] Draws animated/scrolled runtime
   status message overlays. */

void draw_scrolling_status_message_overlays(void)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  undefined1 uVar5;
  undefined3 extraout_var;
  uint *puVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  float10 fVar12;
  uint *puVar13;
  uint local_30;
  int local_2c;
  
  uVar4 = DAT_005dcec0;
  iVar1 = DAT_005dcec4 * 8;
  for (puVar3 = g_scrolling_status_overlay_list; puVar3 != (undefined4 *)0x0;
      puVar3 = (undefined4 *)*puVar3) {
    iVar2 = puVar3[2];
    if ((*(uint *)(iVar2 + 0x94) & 2) != 0) {
      if (((*(uint *)(iVar2 + 0x94) & 0x80000000) != 0) ||
         (fVar12 = get_multiplayer_or_runtime_seconds(), (float10)*(float *)(iVar2 + 0x90) < fVar12)
         ) {
        uVar8 = *(uint *)(iVar2 + 0x58);
        if (uVar8 != 0) {
          if ((*(byte *)(iVar2 + 0x94) & 4) == 0) {
            uVar8 = uVar8 - 1;
          }
          else {
            uVar8 = uVar8 - 4;
          }
          *(uint *)(iVar2 + 0x58) = uVar8;
          if ((uVar8 & 3) == 0) {
            *(uint *)(iVar2 + 0x50) = (*(int *)(iVar2 + 0x50) + 1U) % (*(int *)(iVar2 + 0x44) + 5U);
          }
        }
        iVar7 = *(int *)(iVar2 + 0x4c);
        fill_bitmap_surface_context((int *)(iVar2 + 0x10),0xff);
        if (*(int *)(iVar2 + 100) == -1) {
          uVar5 = convert_rgb_floats_to_nearest_palette_index();
          *(uint *)(iVar2 + 100) = CONCAT31(extraout_var,uVar5);
        }
        dib_surface_context_setter_helper_004766e0((int)DAT_00504c0c,*(int *)(iVar2 + 100));
        dib_surface_context_flag_helper_00476730((int)DAT_00504c0c,-1);
        iVar9 = *(int *)(iVar2 + 0x44);
        local_30 = 0;
        local_2c = 0;
        if (iVar9 != -1) {
          do {
            uVar10 = (local_30 + *(int *)(iVar2 + 0x50)) % (iVar9 + 5U);
            if ((*(byte *)(iVar2 + 0x94) & 1) != 0) {
              iVar9 = *(int *)(iVar2 + 0x5c);
              iVar11 = uVar10 * 0x54;
              fVar12 = get_multiplayer_or_runtime_seconds();
              if (fVar12 <= (float10)*(float *)(iVar11 + 0x50 + iVar9)) {
                if (*(int *)(iVar2 + 0x90) == -0x40800000) {
                  *(undefined4 *)(iVar2 + 0x90) =
                       *(undefined4 *)(iVar11 + 0x50 + *(int *)(iVar2 + 0x5c));
                }
              }
              else {
                *(undefined4 *)(iVar11 + 0x50 + *(int *)(iVar2 + 0x5c)) = 0xbf800000;
                *(undefined1 *)(iVar11 + *(int *)(iVar2 + 0x5c)) = DAT_00504c28;
              }
            }
            if (*(int *)(iVar2 + 0x68) == -1) {
              dib_surface_context_release_helper_004768d0();
            }
            else {
              dib_surface_context_cleanup_helper_00476890(*(int *)(iVar2 + 0x68),iVar2 + 0x6c);
            }
            update_palette_dib_surface_pixels_helper_00477300
                      (DAT_00504c0c,(int *)(iVar2 + 0x10),0,local_2c - ((-uVar8 & 3) * iVar7 >> 2),
                       (ushort *)(*(int *)(iVar2 + 0x5c) + uVar10 * 0x54));
            if (*(int *)(iVar2 + 0x68) != -1) {
              dib_surface_context_release_helper_004768d0();
            }
            iVar9 = *(int *)(iVar2 + 0x44);
            local_30 = local_30 + 1;
            local_2c = local_2c + *(int *)(iVar2 + 0x4c);
          } while (local_30 < iVar9 + 1U);
        }
        if (*(int *)(iVar2 + 0x58) == 0) {
          *(uint *)(iVar2 + 0x94) = *(uint *)(iVar2 + 0x94) & 0x7fffffff;
        }
      }
      puVar13 = (uint *)0x1;
      puVar6 = (uint *)ftol();
      iVar7 = ftol();
      blit_bitmap_surface_context_clipped_with_palette_blend
                (&DAT_005dcec0,(int *)(iVar2 + 0x10),iVar7,puVar6,puVar13);
    }
  }
  _DAT_005a7d84 = iVar1 >> 3;
  _DAT_005a7d8c = uVar4;
  return;
}


