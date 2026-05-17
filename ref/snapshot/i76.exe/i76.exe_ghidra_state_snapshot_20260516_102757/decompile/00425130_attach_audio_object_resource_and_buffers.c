/*
 * Program: i76.exe
 * Function: attach_audio_object_resource_and_buffers
 * Entry: 00425130
 * Signature: undefined4 __cdecl attach_audio_object_resource_and_buffers(undefined4 * param_1, int * param_2, int * param_3)
 */


/* cgpt rename v2: Loads/attaches audio object backing resources and buffer/interface state. */

undefined4 __cdecl
attach_audio_object_resource_and_buffers(undefined4 *param_1,int *param_2,int *param_3)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  bool bVar4;
  int *piVar5;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  undefined3 extraout_var_02;
  uint *puVar6;
  int *piVar7;
  int *piVar8;
  undefined3 extraout_var_03;
  undefined3 extraout_var_04;
  undefined3 extraout_var_05;
  undefined3 extraout_var_06;
  LPVOID pvVar9;
  int iVar10;
  uint uVar11;
  uint uVar12;
  int *piVar13;
  undefined4 *puVar14;
  char *pcVar15;
  undefined4 **ppuVar16;
  undefined4 **ppuVar17;
  int *piVar18;
  undefined4 *puVar19;
  char *pcVar20;
  char *pcVar21;
  int local_44c;
  uint local_448;
  char local_444 [16];
  undefined4 local_434;
  undefined4 local_430;
  int *local_42c;
  undefined4 local_428;
  int *local_424;
  int *local_420;
  undefined4 *local_41c;
  undefined4 *local_418 [4];
  int *piStack_408;
  uint uStack_404;
  char local_400 [256];
  char local_300 [256];
  char local_200 [256];
  char local_100 [256];
  
  do {
    piVar5 = find_audio_object_by_name_with_loaded_buffer((char *)(param_2 + 1));
    if ((piVar5 == (int *)0x0) || (piVar5[0x15] == 0)) {
      if ((param_2[0x1e] & 0x200U) == 0) {
        _splitpath((char *)(param_2 + 1),(char *)&local_41c,local_100,(char *)local_418,local_200);
        uVar11 = 0xffffffff;
        pcVar15 = &DAT_004ed898;
        do {
          pcVar21 = pcVar15;
          if (uVar11 == 0) break;
          uVar11 = uVar11 - 1;
          pcVar21 = pcVar15 + 1;
          cVar2 = *pcVar15;
          pcVar15 = pcVar21;
        } while (cVar2 != '\0');
        uVar11 = ~uVar11;
        iVar10 = -1;
        ppuVar17 = local_418;
        do {
          ppuVar16 = ppuVar17;
          if (iVar10 == 0) break;
          iVar10 = iVar10 + -1;
          ppuVar16 = (undefined4 **)((int)ppuVar17 + 1);
          cVar2 = *(char *)ppuVar17;
          ppuVar17 = ppuVar16;
        } while (cVar2 != '\0');
        pcVar15 = pcVar21 + -uVar11;
        pcVar21 = (char *)((int)ppuVar16 + -1);
        for (uVar12 = uVar11 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
          *(undefined4 *)pcVar21 = *(undefined4 *)pcVar15;
          pcVar15 = pcVar15 + 4;
          pcVar21 = pcVar21 + 4;
        }
        for (uVar11 = uVar11 & 3; uVar11 != 0; uVar11 = uVar11 - 1) {
          *pcVar21 = *pcVar15;
          pcVar15 = pcVar15 + 1;
          pcVar21 = pcVar21 + 1;
        }
        bVar4 = resource_exists_in_cache_or_search_paths((char *)local_418);
        if (CONCAT31(extraout_var,bVar4) == 0) {
          uVar11 = 0xffffffff;
          piVar13 = param_2 + 1;
          do {
            piVar8 = piVar13;
            if (uVar11 == 0) break;
            uVar11 = uVar11 - 1;
            piVar8 = (int *)((int)piVar13 + 1);
            iVar10 = *piVar13;
            piVar13 = piVar8;
          } while (bVar4 != (bool)(char)iVar10);
          uVar11 = ~uVar11;
          puVar14 = (undefined4 *)((int)piVar8 - uVar11);
          ppuVar17 = local_418;
          for (uVar12 = uVar11 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
            *ppuVar17 = (undefined4 *)*puVar14;
            puVar14 = puVar14 + 1;
            ppuVar17 = ppuVar17 + 1;
          }
          for (uVar11 = uVar11 & 3; uVar11 != 0; uVar11 = uVar11 - 1) {
            *(undefined1 *)ppuVar17 = *(undefined1 *)puVar14;
            puVar14 = (undefined4 *)((int)puVar14 + 1);
            ppuVar17 = (undefined4 **)((int)ppuVar17 + 1);
          }
        }
        puVar6 = open_resource_file_into_memory((char *)local_418);
        param_2[0x14] = (int)puVar6;
        param_2[0x13] = (int)puVar6;
      }
      else {
        puVar6 = (uint *)param_2[0x13];
        param_2[0x14] = (int)puVar6;
      }
      if (puVar6 == (uint *)0x0) {
        return 0;
      }
      piVar13 = (int *)param_2[0x13];
      if (*piVar13 == 0x30534147) {
        param_2[0x14] = param_2[0x14] + 0x1c;
        piVar8 = piVar13;
        piVar18 = param_2 + 0xc;
        for (iVar10 = 7; iVar10 != 0; iVar10 = iVar10 + -1) {
          *piVar18 = *piVar8;
          piVar8 = piVar8 + 1;
          piVar18 = piVar18 + 1;
        }
        copy_audio_params_with_defaults(piVar13,param_2 + 0xc);
      }
      *(char *)((int)param_2 + 0x77) = (char)param_2[0xd];
      if (param_3 == (int *)0x0) {
        param_3 = param_2 + 0xc;
      }
      merge_audio_params_with_defaults((int)param_3,(int)(param_2 + 0xc));
      param_2[0x19] = 0;
      param_2[0x1b] = 0;
      if ((param_2[0x1e] & 0x200U) == 0) {
        _splitpath((char *)(param_2 + 1),(char *)&local_448,local_400,local_444,local_300);
        uVar11 = 0xffffffff;
        pcVar15 = &DAT_004ed898;
        do {
          pcVar21 = pcVar15;
          if (uVar11 == 0) break;
          uVar11 = uVar11 - 1;
          pcVar21 = pcVar15 + 1;
          cVar2 = *pcVar15;
          pcVar15 = pcVar21;
        } while (cVar2 != '\0');
        uVar11 = ~uVar11;
        iVar10 = -1;
        pcVar15 = local_444;
        do {
          pcVar20 = pcVar15;
          if (iVar10 == 0) break;
          iVar10 = iVar10 + -1;
          pcVar20 = pcVar15 + 1;
          cVar2 = *pcVar15;
          pcVar15 = pcVar20;
        } while (cVar2 != '\0');
        pcVar15 = pcVar21 + -uVar11;
        pcVar21 = pcVar20 + -1;
        for (uVar12 = uVar11 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
          *(undefined4 *)pcVar21 = *(undefined4 *)pcVar15;
          pcVar15 = pcVar15 + 4;
          pcVar21 = pcVar21 + 4;
        }
        for (uVar11 = uVar11 & 3; uVar11 != 0; uVar11 = uVar11 - 1) {
          *pcVar21 = *pcVar15;
          pcVar15 = pcVar15 + 1;
          pcVar21 = pcVar21 + 1;
        }
        bVar4 = resource_exists_in_cache_or_search_paths(local_444);
        if (CONCAT31(extraout_var_00,bVar4) == 0) {
          uVar11 = 0xffffffff;
          piVar13 = param_2 + 1;
          do {
            piVar8 = piVar13;
            if (uVar11 == 0) break;
            uVar11 = uVar11 - 1;
            piVar8 = (int *)((int)piVar13 + 1);
            iVar10 = *piVar13;
            piVar13 = piVar8;
          } while (bVar4 != (bool)(char)iVar10);
          uVar11 = ~uVar11;
          pcVar15 = (char *)((int)piVar8 - uVar11);
          pcVar21 = local_444;
          for (uVar12 = uVar11 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
            *(undefined4 *)pcVar21 = *(undefined4 *)pcVar15;
            pcVar15 = pcVar15 + 4;
            pcVar21 = pcVar21 + 4;
          }
          for (uVar11 = uVar11 & 3; uVar11 != 0; uVar11 = uVar11 - 1) {
            *pcVar21 = *pcVar15;
            pcVar15 = pcVar15 + 1;
            pcVar21 = pcVar21 + 1;
          }
        }
        release_resource_file_reference(local_444);
        param_2[0x13] = 0;
        param_2[0x14] = 0;
      }
    }
    else if (param_2 != piVar5) {
      piVar13 = param_2 + 0xc;
      piVar8 = piVar5 + 0xc;
      piVar18 = piVar13;
      for (iVar10 = 7; iVar10 != 0; iVar10 = iVar10 + -1) {
        *piVar18 = *piVar8;
        piVar8 = piVar8 + 1;
        piVar18 = piVar18 + 1;
      }
      param_2[0xd] = (uint)*(byte *)((int)piVar5 + 0x77);
      param_2[0x13] = piVar5[0x13];
      param_2[0x14] = piVar5[0x14];
      param_2[0x19] = 1;
      param_2[0x15] = 0;
      param_2[0x16] = 0;
      *(undefined1 *)(param_2 + 0x1d) = 0xff;
      piVar5[0x1b] = piVar5[0x1b] + 1;
      if (param_3 == (int *)0x0) {
        param_3 = piVar13;
      }
      merge_audio_params_with_defaults((int)param_3,(int)piVar13);
    }
    cVar2 = evaluate_audio_object_priority_distance_state(param_2);
    local_44c = CONCAT31(extraout_var_01,cVar2);
  } while (local_44c == 6);
  if ((((local_44c != 1) && (local_44c != 4)) && (local_44c != 3)) && (local_44c != 5))
  goto LAB_00425a4c;
  local_424 = (int *)0x0;
  local_42c = (int *)0x0;
  local_428 = 0;
  local_434 = 0x14;
  if ((param_2[0x17] == 0) || (local_430 = 0xb2, param_1[2] == 0)) {
    local_430 = 0xe2;
  }
  if (piVar5 == (int *)0x0) {
    local_418[0] = (undefined4 *)0x0;
    bVar4 = true;
    if ((param_2[0x1e] & 0x200U) == 0) {
      _splitpath((char *)(param_2 + 1),(char *)&local_448,local_300,local_444,local_400);
      uVar11 = 0xffffffff;
      pcVar15 = &DAT_004ed898;
      do {
        pcVar21 = pcVar15;
        if (uVar11 == 0) break;
        uVar11 = uVar11 - 1;
        pcVar21 = pcVar15 + 1;
        cVar2 = *pcVar15;
        pcVar15 = pcVar21;
      } while (cVar2 != '\0');
      uVar11 = ~uVar11;
      iVar10 = -1;
      pcVar15 = local_444;
      do {
        pcVar20 = pcVar15;
        if (iVar10 == 0) break;
        iVar10 = iVar10 + -1;
        pcVar20 = pcVar15 + 1;
        cVar2 = *pcVar15;
        pcVar15 = pcVar20;
      } while (cVar2 != '\0');
      pcVar15 = pcVar21 + -uVar11;
      pcVar21 = pcVar20 + -1;
      for (uVar12 = uVar11 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
        *(undefined4 *)pcVar21 = *(undefined4 *)pcVar15;
        pcVar15 = pcVar15 + 4;
        pcVar21 = pcVar21 + 4;
      }
      for (uVar11 = uVar11 & 3; uVar11 != 0; uVar11 = uVar11 - 1) {
        *pcVar21 = *pcVar15;
        pcVar15 = pcVar15 + 1;
        pcVar21 = pcVar21 + 1;
      }
      bVar3 = resource_exists_in_cache_or_search_paths(local_444);
      if (CONCAT31(extraout_var_02,bVar3) == 0) {
        uVar11 = 0xffffffff;
        piVar5 = param_2 + 1;
        do {
          piVar13 = piVar5;
          if (uVar11 == 0) break;
          uVar11 = uVar11 - 1;
          piVar13 = (int *)((int)piVar5 + 1);
          iVar10 = *piVar5;
          piVar5 = piVar13;
        } while (bVar3 != (bool)(char)iVar10);
        uVar11 = ~uVar11;
        pcVar15 = (char *)((int)piVar13 - uVar11);
        pcVar21 = local_444;
        for (uVar12 = uVar11 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
          *(undefined4 *)pcVar21 = *(undefined4 *)pcVar15;
          pcVar15 = pcVar15 + 4;
          pcVar21 = pcVar21 + 4;
        }
        for (uVar11 = uVar11 & 3; uVar11 != 0; uVar11 = uVar11 - 1) {
          *pcVar21 = *pcVar15;
          pcVar15 = pcVar15 + 1;
          pcVar21 = pcVar21 + 1;
        }
      }
      puVar6 = open_resource_file_into_memory(local_444);
      param_2[0x14] = (int)puVar6;
      param_2[0x13] = (int)puVar6;
      if (puVar6 == (uint *)0x0) {
        bVar4 = false;
      }
      else {
        local_418[0] = (undefined4 *)0x1;
        if (*puVar6 == 0x30534147) {
          param_2[0x14] = param_2[0x14] + 0x1c;
        }
      }
    }
    bVar3 = false;
    if (bVar4) {
      piVar13 = (int *)param_2[0x14];
      piVar5 = param_2 + 0x14;
      if (&stack0x00000000 != (undefined1 *)0x424) {
        local_424 = (int *)0x0;
      }
      if (piVar5 != (int *)0x0) {
        *piVar5 = 0;
      }
      if (&stack0x00000000 != (undefined1 *)0x42c) {
        local_42c = (int *)0x0;
      }
      piVar8 = piVar13 + 3;
      if ((*piVar13 == 0x46464952) && (piVar13[2] == 0x45564157)) {
        local_420 = (int *)(piVar13[1] + -4 + (int)piVar8);
        piVar13 = local_42c;
        piVar18 = local_424;
        while (piVar8 < local_420) {
          piVar1 = (int *)piVar8[1];
          piVar7 = piVar8 + 2;
          if (*piVar8 == 0x20746d66) {
            if ((&stack0x00000000 != (undefined1 *)0x424) && (piVar18 == (int *)0x0)) {
              if (piVar1 < (int *)0xe) break;
              piVar18 = piVar7;
              local_424 = piVar7;
              if ((piVar5 == (int *)0x0) || (*piVar5 != 0)) {
                piVar8 = piVar13;
                if (&stack0x00000000 != (undefined1 *)0x42c) goto joined_r0x0042562b;
                goto LAB_00425bfa;
              }
            }
          }
          else if ((*piVar8 == 0x61746164) &&
                  (((piVar5 != (int *)0x0 && (*piVar5 == 0)) ||
                   ((&stack0x00000000 != (undefined1 *)0x42c && (piVar13 == (int *)0x0)))))) {
            if (piVar5 != (int *)0x0) {
              *piVar5 = (int)piVar7;
            }
            if (&stack0x00000000 != (undefined1 *)0x42c) {
              piVar13 = piVar1;
              local_42c = piVar1;
            }
            piVar8 = piVar18;
            if (&stack0x00000000 != (undefined1 *)0x424) {
joined_r0x0042562b:
              if (piVar8 == (int *)0x0) goto LAB_00425631;
            }
LAB_00425bfa:
            bVar3 = true;
            goto LAB_00425645;
          }
LAB_00425631:
          piVar8 = (int *)((int)piVar7 + ((uint)((int)piVar1 + 1) & 0xfffffffe));
        }
      }
      bVar3 = false;
    }
LAB_00425645:
    if ((bVar3) && (local_42c != (int *)0x0)) {
      iVar10 = (**(code **)(*(int *)*param_1 + 0xc))((int *)*param_1,&local_434,param_2 + 0x15,0);
      piStack_408 = (int *)param_2[0x15];
      local_41c = (undefined4 *)param_2[0x14];
      bVar3 = iVar10 == 0;
      if ((((piStack_408 != (int *)0x0) && (local_41c != (undefined4 *)0x0)) &&
          (local_42c != (int *)0x0)) &&
         (iVar10 = (**(code **)(*piStack_408 + 0x2c))
                             (piStack_408,0,local_42c,local_418,&local_448,&local_420,&uStack_404,0)
         , -1 < iVar10)) {
        puVar14 = local_41c;
        puVar19 = local_418[0];
        for (uVar11 = local_448 >> 2; uVar11 != 0; uVar11 = uVar11 - 1) {
          *puVar19 = *puVar14;
          puVar14 = puVar14 + 1;
          puVar19 = puVar19 + 1;
        }
        for (uVar11 = local_448 & 3; uVar11 != 0; uVar11 = uVar11 - 1) {
          *(undefined1 *)puVar19 = *(undefined1 *)puVar14;
          puVar14 = (undefined4 *)((int)puVar14 + 1);
          puVar19 = (undefined4 *)((int)puVar19 + 1);
        }
        if (uStack_404 != 0) {
          piVar5 = (int *)((int)local_41c + local_448);
          piVar13 = local_420;
          for (uVar11 = uStack_404 >> 2; uVar11 != 0; uVar11 = uVar11 - 1) {
            *piVar13 = *piVar5;
            piVar5 = piVar5 + 1;
            piVar13 = piVar13 + 1;
          }
          for (uVar11 = uStack_404 & 3; uVar11 != 0; uVar11 = uVar11 - 1) {
            *(char *)piVar13 = (char)*piVar5;
            piVar5 = (int *)((int)piVar5 + 1);
            piVar13 = (int *)((int)piVar13 + 1);
          }
        }
        (**(code **)(*piStack_408 + 0x4c))(piStack_408,local_418[0],local_448,local_420,uStack_404);
        if (bVar3) {
          DAT_005fcbf4 = DAT_005fcbf4 + (int)local_42c;
          local_418[1] = (undefined4 *)0x0;
          param_2[0x1c] = (int)local_42c;
          param_2[0x12] = local_424[1];
          local_418[0] = (undefined4 *)local_424[1];
          param_2[6] = (int)(float)local_418[0];
          if ((param_2[0x17] != 0) && (param_1[2] != 0)) {
            (*(code *)**(undefined4 **)param_2[0x15])
                      ((undefined4 *)param_2[0x15],&DAT_004bcf48,param_2 + 0x16);
          }
          if ((param_2[0x1e] & 0x200U) == 0) {
            _splitpath((char *)(param_2 + 1),(char *)&local_448,local_300,local_444,local_400);
            uVar11 = 0xffffffff;
            pcVar15 = &DAT_004ed898;
            do {
              pcVar21 = pcVar15;
              if (uVar11 == 0) break;
              uVar11 = uVar11 - 1;
              pcVar21 = pcVar15 + 1;
              cVar2 = *pcVar15;
              pcVar15 = pcVar21;
            } while (cVar2 != '\0');
            uVar11 = ~uVar11;
            iVar10 = -1;
            pcVar15 = local_444;
            do {
              pcVar20 = pcVar15;
              if (iVar10 == 0) break;
              iVar10 = iVar10 + -1;
              pcVar20 = pcVar15 + 1;
              cVar2 = *pcVar15;
              pcVar15 = pcVar20;
            } while (cVar2 != '\0');
            pcVar15 = pcVar21 + -uVar11;
            pcVar21 = pcVar20 + -1;
            for (uVar12 = uVar11 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
              *(undefined4 *)pcVar21 = *(undefined4 *)pcVar15;
              pcVar15 = pcVar15 + 4;
              pcVar21 = pcVar21 + 4;
            }
            for (uVar11 = uVar11 & 3; uVar11 != 0; uVar11 = uVar11 - 1) {
              *pcVar21 = *pcVar15;
              pcVar15 = pcVar15 + 1;
              pcVar21 = pcVar21 + 1;
            }
            bVar4 = resource_exists_in_cache_or_search_paths(local_444);
            if (CONCAT31(extraout_var_03,bVar4) == 0) {
              uVar11 = 0xffffffff;
              piVar5 = param_2 + 1;
              do {
                piVar13 = piVar5;
                if (uVar11 == 0) break;
                uVar11 = uVar11 - 1;
                piVar13 = (int *)((int)piVar5 + 1);
                iVar10 = *piVar5;
                piVar5 = piVar13;
              } while (bVar4 != (bool)(char)iVar10);
              uVar11 = ~uVar11;
              pcVar15 = (char *)((int)piVar13 - uVar11);
              pcVar21 = local_444;
              for (uVar12 = uVar11 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
                *(undefined4 *)pcVar21 = *(undefined4 *)pcVar15;
                pcVar15 = pcVar15 + 4;
                pcVar21 = pcVar21 + 4;
              }
              for (uVar11 = uVar11 & 3; uVar11 != 0; uVar11 = uVar11 - 1) {
                *pcVar21 = *pcVar15;
                pcVar15 = pcVar15 + 1;
                pcVar21 = pcVar21 + 1;
              }
            }
            release_resource_file_reference(local_444);
            param_2[0x13] = 0;
            param_2[0x14] = 0;
          }
          if (local_44c == 1) {
            local_44c = move_audio_object_between_active_and_pending_lists
                                  (param_2,(undefined4 *)0x1);
          }
        }
      }
    }
    else if (((param_2[0x1e] & 0x200U) == 0) && ((local_418[0] != (undefined4 *)0x0 && (bVar3)))) {
      _splitpath((char *)(param_2 + 1),(char *)&local_448,local_300,local_444,local_400);
      uVar11 = 0xffffffff;
      pcVar15 = &DAT_004ed898;
      do {
        pcVar21 = pcVar15;
        if (uVar11 == 0) break;
        uVar11 = uVar11 - 1;
        pcVar21 = pcVar15 + 1;
        cVar2 = *pcVar15;
        pcVar15 = pcVar21;
      } while (cVar2 != '\0');
      uVar11 = ~uVar11;
      iVar10 = -1;
      pcVar15 = local_444;
      do {
        pcVar20 = pcVar15;
        if (iVar10 == 0) break;
        iVar10 = iVar10 + -1;
        pcVar20 = pcVar15 + 1;
        cVar2 = *pcVar15;
        pcVar15 = pcVar20;
      } while (cVar2 != '\0');
      pcVar15 = pcVar21 + -uVar11;
      pcVar21 = pcVar20 + -1;
      for (uVar12 = uVar11 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
        *(undefined4 *)pcVar21 = *(undefined4 *)pcVar15;
        pcVar15 = pcVar15 + 4;
        pcVar21 = pcVar21 + 4;
      }
      for (uVar11 = uVar11 & 3; uVar11 != 0; uVar11 = uVar11 - 1) {
        *pcVar21 = *pcVar15;
        pcVar15 = pcVar15 + 1;
        pcVar21 = pcVar21 + 1;
      }
      bVar4 = resource_exists_in_cache_or_search_paths(local_444);
      if (CONCAT31(extraout_var_04,bVar4) == 0) {
        uVar11 = 0xffffffff;
        piVar5 = param_2 + 1;
        do {
          piVar13 = piVar5;
          if (uVar11 == 0) break;
          uVar11 = uVar11 - 1;
          piVar13 = (int *)((int)piVar5 + 1);
          iVar10 = *piVar5;
          piVar5 = piVar13;
        } while (bVar4 != (bool)(char)iVar10);
        uVar11 = ~uVar11;
        pcVar15 = (char *)((int)piVar13 - uVar11);
        pcVar21 = local_444;
        for (uVar12 = uVar11 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
          *(undefined4 *)pcVar21 = *(undefined4 *)pcVar15;
          pcVar15 = pcVar15 + 4;
          pcVar21 = pcVar21 + 4;
        }
        for (uVar11 = uVar11 & 3; uVar11 != 0; uVar11 = uVar11 - 1) {
          *pcVar21 = *pcVar15;
          pcVar15 = pcVar15 + 1;
          pcVar21 = pcVar21 + 1;
        }
      }
      release_resource_file_reference(local_444);
      param_2[0x13] = 0;
      param_2[0x14] = 0;
    }
    if (!bVar3) {
      local_44c = 0;
      if (param_2 != (int *)0x0) {
        stop_audio_object_buffer_if_playing((uint)param_2);
        unlink_audio_object_from_active_or_pending_list(param_2);
        if (param_2[0x15] != 0) {
          piVar5 = (int *)param_2[0x16];
          if (piVar5 != (int *)0x0) {
            (**(code **)(*piVar5 + 8))(piVar5);
          }
          (**(code **)(*(int *)param_2[0x15] + 8))((int *)param_2[0x15]);
          param_2[0x15] = 0;
          param_2[0x16] = 0;
          DAT_005fcbf4 = DAT_005fcbf4 + -param_2[0x1c];
        }
        if (param_2[0x13] != 0) {
          if ((param_2[0x1e] & 0x200U) == 0) {
            _splitpath((char *)(param_2 + 1),(char *)&local_448,local_300,local_444,local_400);
            uVar11 = 0xffffffff;
            pcVar15 = &DAT_004ed898;
            do {
              pcVar21 = pcVar15;
              if (uVar11 == 0) break;
              uVar11 = uVar11 - 1;
              pcVar21 = pcVar15 + 1;
              cVar2 = *pcVar15;
              pcVar15 = pcVar21;
            } while (cVar2 != '\0');
            uVar11 = ~uVar11;
            iVar10 = -1;
            pcVar15 = local_444;
            do {
              pcVar20 = pcVar15;
              if (iVar10 == 0) break;
              iVar10 = iVar10 + -1;
              pcVar20 = pcVar15 + 1;
              cVar2 = *pcVar15;
              pcVar15 = pcVar20;
            } while (cVar2 != '\0');
            pcVar15 = pcVar21 + -uVar11;
            pcVar21 = pcVar20 + -1;
            for (uVar12 = uVar11 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
              *(undefined4 *)pcVar21 = *(undefined4 *)pcVar15;
              pcVar15 = pcVar15 + 4;
              pcVar21 = pcVar21 + 4;
            }
            for (uVar11 = uVar11 & 3; uVar11 != 0; uVar11 = uVar11 - 1) {
              *pcVar21 = *pcVar15;
              pcVar15 = pcVar15 + 1;
              pcVar21 = pcVar21 + 1;
            }
            bVar4 = resource_exists_in_cache_or_search_paths(local_444);
            if (CONCAT31(extraout_var_05,bVar4) == 0) {
              uVar11 = 0xffffffff;
              piVar5 = param_2 + 1;
              do {
                piVar13 = piVar5;
                if (uVar11 == 0) break;
                uVar11 = uVar11 - 1;
                piVar13 = (int *)((int)piVar5 + 1);
                iVar10 = *piVar5;
                piVar5 = piVar13;
              } while (bVar4 != (bool)(char)iVar10);
              uVar11 = ~uVar11;
              pcVar15 = (char *)((int)piVar13 - uVar11);
              pcVar21 = local_444;
              for (uVar12 = uVar11 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
                *(undefined4 *)pcVar21 = *(undefined4 *)pcVar15;
                pcVar15 = pcVar15 + 4;
                pcVar21 = pcVar21 + 4;
              }
              for (uVar11 = uVar11 & 3; uVar11 != 0; uVar11 = uVar11 - 1) {
                *pcVar21 = *pcVar15;
                pcVar15 = pcVar15 + 1;
                pcVar21 = pcVar21 + 1;
              }
            }
            release_resource_file_reference(local_444);
          }
          param_2[0x13] = 0;
          param_2[0x14] = 0;
        }
        if ((LPVOID)param_2[0x17] != (LPVOID)0x0) {
          pvVar9 = release_world_object_tree_reference((LPVOID)param_2[0x17],&PTR_DAT_004ed7ec);
          param_2[0x17] = (int)pvVar9;
          if (pvVar9 != (LPVOID)0x0) {
            finalize_released_world_object_after_damage(pvVar9,&PTR_DAT_004ed7ec);
          }
        }
        HeapFree(DAT_005fcc00,0,param_2);
      }
      param_2 = (int *)0x0;
    }
    goto LAB_00425a4c;
  }
  if (piVar5[0x15] == 0) {
    local_44c = 0;
    goto LAB_00425a4c;
  }
  iVar10 = (**(code **)(*(int *)*param_1 + 0x14))((int *)*param_1,piVar5[0x15],param_2 + 0x15);
  if ((iVar10 == 0) && (puVar14 = (undefined4 *)param_2[0x15], puVar14 != (undefined4 *)0x0)) {
    if ((param_2[0x17] != 0) && (param_1[2] != 0)) {
      iVar10 = (**(code **)*puVar14)(puVar14,&DAT_004bcf48,param_2 + 0x16);
      if ((iVar10 != 0) || (param_2[0x16] == 0)) goto LAB_00425441;
    }
  }
  else {
LAB_00425441:
    local_44c = 0;
  }
  if (local_44c == 1) {
    local_44c = move_audio_object_between_active_and_pending_lists(param_2,(undefined4 *)0x1);
  }
LAB_00425a4c:
  if (local_44c == 4) {
    local_44c = set_audio_object_playback_flags_and_queue(param_2,0x20);
  }
  else if (local_44c == 3) {
    local_44c = set_audio_object_playback_flags_and_queue(param_2,0x40);
  }
  else if (local_44c == 5) {
    local_44c = set_audio_object_playback_flags_and_queue(param_2,0x80);
  }
  else if (local_44c == 2) {
    if (param_2 != (int *)0x0) {
      stop_audio_object_buffer_if_playing((uint)param_2);
      unlink_audio_object_from_active_or_pending_list(param_2);
      if (param_2[0x15] != 0) {
        piVar5 = (int *)param_2[0x16];
        if (piVar5 != (int *)0x0) {
          (**(code **)(*piVar5 + 8))(piVar5);
        }
        (**(code **)(*(int *)param_2[0x15] + 8))((int *)param_2[0x15]);
        param_2[0x15] = 0;
        param_2[0x16] = 0;
        DAT_005fcbf4 = DAT_005fcbf4 + -param_2[0x1c];
      }
      if (param_2[0x13] != 0) {
        if ((param_2[0x1e] & 0x200U) == 0) {
          _splitpath((char *)(param_2 + 1),(char *)&local_448,local_300,local_444,local_400);
          uVar11 = 0xffffffff;
          pcVar15 = &DAT_004ed898;
          do {
            pcVar21 = pcVar15;
            if (uVar11 == 0) break;
            uVar11 = uVar11 - 1;
            pcVar21 = pcVar15 + 1;
            cVar2 = *pcVar15;
            pcVar15 = pcVar21;
          } while (cVar2 != '\0');
          uVar11 = ~uVar11;
          iVar10 = -1;
          pcVar15 = local_444;
          do {
            pcVar20 = pcVar15;
            if (iVar10 == 0) break;
            iVar10 = iVar10 + -1;
            pcVar20 = pcVar15 + 1;
            cVar2 = *pcVar15;
            pcVar15 = pcVar20;
          } while (cVar2 != '\0');
          pcVar15 = pcVar21 + -uVar11;
          pcVar21 = pcVar20 + -1;
          for (uVar12 = uVar11 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
            *(undefined4 *)pcVar21 = *(undefined4 *)pcVar15;
            pcVar15 = pcVar15 + 4;
            pcVar21 = pcVar21 + 4;
          }
          for (uVar11 = uVar11 & 3; uVar11 != 0; uVar11 = uVar11 - 1) {
            *pcVar21 = *pcVar15;
            pcVar15 = pcVar15 + 1;
            pcVar21 = pcVar21 + 1;
          }
          bVar4 = resource_exists_in_cache_or_search_paths(local_444);
          if (CONCAT31(extraout_var_06,bVar4) == 0) {
            uVar11 = 0xffffffff;
            piVar5 = param_2 + 1;
            do {
              piVar13 = piVar5;
              if (uVar11 == 0) break;
              uVar11 = uVar11 - 1;
              piVar13 = (int *)((int)piVar5 + 1);
              iVar10 = *piVar5;
              piVar5 = piVar13;
            } while (bVar4 != (bool)(char)iVar10);
            uVar11 = ~uVar11;
            pcVar15 = (char *)((int)piVar13 - uVar11);
            pcVar21 = local_444;
            for (uVar12 = uVar11 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
              *(undefined4 *)pcVar21 = *(undefined4 *)pcVar15;
              pcVar15 = pcVar15 + 4;
              pcVar21 = pcVar21 + 4;
            }
            for (uVar11 = uVar11 & 3; uVar11 != 0; uVar11 = uVar11 - 1) {
              *pcVar21 = *pcVar15;
              pcVar15 = pcVar15 + 1;
              pcVar21 = pcVar21 + 1;
            }
          }
          release_resource_file_reference(local_444);
        }
        param_2[0x13] = 0;
        param_2[0x14] = 0;
      }
      if ((LPVOID)param_2[0x17] != (LPVOID)0x0) {
        pvVar9 = release_world_object_tree_reference((LPVOID)param_2[0x17],&PTR_DAT_004ed7ec);
        param_2[0x17] = (int)pvVar9;
        if (pvVar9 != (LPVOID)0x0) {
          finalize_released_world_object_after_damage(pvVar9,&PTR_DAT_004ed7ec);
        }
      }
      HeapFree(DAT_005fcc00,0,param_2);
    }
    local_44c = 0;
  }
  if ((local_44c != 0) && (local_44c != 2)) {
    return 1;
  }
  return 0;
}


