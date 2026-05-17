/*
 * Program: i76.exe
 * Function: render_display_mode1_bitmap_overlay
 * Entry: 004621e0
 * Signature: undefined __cdecl render_display_mode1_bitmap_overlay(int param_1)
 */


/* [cgpt i76.exe runtime loop refinement v23; confidence=MEDIUM_HIGH] Display-mode-1 software
   bitmap/overlay path. Loads or reuses background/overlay surface and blits via bitmap surface
   contexts. */

void __cdecl render_display_mode1_bitmap_overlay(int param_1)

{
  char cVar1;
  ushort uVar2;
  undefined1 uVar3;
  undefined2 uVar4;
  bool bVar5;
  int iVar6;
  uint *puVar7;
  int *piVar8;
  undefined3 extraout_var;
  char cVar9;
  short sVar10;
  int iVar11;
  uint uVar12;
  int iVar13;
  short *psVar14;
  short *psVar15;
  short *psVar16;
  int iVar17;
  short *psVar18;
  int *piVar19;
  undefined4 *puVar20;
  uint local_b8;
  int local_b4;
  char *local_b0;
  int local_ac;
  short *local_a8;
  int local_9c [5];
  void *local_88;
  int local_68 [5];
  short *local_54;
  int local_34 [13];
  
  if ((g_runtime_display_input_mode == 1) && (DAT_0054b67c != 0)) {
    iVar13 = *(int *)(param_1 + 0x3c);
    iVar6 = (*(int *)(iVar13 + 0x24) - *(int *)(iVar13 + 0x1c)) + 1;
    local_b4 = (*(int *)(iVar13 + 0x28) - *(int *)(iVar13 + 0x20)) + 1;
    if ((iVar6 != DAT_0054b648) || (local_b4 != DAT_0054b64c * 8 >> 3)) {
      release_bitmap_surface_context(&DAT_0054b648);
      iVar13 = (&DAT_004f9e14)[DAT_005dd360 * 7];
      uVar12 = (&DAT_004f9e18)[DAT_005dd360 * 7];
      puVar7 = open_resource_file_into_memory(&DAT_004f7c98 + DAT_005dd360 * 0xd);
      piVar8 = (int *)construct_bitmap_surface_context(local_9c,iVar13,uVar12,0,0);
      piVar19 = local_68;
      for (iVar11 = 0xd; iVar11 != 0; iVar11 = iVar11 + -1) {
        *piVar19 = *piVar8;
        piVar8 = piVar8 + 1;
        piVar19 = piVar19 + 1;
      }
      psVar16 = (short *)(uVar12 * iVar13 + (int)local_54);
      uVar2 = (ushort)*puVar7;
      psVar15 = local_54;
      while ((uVar2 != 0 && (psVar15 < psVar16))) {
        psVar14 = (short *)(((ushort)*puVar7 & 0x7fff) + (int)psVar15);
        if (psVar16 < psVar14) {
          psVar14 = psVar16;
        }
        if (((ushort)*puVar7 & 0x8000) != 0) {
          psVar18 = psVar15;
          for (uVar12 = (uint)((int)psVar14 - (int)psVar15) >> 2; uVar12 != 0; uVar12 = uVar12 - 1)
          {
            psVar18[0] = -0x102;
            psVar18[1] = -0x102;
            psVar18 = psVar18 + 2;
          }
          for (uVar12 = (int)psVar14 - (int)psVar15 & 3; uVar12 != 0; uVar12 = uVar12 - 1) {
            *(char *)psVar18 = -2;
            psVar18 = (short *)((int)psVar18 + 1);
          }
        }
        puVar7 = (uint *)((int)puVar7 + 2);
        uVar2 = *(ushort *)puVar7;
        psVar15 = psVar14;
      }
      local_a8 = local_54;
      uVar12 = local_68[1] * 8 >> 3;
      local_b0 = (char *)0x0;
      psVar15 = local_54;
      local_b8 = uVar12;
      if (0 < (int)uVar12) {
        do {
          cVar9 = (char)*psVar15;
          sVar10 = 1;
          psVar16 = local_a8;
          if (1 < local_68[0]) {
            local_ac = local_68[0] + -1;
            psVar14 = psVar15;
            do {
              cVar1 = *(char *)((int)psVar14 + 1);
              psVar14 = (short *)((int)psVar14 + 1);
              if (cVar1 == cVar9) {
                sVar10 = sVar10 + 1;
              }
              else {
                if (sVar10 != 0) {
                  if (cVar9 != -2) {
                    sVar10 = -sVar10;
                  }
                  *psVar16 = sVar10;
                  psVar16 = psVar16 + 1;
                }
                sVar10 = 1;
                cVar9 = cVar1;
              }
              local_ac = local_ac + -1;
            } while (local_ac != 0);
          }
          if (sVar10 != 0) {
            if (cVar9 != -2) {
              sVar10 = -sVar10;
            }
            *psVar16 = sVar10;
            psVar16 = psVar16 + 1;
          }
          local_b0 = (char *)((int)psVar16 + ((int)local_b0 - (int)local_a8));
          local_a8 = (short *)(local_b0 + (int)local_54);
          local_b8 = local_b8 - 1;
          psVar15 = (short *)((int)psVar15 + local_68[0]);
        } while (local_b8 != 0);
      }
      piVar8 = (int *)construct_bitmap_surface_context(local_34,(int)local_b0,1,0,0);
      piVar19 = local_9c;
      for (iVar13 = 0xd; iVar13 != 0; iVar13 = iVar13 + -1) {
        *piVar19 = *piVar8;
        piVar8 = piVar8 + 1;
        piVar19 = piVar19 + 1;
      }
      local_9c[1] = local_9c[1] ^ (local_9c[1] ^ uVar12) & 0x1fffffff;
      local_9c[0] = local_68[0];
      set_bitmap_surface_clip_rect(local_9c,0,0,local_68[0],uVar12);
      memmove(local_88,local_54,(size_t)local_b0);
      piVar8 = local_9c;
      piVar19 = &DAT_0054b648;
      for (iVar13 = 0xd; iVar13 != 0; iVar13 = iVar13 + -1) {
        *piVar19 = *piVar8;
        piVar8 = piVar8 + 1;
        piVar19 = piVar19 + 1;
      }
      release_bitmap_surface_context(local_68);
      release_resource_file_reference(&DAT_004f7c98 + DAT_005dd360 * 0xd);
    }
    psVar15 = DAT_0054b65c;
    iVar13 = (*(int **)(param_1 + 0x3c))[5];
    iVar11 = **(int **)(param_1 + 0x3c);
    bVar5 = get_global_heap_handle();
    uVar4 = DAT_0060865e;
    if (CONCAT31(extraout_var,bVar5) == 0) {
      if (0 < local_b4) {
        do {
          iVar17 = 0;
          do {
            sVar10 = *psVar15;
            psVar15 = psVar15 + 1;
            if (0 < sVar10) {
              puVar20 = (undefined4 *)(iVar13 + iVar17);
              for (uVar12 = (uint)(int)sVar10 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
                *puVar20 = 0xffffffff;
                puVar20 = puVar20 + 1;
              }
              for (uVar12 = (int)sVar10 & 3; uVar12 != 0; uVar12 = uVar12 - 1) {
                *(undefined1 *)puVar20 = 0xff;
                puVar20 = (undefined4 *)((int)puVar20 + 1);
              }
              sVar10 = -sVar10;
            }
            iVar17 = iVar17 - sVar10;
          } while (iVar17 < iVar6);
          iVar13 = iVar13 + iVar11;
          local_b4 = local_b4 + -1;
        } while (local_b4 != 0);
      }
    }
    else {
      local_ac = local_b4;
      if (0 < local_b4) {
        do {
          iVar17 = 0;
          do {
            sVar10 = *psVar15;
            psVar15 = psVar15 + 1;
            if (0 < sVar10) {
              uVar3 = (undefined1)uVar4;
              puVar20 = (undefined4 *)(iVar13 + iVar17 * 2);
              for (uVar12 = (uint)((int)sVar10 << 1) >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
                *puVar20 = CONCAT22(CONCAT11(uVar3,uVar3),CONCAT11(uVar3,uVar3));
                puVar20 = puVar20 + 1;
              }
              for (uVar12 = (int)sVar10 << 1 & 3; uVar12 != 0; uVar12 = uVar12 - 1) {
                *(undefined1 *)puVar20 = uVar3;
                puVar20 = (undefined4 *)((int)puVar20 + 1);
              }
              sVar10 = -sVar10;
            }
            iVar17 = iVar17 - sVar10;
          } while (iVar17 < iVar6);
          local_ac = local_ac + -1;
          iVar13 = iVar13 + iVar11 * 2;
        } while (local_ac != 0);
        return;
      }
    }
  }
  return;
}


