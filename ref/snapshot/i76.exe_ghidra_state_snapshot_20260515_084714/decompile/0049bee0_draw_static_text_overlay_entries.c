/*
 * Program: i76.exe
 * Function: draw_static_text_overlay_entries
 * Entry: 0049bee0
 * Signature: undefined __stdcall draw_static_text_overlay_entries(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe runtime loop refinement v23; confidence=HIGH] Draws static runtime text overlay
   entries, optional underline spans, and blended surface output. */

void draw_static_text_overlay_entries(void)

{
  byte bVar1;
  short sVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined1 uVar5;
  ushort uVar6;
  undefined3 extraout_var;
  uint uVar7;
  int *piVar8;
  int iVar9;
  uint *puVar10;
  int iVar11;
  uint uVar12;
  uint *puVar13;
  int local_8;
  
  for (puVar4 = g_static_text_overlay_list; puVar4 != (undefined4 *)0x0;
      puVar4 = (undefined4 *)*puVar4) {
    iVar3 = puVar4[2];
    if ((*(uint *)(iVar3 + 0xb0) & 1) != 0) {
      if ((*(uint *)(iVar3 + 0xb0) & 0x200) != 0) {
        fill_bitmap_surface_context((int *)(iVar3 + 0x10),0xff);
        if (*(int *)(iVar3 + 0xac) == -1) {
          uVar5 = convert_rgb_floats_to_nearest_palette_index();
          *(uint *)(iVar3 + 0xac) = CONCAT31(extraout_var,uVar5);
        }
        dib_surface_context_setter_helper_004766e0((int)DAT_00504c0c,*(int *)(iVar3 + 0xac));
        dib_surface_context_flag_helper_00476730((int)DAT_00504c0c,-1);
        update_palette_dib_surface_pixels_helper_00477300
                  (DAT_00504c0c,(int *)(iVar3 + 0x10),0,0,(ushort *)(iVar3 + 0x44));
        if ((*(uint *)(iVar3 + 0xb0) & 0x100) != 0) {
          uVar12 = 0;
          local_8 = 0;
          if (*(int *)(iVar3 + 0xa4) != 0) {
            do {
              bVar1 = *(byte *)(uVar12 + 0x44 + iVar3);
              uVar6 = (ushort)(char)bVar1;
              if ((*DAT_00504c0c & 0x100) == 0) {
                uVar7 = uVar6 & 0xff;
                if ((int)DAT_00504c0c[1] < (int)uVar7) {
                  uVar7 = 0x2a;
                }
                piVar8 = (int *)DAT_00504c0c[uVar7 + 0x83];
              }
              else {
                sVar2 = *(short *)(DAT_006547e4 + (uVar6 & 0xffff00ff) * 2);
                if (sVar2 == 0) {
                  uVar6 = (ushort)bVar1;
                }
                else {
                  uVar6 = sVar2 + (uVar6 >> 8);
                }
                piVar8 = (int *)DAT_00504c0c[uVar6 + 0x83];
              }
              uVar12 = uVar12 + 1;
              local_8 = local_8 + 2 + *piVar8;
            } while (uVar12 < *(uint *)(iVar3 + 0xa4));
          }
          bVar1 = *(byte *)(uVar12 + 0x44 + iVar3);
          if (bVar1 == 0) {
            iVar11 = 0x77;
            if ((*DAT_00504c0c & 0x100) == 0) {
              if ((int)DAT_00504c0c[1] < 0x77) {
                iVar11 = 0x2a;
              }
              piVar8 = (int *)DAT_00504c0c[iVar11 + 0x83];
            }
            else {
              uVar6 = *(ushort *)(DAT_006547e4 + 0xee);
              if (uVar6 == 0) {
                uVar6 = 0x77;
              }
              piVar8 = (int *)DAT_00504c0c[uVar6 + 0x83];
            }
            iVar11 = *piVar8;
          }
          else {
            uVar6 = (ushort)(char)bVar1;
            if ((*DAT_00504c0c & 0x100) == 0) {
              uVar12 = uVar6 & 0xff;
              if ((int)DAT_00504c0c[1] < (int)uVar12) {
                uVar12 = 0x2a;
              }
              iVar11 = *(int *)DAT_00504c0c[uVar12 + 0x83];
            }
            else {
              sVar2 = *(short *)(DAT_006547e4 + (uVar6 & 0xffff00ff) * 2);
              if (sVar2 == 0) {
                uVar6 = (ushort)bVar1;
              }
              else {
                uVar6 = sVar2 + (uVar6 >> 8);
              }
              iVar11 = *(int *)DAT_00504c0c[uVar6 + 0x83];
            }
          }
          iVar9 = *(int *)(iVar3 + 0xc) + -1;
          draw_clipped_line_to_bitmap_surface
                    ((int *)(iVar3 + 0x10),local_8,iVar9,iVar11 + local_8,iVar9,
                     (char)*(undefined4 *)(iVar3 + 0xa8),0);
        }
        *(uint *)(iVar3 + 0xb0) = *(uint *)(iVar3 + 0xb0) & 0xfffffdff;
      }
      puVar13 = (uint *)0x1;
      puVar10 = (uint *)ftol();
      iVar11 = ftol();
      blit_bitmap_surface_context_clipped_with_palette_blend
                (&DAT_005dcec0,(int *)(iVar3 + 0x10),iVar11,puVar10,puVar13);
    }
  }
  return;
}


