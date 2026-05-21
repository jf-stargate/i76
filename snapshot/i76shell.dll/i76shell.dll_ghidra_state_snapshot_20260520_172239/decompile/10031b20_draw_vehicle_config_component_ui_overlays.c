/*
 * Program: i76shell.dll
 * Function: draw_vehicle_config_component_ui_overlays
 * Entry: 10031b20
 * Signature: undefined __cdecl draw_vehicle_config_component_ui_overlays(int * param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl draw_vehicle_config_component_ui_overlays(int *param_1)

{
  double dVar1;
  double dVar2;
  char cVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  char *pcVar7;
  char *pcVar8;
  char *pcVar9;
  bool bVar10;
  int iVar11;
  int iVar12;
  int local_80c;
  int local_808;
  undefined1 local_800 [2048];
  
  iVar6 = *param_1;
  iVar4 = atoi((char *)(iVar6 + 0x31));
  iVar4 = iVar4 + -1;
  switch(*(undefined4 *)(iVar6 + 0x1e)) {
  case 1:
  case 4:
    clear_text_rect(DAT_100cc518,0x11b,0xae,0x28,0x18);
    if (iVar4 < 0) {
      return;
    }
    if (3 < iVar4) {
      return;
    }
    if (*(int *)(*param_1 + 0x4c) == param_1[3]) {
      iVar6 = 0;
    }
    else {
      dVar2 = (double)param_1[3];
      dVar1 = (double)*(int *)(*param_1 + 0x4c) * _DAT_10041eb0;
      if (dVar1 <= dVar2) {
        iVar6 = 2;
        if (dVar1 + dVar1 <= dVar2) {
          iVar6 = 1;
        }
      }
      else {
        iVar6 = 3;
      }
    }
    draw_mw2_image_subresource_to_shell_surface
              (DAT_100cc518,(&g_shell_ui_image_record_ptr_100f4f70)[iVar4],iVar6,0x11b,0xae,0x27,
               0x17);
    return;
  case 2:
    clear_text_rect(DAT_100cc518,0x145,0x70,0x40,0x5c);
    if (iVar4 < 0) {
      return;
    }
    if (3 < iVar4) {
      return;
    }
    if (*(int *)(*param_1 + 0x4c) == param_1[3]) {
      iVar6 = 0;
    }
    else {
      dVar2 = (double)param_1[3];
      dVar1 = (double)*(int *)(*param_1 + 0x4c) * _DAT_10041eb0;
      if (dVar1 <= dVar2) {
        iVar6 = 2;
        if (dVar1 + dVar1 <= dVar2) {
          iVar6 = 1;
        }
      }
      else {
        iVar6 = 3;
      }
    }
    draw_mw2_image_subresource_to_shell_surface
              (DAT_100cc518,(&g_shell_ui_image_record_ptr_100f4f48)[iVar4],iVar6,0x145,0x70,0x40,
               0x5c);
    return;
  case 3:
    clear_text_rect(DAT_100cc518,0x133,0x12a,100,0x50);
    if (iVar4 < 0) {
      return;
    }
    if (3 < iVar4) {
      return;
    }
    if (*(int *)(*param_1 + 0x4c) == param_1[3]) {
      iVar6 = 0;
    }
    else {
      dVar2 = (double)param_1[3];
      dVar1 = (double)*(int *)(*param_1 + 0x4c) * _DAT_10041eb0;
      if (dVar1 <= dVar2) {
        iVar6 = 2;
        if (dVar1 + dVar1 <= dVar2) {
          iVar6 = 1;
        }
      }
      else {
        iVar6 = 3;
      }
    }
    draw_mw2_image_subresource_to_shell_surface
              (DAT_100cc518,(&g_shell_ui_image_record_ptr_100f4f60)[iVar4],iVar6,0x133,0x12a,99,0x4f
              );
    return;
  case 5:
    switch(DAT_10051e6c) {
    case 0:
      iVar6 = FUN_10032920(param_1);
      clear_text_rect(DAT_100cc518,0x198,0x77,0x24,0x34);
      if ((-1 < iVar4) && (iVar4 < 4)) {
        iVar4 = (&g_shell_ui_image_record_ptr_100f4f80)[iVar4];
        iVar12 = 0x34;
        iVar11 = 0x24;
        local_80c = 0x77;
        local_808 = 0x198;
        goto LAB_100328b7;
      }
      break;
    case 1:
      iVar6 = FUN_10032920(param_1);
      iVar6 = iVar6 + 4;
      clear_text_rect(DAT_100cc518,0x10e,0x77,0x24,0x34);
      if ((-1 < iVar4) && (iVar4 < 4)) {
        iVar4 = (&g_shell_ui_image_record_ptr_100f4f80)[iVar4];
        iVar12 = 0x34;
        iVar11 = 0x24;
        local_80c = 0x77;
        local_808 = 0x10e;
        goto LAB_100328b7;
      }
      break;
    case 2:
      iVar6 = FUN_10032920(param_1);
      iVar6 = iVar6 + 8;
      clear_text_rect(DAT_100cc518,0x198,0x138,0x24,0x34);
      if ((-1 < iVar4) && (iVar4 < 4)) {
        iVar4 = (&g_shell_ui_image_record_ptr_100f4f80)[iVar4];
        iVar12 = 0x34;
        iVar11 = 0x24;
        local_80c = 0x138;
        local_808 = 0x198;
        goto LAB_100328b7;
      }
      break;
    case 3:
      iVar6 = FUN_10032920(param_1);
      iVar6 = iVar6 + 0xc;
      clear_text_rect(DAT_100cc518,0x10e,0x138,0x24,0x34);
      if ((-1 < iVar4) && (iVar4 < 4)) {
        iVar4 = (&g_shell_ui_image_record_ptr_100f4f80)[iVar4];
        iVar12 = 0x34;
        iVar11 = 0x24;
        local_80c = 0x138;
        local_808 = 0x10e;
        goto LAB_100328b7;
      }
    }
    break;
  case 6:
  case 7:
  case 9:
  case 10:
  case 0xb:
    DAT_100f4f58 = 0;
    iVar4 = DAT_10051fac + DAT_10051f70;
    if (DAT_10051e6c < DAT_10051f70) {
      local_80c = *(int *)(&DAT_1004cbec + DAT_10051e6c * 8);
      local_808 = *(int *)(&DAT_1004cbe8 + DAT_10051e6c * 8);
    }
    else if (DAT_10051e6c < iVar4) {
      local_80c = *(int *)(&DAT_1004cc04 + (DAT_10051e6c - DAT_10051f70) * 8);
      local_808 = *(int *)(&DAT_1004cc00 + (DAT_10051e6c - DAT_10051f70) * 8);
    }
    else if (DAT_10051e6c <= iVar4 + DAT_10051f6c) {
      DAT_100f4f58 = 1;
      local_808 = *(int *)(&DAT_1004cc10 + (DAT_10051e6c - iVar4) * 8);
      local_80c = *(int *)(&DAT_1004cc14 + (DAT_10051e6c - iVar4) * 8);
    }
    clear_text_rect(DAT_100cc518,local_808,local_80c,0x16,0x36);
    iVar11 = g_shell_ui_image_record_ptr_100f4f98;
    iVar4 = g_shell_ui_image_record_ptr_100f4f94;
    pcVar8 = (char *)(iVar6 + 0x2e);
    iVar6 = 6;
    bVar10 = true;
    pcVar7 = pcVar8;
    pcVar9 = s_slg01_1004cc38;
    do {
      if (iVar6 == 0) break;
      iVar6 = iVar6 + -1;
      bVar10 = *pcVar7 == *pcVar9;
      pcVar7 = pcVar7 + 1;
      pcVar9 = pcVar9 + 1;
    } while (bVar10);
    if (bVar10) {
      if (*(int *)(*param_1 + 0x4c) == param_1[3]) {
        iVar6 = 0;
      }
      else {
        dVar2 = (double)param_1[3];
        dVar1 = (double)*(int *)(*param_1 + 0x4c) * _DAT_10041eb0;
        if (dVar1 <= dVar2) {
          iVar6 = 2;
          if (dVar1 + dVar1 <= dVar2) {
            iVar6 = 1;
          }
        }
        else {
          iVar6 = 3;
        }
      }
      if (DAT_100f4f58 != 0) {
        uVar5 = lock_shell_surface_for_draw((int)DAT_100cc518);
        cVar3 = (char)uVar5;
joined_r0x100324fd:
        if (cVar3 == '\0') {
          blit_mw2_image_subresource_transformed_or_masked
                    ((int *)((int)DAT_100cc518 + 0x6c),iVar4,iVar6,local_808 + 0x10,local_80c + 0x33
                     ,(int)local_800,0,-0x10000,-0x10000,0);
          unlock_shell_surface_after_draw((int)DAT_100cc518);
        }
        mark_shell_surface_dirty_rect(DAT_100cc518,local_808,local_80c,0x14,0x34);
        break;
      }
    }
    else {
      iVar6 = 6;
      bVar10 = true;
      pcVar7 = pcVar8;
      pcVar9 = s_slg02_1004cc40;
      do {
        if (iVar6 == 0) break;
        iVar6 = iVar6 + -1;
        bVar10 = *pcVar7 == *pcVar9;
        pcVar7 = pcVar7 + 1;
        pcVar9 = pcVar9 + 1;
      } while (bVar10);
      if (bVar10) {
        if (*(int *)(*param_1 + 0x4c) == param_1[3]) {
          iVar6 = 0;
        }
        else {
          dVar2 = (double)param_1[3];
          dVar1 = (double)*(int *)(*param_1 + 0x4c) * _DAT_10041eb0;
          if (dVar1 <= dVar2) {
            iVar6 = 2;
            if (dVar1 + dVar1 <= dVar2) {
              iVar6 = 1;
            }
          }
          else {
            iVar6 = 3;
          }
        }
        iVar6 = iVar6 + 4;
        if (DAT_100f4f58 != 0) {
          uVar5 = lock_shell_surface_for_draw((int)DAT_100cc518);
          cVar3 = (char)uVar5;
          goto joined_r0x100324fd;
        }
      }
      else {
        iVar6 = 6;
        bVar10 = true;
        pcVar7 = pcVar8;
        pcVar9 = s_slg03_1004cc48;
        do {
          if (iVar6 == 0) break;
          iVar6 = iVar6 + -1;
          bVar10 = *pcVar7 == *pcVar9;
          pcVar7 = pcVar7 + 1;
          pcVar9 = pcVar9 + 1;
        } while (bVar10);
        if (bVar10) {
          if (*(int *)(*param_1 + 0x4c) == param_1[3]) {
            iVar6 = 0;
          }
          else {
            dVar2 = (double)param_1[3];
            dVar1 = (double)*(int *)(*param_1 + 0x4c) * _DAT_10041eb0;
            if (dVar1 <= dVar2) {
              iVar6 = 2;
              if (dVar1 + dVar1 <= dVar2) {
                iVar6 = 1;
              }
            }
            else {
              iVar6 = 3;
            }
          }
          iVar6 = iVar6 + 8;
          if (DAT_100f4f58 != 0) {
            uVar5 = lock_shell_surface_for_draw((int)DAT_100cc518);
            cVar3 = (char)uVar5;
            goto joined_r0x100324fd;
          }
        }
        else {
          iVar6 = 6;
          bVar10 = true;
          pcVar7 = pcVar8;
          pcVar9 = s_slg04_1004cc50;
          do {
            if (iVar6 == 0) break;
            iVar6 = iVar6 + -1;
            bVar10 = *pcVar7 == *pcVar9;
            pcVar7 = pcVar7 + 1;
            pcVar9 = pcVar9 + 1;
          } while (bVar10);
          if (bVar10) {
            if (*(int *)(*param_1 + 0x4c) == param_1[3]) {
              iVar6 = 0;
            }
            else {
              dVar2 = (double)param_1[3];
              dVar1 = (double)*(int *)(*param_1 + 0x4c) * _DAT_10041eb0;
              if (dVar1 <= dVar2) {
                iVar6 = 2;
                if (dVar1 + dVar1 <= dVar2) {
                  iVar6 = 1;
                }
              }
              else {
                iVar6 = 3;
              }
            }
            iVar6 = iVar6 + 0xc;
            if (DAT_100f4f58 != 0) {
              uVar5 = lock_shell_surface_for_draw((int)DAT_100cc518);
              cVar3 = (char)uVar5;
              goto joined_r0x100324fd;
            }
          }
          else {
            iVar6 = 6;
            bVar10 = true;
            pcVar7 = pcVar8;
            pcVar9 = s_slg05_1004cc58;
            do {
              if (iVar6 == 0) break;
              iVar6 = iVar6 + -1;
              bVar10 = *pcVar7 == *pcVar9;
              pcVar7 = pcVar7 + 1;
              pcVar9 = pcVar9 + 1;
            } while (bVar10);
            if (bVar10) {
              if (*(int *)(*param_1 + 0x4c) == param_1[3]) {
                iVar6 = 0;
              }
              else {
                dVar2 = (double)param_1[3];
                dVar1 = (double)*(int *)(*param_1 + 0x4c) * _DAT_10041eb0;
                if (dVar1 <= dVar2) {
                  iVar6 = 2;
                  if (dVar1 + dVar1 <= dVar2) {
                    iVar6 = 1;
                  }
                }
                else {
                  iVar6 = 3;
                }
              }
              iVar6 = iVar6 + 0x10;
              if (DAT_100f4f58 != 0) {
                uVar5 = lock_shell_surface_for_draw((int)DAT_100cc518);
                cVar3 = (char)uVar5;
                goto joined_r0x100324fd;
              }
            }
            else {
              iVar6 = 6;
              bVar10 = true;
              pcVar7 = pcVar8;
              pcVar9 = s_slg06_1004cc60;
              do {
                if (iVar6 == 0) break;
                iVar6 = iVar6 + -1;
                bVar10 = *pcVar7 == *pcVar9;
                pcVar7 = pcVar7 + 1;
                pcVar9 = pcVar9 + 1;
              } while (bVar10);
              if (bVar10) {
                if (*(int *)(*param_1 + 0x4c) == param_1[3]) {
                  iVar6 = 0;
                }
                else {
                  dVar2 = (double)param_1[3];
                  dVar1 = (double)*(int *)(*param_1 + 0x4c) * _DAT_10041eb0;
                  if (dVar1 <= dVar2) {
                    iVar6 = 2;
                    if (dVar1 + dVar1 <= dVar2) {
                      iVar6 = 1;
                    }
                  }
                  else {
                    iVar6 = 3;
                  }
                }
                iVar6 = iVar6 + 0x14;
                if (DAT_100f4f58 != 0) {
                  uVar5 = lock_shell_surface_for_draw((int)DAT_100cc518);
                  cVar3 = (char)uVar5;
                  goto joined_r0x100324fd;
                }
              }
              else {
                iVar6 = 6;
                bVar10 = true;
                pcVar7 = pcVar8;
                pcVar9 = s_slg07_1004cc68;
                do {
                  if (iVar6 == 0) break;
                  iVar6 = iVar6 + -1;
                  bVar10 = *pcVar7 == *pcVar9;
                  pcVar7 = pcVar7 + 1;
                  pcVar9 = pcVar9 + 1;
                } while (bVar10);
                if (bVar10) {
                  if (*(int *)(*param_1 + 0x4c) == param_1[3]) {
                    iVar6 = 0;
                  }
                  else {
                    dVar2 = (double)param_1[3];
                    dVar1 = (double)*(int *)(*param_1 + 0x4c) * _DAT_10041eb0;
                    if (dVar1 <= dVar2) {
                      iVar6 = 2;
                      if (dVar1 + dVar1 <= dVar2) {
                        iVar6 = 1;
                      }
                    }
                    else {
                      iVar6 = 3;
                    }
                  }
                  iVar6 = iVar6 + 0x18;
                  if (DAT_100f4f58 != 0) {
                    uVar5 = lock_shell_surface_for_draw((int)DAT_100cc518);
                    cVar3 = (char)uVar5;
                    goto joined_r0x100324fd;
                  }
                }
                else {
                  iVar6 = 6;
                  bVar10 = true;
                  pcVar7 = pcVar8;
                  pcVar9 = s_spp01_1004cc70;
                  do {
                    if (iVar6 == 0) break;
                    iVar6 = iVar6 + -1;
                    bVar10 = *pcVar7 == *pcVar9;
                    pcVar7 = pcVar7 + 1;
                    pcVar9 = pcVar9 + 1;
                  } while (bVar10);
                  if (!bVar10) {
                    iVar6 = 6;
                    bVar10 = true;
                    pcVar7 = pcVar8;
                    pcVar9 = s_spp02_1004cc78;
                    do {
                      if (iVar6 == 0) break;
                      iVar6 = iVar6 + -1;
                      bVar10 = *pcVar7 == *pcVar9;
                      pcVar7 = pcVar7 + 1;
                      pcVar9 = pcVar9 + 1;
                    } while (bVar10);
                    if (bVar10) {
                      if (*(int *)(*param_1 + 0x4c) == param_1[3]) {
                        iVar6 = 0;
                      }
                      else {
                        dVar2 = (double)param_1[3];
                        dVar1 = (double)*(int *)(*param_1 + 0x4c) * _DAT_10041eb0;
                        if (dVar1 <= dVar2) {
                          iVar6 = 2;
                          if (dVar1 + dVar1 <= dVar2) {
                            iVar6 = 1;
                          }
                        }
                        else {
                          iVar6 = 3;
                        }
                      }
                      draw_ui_image_subrect_with_optional_restore
                                (g_shell_ui_image_record_ptr_100f4f98,iVar6 + 4,local_808,local_80c,
                                 0x14,0x34);
                    }
                    else {
                      iVar6 = 6;
                      bVar10 = true;
                      pcVar7 = pcVar8;
                      pcVar9 = s_spp03_1004cc80;
                      do {
                        if (iVar6 == 0) break;
                        iVar6 = iVar6 + -1;
                        bVar10 = *pcVar7 == *pcVar9;
                        pcVar7 = pcVar7 + 1;
                        pcVar9 = pcVar9 + 1;
                      } while (bVar10);
                      if (bVar10) {
                        if (*(int *)(*param_1 + 0x4c) == param_1[3]) {
                          iVar6 = 0;
                        }
                        else {
                          dVar2 = (double)param_1[3];
                          dVar1 = (double)*(int *)(*param_1 + 0x4c) * _DAT_10041eb0;
                          if (dVar1 <= dVar2) {
                            iVar6 = 2;
                            if (dVar1 + dVar1 <= dVar2) {
                              iVar6 = 1;
                            }
                          }
                          else {
                            iVar6 = 3;
                          }
                        }
                        draw_ui_image_subrect_with_optional_restore
                                  (g_shell_ui_image_record_ptr_100f4f98,iVar6 + 8,local_808,
                                   local_80c,0x14,0x34);
                      }
                      else {
                        iVar6 = 6;
                        bVar10 = true;
                        pcVar7 = pcVar8;
                        pcVar9 = s_spp04_1004cc88;
                        do {
                          if (iVar6 == 0) break;
                          iVar6 = iVar6 + -1;
                          bVar10 = *pcVar7 == *pcVar9;
                          pcVar7 = pcVar7 + 1;
                          pcVar9 = pcVar9 + 1;
                        } while (bVar10);
                        if (bVar10) {
                          iVar11 = 0x34;
                          iVar4 = 0x14;
                          iVar6 = FUN_10032920(param_1);
                          draw_ui_image_subrect_with_optional_restore
                                    (g_shell_ui_image_record_ptr_100f4f98,iVar6 + 0xc,local_808,
                                     local_80c,iVar4,iVar11);
                        }
                        else {
                          iVar6 = 6;
                          bVar10 = true;
                          pcVar7 = pcVar8;
                          pcVar9 = s_flm01_1004cc90;
                          do {
                            if (iVar6 == 0) break;
                            iVar6 = iVar6 + -1;
                            bVar10 = *pcVar7 == *pcVar9;
                            pcVar7 = pcVar7 + 1;
                            pcVar9 = pcVar9 + 1;
                          } while (bVar10);
                          if (bVar10) {
                            iVar11 = 0x34;
                            iVar4 = 0x14;
                            iVar6 = FUN_10032920(param_1);
                            draw_ui_image_subrect_with_optional_restore
                                      (g_shell_ui_image_record_ptr_100f4f9c,iVar6,local_808,
                                       local_80c,iVar4,iVar11);
                          }
                          else {
                            iVar6 = 6;
                            bVar10 = true;
                            pcVar7 = pcVar8;
                            pcVar9 = s_flm02_1004cc98;
                            do {
                              if (iVar6 == 0) break;
                              iVar6 = iVar6 + -1;
                              bVar10 = *pcVar7 == *pcVar9;
                              pcVar7 = pcVar7 + 1;
                              pcVar9 = pcVar9 + 1;
                            } while (bVar10);
                            if (bVar10) {
                              iVar11 = 0x34;
                              iVar4 = 0x14;
                              iVar6 = FUN_10032920(param_1);
                              draw_ui_image_subrect_with_optional_restore
                                        (g_shell_ui_image_record_ptr_100f4f9c,iVar6 + 4,local_808,
                                         local_80c,iVar4,iVar11);
                            }
                            else {
                              iVar6 = 6;
                              bVar10 = true;
                              pcVar7 = pcVar8;
                              pcVar9 = s_flm03_1004cca0;
                              do {
                                if (iVar6 == 0) break;
                                iVar6 = iVar6 + -1;
                                bVar10 = *pcVar7 == *pcVar9;
                                pcVar7 = pcVar7 + 1;
                                pcVar9 = pcVar9 + 1;
                              } while (bVar10);
                              if (bVar10) {
                                iVar11 = 0x34;
                                iVar4 = 0x14;
                                iVar6 = FUN_10032920(param_1);
                                draw_ui_image_subrect_with_optional_restore
                                          (g_shell_ui_image_record_ptr_100f4f9c,iVar6 + 8,local_808,
                                           local_80c,iVar4,iVar11);
                              }
                              else {
                                iVar6 = 6;
                                bVar10 = true;
                                pcVar7 = pcVar8;
                                pcVar9 = s_flm04_1004cca8;
                                do {
                                  if (iVar6 == 0) break;
                                  iVar6 = iVar6 + -1;
                                  bVar10 = *pcVar7 == *pcVar9;
                                  pcVar7 = pcVar7 + 1;
                                  pcVar9 = pcVar9 + 1;
                                } while (bVar10);
                                if (bVar10) {
                                  iVar11 = 0x34;
                                  iVar4 = 0x14;
                                  iVar6 = FUN_10032920(param_1);
                                  draw_ui_image_subrect_with_optional_restore
                                            (g_shell_ui_image_record_ptr_100f4f9c,iVar6 + 0xc,
                                             local_808,local_80c,iVar4,iVar11);
                                }
                                else {
                                  iVar6 = 6;
                                  bVar10 = true;
                                  pcVar7 = pcVar8;
                                  pcVar9 = s_mor01_1004ccb0;
                                  do {
                                    if (iVar6 == 0) break;
                                    iVar6 = iVar6 + -1;
                                    bVar10 = *pcVar7 == *pcVar9;
                                    pcVar7 = pcVar7 + 1;
                                    pcVar9 = pcVar9 + 1;
                                  } while (bVar10);
                                  if (bVar10) {
                                    iVar11 = 0x34;
                                    iVar4 = 0x14;
                                    iVar6 = FUN_10032920(param_1);
                                  }
                                  else {
                                    iVar6 = 6;
                                    bVar10 = true;
                                    pcVar7 = pcVar8;
                                    pcVar9 = s_mor02_1004ccb8;
                                    do {
                                      if (iVar6 == 0) break;
                                      iVar6 = iVar6 + -1;
                                      bVar10 = *pcVar7 == *pcVar9;
                                      pcVar7 = pcVar7 + 1;
                                      pcVar9 = pcVar9 + 1;
                                    } while (bVar10);
                                    if (bVar10) {
                                      iVar11 = 0x34;
                                      iVar4 = 0x14;
                                      iVar6 = FUN_10032920(param_1);
                                      iVar6 = iVar6 + 4;
                                    }
                                    else {
                                      iVar6 = 6;
                                      bVar10 = true;
                                      pcVar7 = pcVar8;
                                      pcVar9 = s_mor03_1004ccc0;
                                      do {
                                        if (iVar6 == 0) break;
                                        iVar6 = iVar6 + -1;
                                        bVar10 = *pcVar7 == *pcVar9;
                                        pcVar7 = pcVar7 + 1;
                                        pcVar9 = pcVar9 + 1;
                                      } while (bVar10);
                                      if (bVar10) {
                                        iVar11 = 0x34;
                                        iVar4 = 0x14;
                                        iVar6 = FUN_10032920(param_1);
                                        iVar6 = iVar6 + 8;
                                      }
                                      else {
                                        iVar6 = 6;
                                        bVar10 = true;
                                        pcVar7 = s_mor04_1004ccc8;
                                        do {
                                          if (iVar6 == 0) break;
                                          iVar6 = iVar6 + -1;
                                          bVar10 = *pcVar8 == *pcVar7;
                                          pcVar8 = pcVar8 + 1;
                                          pcVar7 = pcVar7 + 1;
                                        } while (bVar10);
                                        if (!bVar10) break;
                                        iVar11 = 0x34;
                                        iVar4 = 0x14;
                                        iVar6 = FUN_10032920(param_1);
                                        iVar6 = iVar6 + 0xc;
                                      }
                                    }
                                  }
                                  draw_ui_image_subrect_with_optional_restore
                                            (g_shell_ui_image_record_ptr_100f4fa0,iVar6,local_808,
                                             local_80c,iVar4,iVar11);
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                    break;
                  }
                  if (*(int *)(*param_1 + 0x4c) == param_1[3]) {
                    iVar6 = 0;
                  }
                  else {
                    dVar2 = (double)param_1[3];
                    dVar1 = (double)*(int *)(*param_1 + 0x4c) * _DAT_10041eb0;
                    if (dVar1 <= dVar2) {
                      iVar6 = 2;
                      if (dVar1 + dVar1 <= dVar2) {
                        iVar6 = 1;
                      }
                    }
                    else {
                      iVar6 = 3;
                    }
                  }
                  iVar4 = g_shell_ui_image_record_ptr_100f4f98;
                  if (DAT_100f4f58 != 0) {
                    uVar5 = lock_shell_surface_for_draw((int)DAT_100cc518);
                    cVar3 = (char)uVar5;
                    iVar4 = iVar11;
                    goto joined_r0x100324fd;
                  }
                }
              }
            }
          }
        }
      }
    }
    iVar12 = 0x34;
    iVar11 = 0x14;
LAB_100328b7:
    draw_mw2_image_subresource_to_shell_surface
              (DAT_100cc518,iVar4,iVar6,local_808,local_80c,iVar11,iVar12);
    break;
  case 8:
    local_80c = *(int *)(&DAT_1004cc2c + DAT_10051e6c * 8);
    local_808 = *(int *)(&DAT_1004cc28 + DAT_10051e6c * 8);
    clear_text_rect(DAT_100cc518,local_808,local_80c,0x34,0x16);
    if ((-1 < iVar4) && (iVar4 < 7)) {
      if (*(int *)(*param_1 + 0x4c) == param_1[3]) {
        iVar6 = 0;
      }
      else {
        dVar2 = (double)param_1[3];
        dVar1 = (double)*(int *)(*param_1 + 0x4c) * _DAT_10041eb0;
        if (dVar1 <= dVar2) {
          iVar6 = 2;
          if (dVar1 + dVar1 <= dVar2) {
            iVar6 = 1;
          }
        }
        else {
          iVar6 = 3;
        }
      }
      iVar12 = 0x16;
      iVar11 = 0x34;
      iVar6 = iVar6 + iVar4 * 4;
      iVar4 = g_shell_ui_image_record_ptr_100f4fa4;
      goto LAB_100328b7;
    }
    break;
  case 0xc:
  case 0xd:
    if (iVar4 == -1) {
      iVar4 = atoi((char *)(iVar6 + 0x3e));
      iVar4 = iVar4 + -1;
    }
    local_80c = *(int *)(&DAT_1004cbd4 + DAT_10051e6c * 8);
    local_808 = *(int *)(&DAT_1004cbd0 + DAT_10051e6c * 8);
    clear_text_rect(DAT_100cc518,local_808,local_80c,0x28,0x18);
    if ((-1 < iVar4) && (iVar4 < 10)) {
      iVar12 = 0x18;
      iVar11 = 0x28;
      iVar6 = FUN_10032920(param_1);
      iVar6 = iVar6 + iVar4 * 4;
      iVar4 = g_shell_ui_image_record_ptr_100f4fac;
      goto LAB_100328b7;
    }
    break;
  default:
    goto switchD_10031b52_default;
  }
  DAT_10051e6c = DAT_10051e6c + 1;
switchD_10031b52_default:
  return;
}


