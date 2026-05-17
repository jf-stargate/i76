/*
 * Program: i76.exe
 * Function: create_or_restore_video_memory_texture_surface
 * Entry: 0042ede0
 * Signature: undefined4 __cdecl create_or_restore_video_memory_texture_surface(int * param_1)
 */


/* WARNING: Type propagation algorithm not settling */
/* cgpt rename v3: Creates/restores DirectDraw texture surfaces for a bitmap/texture record, builds
   backing bitmap contexts, and logs dimensions on failure/debug. */

undefined4 __cdecl create_or_restore_video_memory_texture_surface(int *param_1)

{
  ushort uVar1;
  int iVar2;
  undefined2 uVar3;
  ushort *puVar4;
  int iVar5;
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  int *piVar6;
  uint uVar7;
  byte *pbVar8;
  uint uVar9;
  int iVar10;
  int *unaff_EBX;
  int *piVar11;
  uint uVar12;
  undefined4 *puVar13;
  int iVar14;
  uint uVar15;
  uint *puVar16;
  undefined4 *puVar17;
  int *piVar18;
  int unaff_retaddr;
  int local_350;
  int *local_34c;
  int *local_348;
  int *local_344;
  int *local_340;
  int *local_33c;
  int *local_338;
  undefined4 *puStack_334;
  int *local_330;
  uint local_32c;
  undefined4 *local_328;
  uint local_324;
  int *piStack_320;
  int *local_31c;
  undefined4 uStack_318;
  int iStack_314;
  int iStack_310;
  uint auStack_30c [3];
  undefined4 *puStack_300;
  int *piStack_2fc;
  int iStack_2e8;
  undefined4 uStack_2c4;
  byte abStack_2c0 [24];
  int iStack_2a8;
  undefined4 uStack_2a4;
  int aiStack_2a0 [5];
  byte *pbStack_28c;
  int iStack_284;
  int iStack_280;
  int iStack_27c;
  int iStack_278;
  int aiStack_26c [5];
  int *piStack_258;
  int iStack_250;
  int iStack_24c;
  int iStack_248;
  int iStack_244;
  int aiStack_238 [14];
  int local_200 [126];
  int iStack_8;
  undefined2 local_2;
  
  piVar11 = DAT_006080b8;
  uVar7 = 0;
  local_324 = param_1[1];
  local_31c = (int *)*param_1;
  local_340 = (int *)0x0;
  local_330 = (int *)(local_324 & 0x1ff);
  local_344 = (int *)0x0;
  local_328 = (undefined4 *)(local_324 >> 9 & 0x1ff);
  local_338 = (int *)0x0;
  local_32c = 0;
  if ((local_31c[1] & 0x80000000U) == 0) {
    piVar6 = (int *)0x0;
  }
  else {
    piVar6 = (int *)((local_31c[1] * 8 >> 3) * *local_31c + 8 + (int)local_31c);
  }
  if ((local_324 >> 0x12 & 3) == 2) {
    local_348 = local_200;
    uVar15 = 0;
    uVar12 = 0;
    local_34c = (int *)0x10;
    do {
      local_33c = (int *)(uVar7 / 0xf & DAT_005fffa0);
      uVar9 = uVar12 / 0xf;
      uVar12 = uVar12 + DAT_005fffa4;
      *(ushort *)local_348 =
           ((ushort)uVar9 & (ushort)DAT_005fffa4) +
           ((ushort)(uVar15 / 0xf) & (ushort)DAT_005fffa8) + (short)DAT_005fffac + (short)local_33c;
      uVar7 = uVar7 + DAT_005fffa0;
      uVar15 = uVar15 + DAT_005fffa8;
      local_348 = (int *)((int)local_348 + 2);
      local_34c = (int *)((int)local_34c + -1);
    } while (local_34c != (int *)0x0);
  }
  else if (piVar6 != (int *)0x0) {
    local_2 = 0;
    if (DAT_00608660 == 0) {
      iVar5 = *piVar6;
      piVar18 = local_200;
      for (uVar7 = (uint)(iVar5 << 1) >> 2; piVar6 = piVar6 + 1, uVar7 != 0; uVar7 = uVar7 - 1) {
        *piVar18 = *piVar6;
        piVar18 = piVar18 + 1;
      }
      for (uVar7 = iVar5 << 1 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
        *(char *)piVar18 = (char)*piVar6;
        piVar6 = (int *)((int)piVar6 + 1);
        piVar18 = (int *)((int)piVar18 + 1);
      }
    }
    else {
      iVar5 = *piVar6;
      if (0 < iVar5) {
        puVar4 = (ushort *)(piVar6 + 1);
        piVar6 = local_200;
        do {
          uVar1 = *puVar4;
          puVar4 = puVar4 + 1;
          iVar5 = iVar5 + -1;
          *(undefined2 *)piVar6 = *(undefined2 *)(DAT_00608660 + (uint)uVar1 * 2);
          piVar6 = (int *)((int)piVar6 + 2);
        } while (iVar5 != 0);
      }
    }
  }
  if (((DAT_005280d4 != 0) && ((local_324 & 0xc0000) != 0)) && (param_1[4] != 0)) {
    DAT_0052b914 = DAT_0052b914 + (int)local_328 * (int)local_330 * 2;
    (**(code **)(*(int *)param_1[6] + 0x1c))((int *)param_1[6]);
    (**(code **)(*(int *)param_1[6] + 8))((int *)param_1[6]);
    (**(code **)(*(int *)param_1[5] + 8))((int *)param_1[5]);
    param_1[4] = 0;
    param_1[6] = 0;
    param_1[5] = 0;
  }
  if (param_1[4] == 0) {
    puVar16 = auStack_30c;
    for (iVar5 = 0x1b; puVar16 = (uint *)((int)puVar16 + 4), iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar16 = 0;
    }
    piStack_2fc = local_330;
    auStack_30c[1] = 0x6c;
    auStack_30c[2] = 0x1007;
    aiStack_2a0[0] = 0x4005000;
    puStack_300 = local_328;
    puVar13 = &DAT_005fff90;
    pbVar8 = abStack_2c0;
    for (iVar5 = 8; iVar5 != 0; iVar5 = iVar5 + -1) {
      *(undefined4 *)pbVar8 = *puVar13;
      puVar13 = puVar13 + 1;
      pbVar8 = pbVar8 + 4;
    }
    iVar5 = (**(code **)(*piVar11 + 0x18))(piVar11,auStack_30c + 1,&local_340,0);
  }
  else {
    local_340 = (int *)param_1[5];
    local_338 = (int *)param_1[6];
    iVar5 = (**(code **)(*local_338 + 0x1c))(local_338);
  }
  if (iVar5 == 0) {
    puVar16 = auStack_30c;
    for (iVar5 = 0x1b; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar16 = 0;
      puVar16 = puVar16 + 1;
    }
    auStack_30c[0] = 0x6c;
    auStack_30c[1] = 0x1007;
    uStack_2a4 = 0x1800;
    puVar13 = &DAT_005fff90;
    puVar17 = &uStack_2c4;
    for (iVar5 = 8; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar17 = *puVar13;
      puVar13 = puVar13 + 1;
      puVar17 = puVar17 + 1;
    }
    auStack_30c[2] = local_32c;
    puStack_300 = puStack_334;
    iVar5 = (**(code **)(*piVar11 + 0x18))(piVar11,auStack_30c,&local_348,0);
    if (iVar5 == 0) {
      if ((abStack_2c0[0] & 0x20) == 0) {
        if ((abStack_2c0[0] & 0x40) == 0) goto LAB_0042f105;
      }
      else if (((*unaff_EBX == 0) &&
               (iVar5 = (**(code **)(*local_344 + 0x7c))(local_344,DAT_006080cc), iVar5 != 0)) ||
              (iVar5 = (**(code **)(*local_348 + 0x7c))(local_348,DAT_006080cc), iVar5 != 0))
      goto LAB_0042f105;
      if (((param_1[1] & 0xc0000U) == 0x40000) && (iStack_2a8 == 0)) {
        uVar3 = get_current_display_transparent_palette_index();
        local_31c = (int *)CONCAT22(extraout_var,uVar3);
        uVar3 = get_current_display_transparent_palette_index();
        uStack_318 = CONCAT22(extraout_var_00,uVar3);
        if (((*unaff_EBX == 0) &&
            (iVar5 = (**(code **)(*local_344 + 0x74))(local_344,8,&local_31c), iVar5 != 0)) ||
           (iVar5 = (**(code **)(*local_348 + 0x74))(local_348,8,&local_31c), iVar5 != 0))
        goto LAB_0042f105;
      }
      iVar5 = (**(code **)(*local_348 + 100))(local_348,0,auStack_30c,1,0);
      puVar13 = puStack_300;
      if (iVar5 == 0) {
        local_340 = DAT_005fffb4;
        piVar11 = piStack_2fc;
        if (DAT_005fffb4 == (int *)0x0) {
          piVar11 = (int *)((int)piStack_2fc >> 1);
        }
        piVar6 = (int *)construct_bitmap_surface_context
                                  (aiStack_2a0,*piStack_320,(piStack_320[1] << 3) >> 3,
                                   (int)(piStack_320 + 2),0);
        piVar18 = aiStack_2a0;
        for (iVar5 = 0xd; iVar5 != 0; iVar5 = iVar5 + -1) {
          *piVar18 = *piVar6;
          piVar6 = piVar6 + 1;
          piVar18 = piVar18 + 1;
        }
        piVar11 = (int *)construct_bitmap_surface_context
                                   (aiStack_238,(int)piVar11,auStack_30c[2],iStack_2e8,
                                    (uint)(local_340 == (int *)0x0));
        piVar6 = aiStack_26c;
        for (iVar5 = 0xd; iVar5 != 0; iVar5 = iVar5 + -1) {
          *piVar6 = *piVar11;
          piVar11 = piVar11 + 1;
          piVar6 = piVar6 + 1;
        }
        set_bitmap_surface_clip_rect(aiStack_26c,0,0,(int)puVar13,auStack_30c[2]);
        iVar5 = (iStack_27c - iStack_284) + 1;
        piVar11 = (int *)((iStack_278 - iStack_280) + 1);
        iVar14 = (iStack_248 - iStack_250) + 1;
        local_34c = piStack_258;
        local_31c = (int *)((iStack_244 - iStack_24c) + 1);
        if ((iVar5 == iVar14) && (piVar11 == local_31c)) {
          piVar6 = local_338;
          if (0 < (int)piVar11) {
            do {
              local_34c = piVar11;
              iVar14 = 0;
              piVar11 = piStack_258;
              if (0 < iVar5) {
                do {
                  pbVar8 = pbStack_28c + iVar14;
                  iVar14 = iVar14 + 1;
                  *(undefined2 *)piVar11 = *(undefined2 *)((int)param_1 + (uint)*pbVar8 * 2 + 0x10);
                  piVar11 = (int *)((int)piVar11 + 2);
                } while (iVar14 < iVar5);
              }
              pbStack_28c = pbStack_28c + aiStack_2a0[0];
              piStack_258 = (int *)((int)piStack_258 + aiStack_26c[0] * 2);
              piVar11 = (int *)((int)local_34c + -1);
            } while ((int *)((int)local_34c + -1) != (int *)0x0);
            local_34c = (int *)0x0;
          }
        }
        else {
          local_324 = iVar5 / iVar14;
          piVar6 = (int *)(iVar5 % iVar14);
          iVar5 = 0;
          local_328 = (undefined4 *)((int)piVar11 % (int)local_31c);
          iStack_314 = ((int)piVar11 / (int)local_31c) * aiStack_2a0[0];
          if (piVar6 == (int *)0x0) {
            local_338 = local_31c;
            if (0 < (int)local_31c) {
              do {
                piVar11 = piStack_258;
                pbVar8 = pbStack_28c;
                local_350 = iVar14;
                if (0 < iVar14) {
                  do {
                    *(undefined2 *)piVar11 =
                         *(undefined2 *)((int)param_1 + (uint)*pbVar8 * 2 + 0x10);
                    local_350 = local_350 + -1;
                    piVar11 = (int *)((int)piVar11 + 2);
                    pbVar8 = pbVar8 + local_324;
                  } while (local_350 != 0);
                }
                pbStack_28c = pbStack_28c + iStack_314;
                piStack_258 = (int *)((int)piStack_258 + aiStack_26c[0] * 2);
                iVar5 = iVar5 + (int)local_328;
                if ((int)local_31c <= iVar5) {
                  iVar5 = iVar5 - (int)local_31c;
                  pbStack_28c = pbStack_28c + aiStack_2a0[0];
                }
                local_338 = (int *)((int)local_338 + -1);
              } while (local_338 != (int *)0x0);
              local_34c = piStack_258;
              piVar6 = (int *)0x0;
            }
          }
          else {
            piVar11 = local_31c;
            if (0 < (int)local_31c) {
              do {
                local_340 = piVar11;
                iVar10 = 0;
                pbVar8 = pbStack_28c;
                piVar11 = piStack_258;
                iVar2 = iVar14;
                if (0 < iVar14) {
                  do {
                    iStack_310 = iVar2;
                    *(undefined2 *)piVar11 =
                         *(undefined2 *)((int)param_1 + (uint)*pbVar8 * 2 + 0x10);
                    pbVar8 = pbVar8 + local_324;
                    iVar10 = iVar10 + (int)piVar6;
                    if (iVar14 <= iVar10) {
                      pbVar8 = pbVar8 + 1;
                      iVar10 = iVar10 - iVar14;
                    }
                    piVar11 = (int *)((int)piVar11 + 2);
                    iVar2 = iStack_310 + -1;
                  } while (iStack_310 + -1 != 0);
                  iStack_310 = 0;
                }
                pbStack_28c = pbStack_28c + iStack_314;
                piStack_258 = (int *)((int)piStack_258 + aiStack_26c[0] * 2);
                iVar5 = iVar5 + (int)local_328;
                if ((int)local_31c <= iVar5) {
                  iVar5 = iVar5 - (int)local_31c;
                  pbStack_28c = pbStack_28c + aiStack_2a0[0];
                }
                local_340 = (int *)((int)local_340 + -1);
                local_34c = piStack_258;
                piVar11 = local_340;
              } while (local_340 != (int *)0x0);
            }
          }
        }
        local_338 = piVar6;
        (**(code **)(*local_348 + 0x80))(local_348,0);
        unaff_EBX = (int *)(unaff_retaddr + 0x10);
        if ((((*(int *)(unaff_retaddr + 0x10) != 0) ||
             (iVar5 = (**(code **)*local_344)(local_344,&DAT_004bce78,&local_33c), iVar5 == 0)) &&
            (iVar5 = (**(code **)*local_348)(local_348,&DAT_004bce78,&local_330), iVar5 == 0)) &&
           (iVar5 = (**(code **)(*local_33c + 0x18))(local_33c,local_330), iVar5 == 0)) {
          if (*unaff_EBX == 0) {
            DAT_0052b914 = DAT_0052b914 + local_32c * (int)puStack_334 * -2;
            (**(code **)(*local_33c + 0x10))(local_33c,DAT_005fde48,unaff_EBX);
          }
          (**(code **)(*local_330 + 8))(local_330);
          (**(code **)(*local_34c + 8))(local_34c);
          puVar13 = local_328;
          *(int **)(iStack_8 + 0x18) = local_344;
          *(int **)(iStack_8 + 0x14) = local_34c;
          if ((g_resource_debug_log_file != 0) &&
             ((iVar5 = find_vqm_texture_cache_record_by_bitmap_id((int)local_328), iVar5 != 0 ||
              (((byte)DAT_00504c08 & 3) == 3)))) {
            debug_fprintf_wrapper
                      (*(char *)((int)&PTR_DAT_004edfa8 + (*(uint *)(iStack_8 + 4) >> 0x12 & 3)));
            fprintf((FILE *)g_resource_debug_log_file,s__s__dx_d_004edf9c,iVar5,*puVar13,
                    (int)(puVar13[1] << 3) >> 3);
          }
          return 1;
        }
      }
    }
  }
LAB_0042f105:
  if (local_330 != (int *)0x0) {
    (**(code **)(*local_330 + 8))(local_330);
  }
  if (local_33c != (int *)0x0) {
    (**(code **)(*local_33c + 8))(local_33c);
  }
  *(undefined4 *)(unaff_retaddr + 0x18) = 0;
  if (local_344 != (int *)0x0) {
    (**(code **)(*local_344 + 8))(local_344);
  }
  *(undefined4 *)(unaff_retaddr + 0x14) = 0;
  if (local_348 != (int *)0x0) {
    (**(code **)(*local_348 + 8))(local_348);
  }
  *unaff_EBX = 0;
  return 0;
}


