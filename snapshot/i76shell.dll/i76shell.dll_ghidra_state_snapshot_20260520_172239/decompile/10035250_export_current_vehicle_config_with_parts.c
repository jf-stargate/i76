/*
 * Program: i76shell.dll
 * Function: export_current_vehicle_config_with_parts
 * Entry: 10035250
 * Signature: undefined __cdecl export_current_vehicle_config_with_parts(char * param_1, int param_2)
 */


void __cdecl export_current_vehicle_config_with_parts(char *param_1,int param_2)

{
  char cVar1;
  int *piVar2;
  undefined **ppuVar3;
  undefined4 uVar4;
  char *pcVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  int *piVar10;
  int iVar11;
  int *piVar12;
  char *pcVar13;
  bool bVar14;
  int local_10c;
  char *local_104;
  int local_100;
  int local_fc;
  int local_f8 [7];
  char local_dc [13];
  char local_cf [13];
  int local_c2;
  int local_be;
  int local_ba;
  char local_b6 [13];
  char local_a9 [13];
  char local_9c [13];
  undefined4 local_8f;
  undefined4 local_8b;
  undefined4 local_87;
  undefined4 local_83;
  undefined4 local_7f;
  undefined4 local_7b;
  undefined4 local_77;
  undefined4 local_73;
  undefined4 local_6f;
  undefined1 local_68 [4];
  char local_64 [13];
  undefined4 local_57;
  char local_53 [13];
  undefined4 local_46;
  char local_42 [66];
  
  local_10c = 0;
  piVar2 = create_pointer_list_default_16();
  uVar6 = 0xffffffff;
  pcVar5 = &DAT_100581b4 + *(int *)(DAT_100c5ad8 + 0x38) * 0x8c4;
  do {
    pcVar13 = pcVar5;
    if (uVar6 == 0) break;
    uVar6 = uVar6 - 1;
    pcVar13 = pcVar5 + 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar13;
  } while (cVar1 != '\0');
  uVar6 = ~uVar6;
  piVar10 = (int *)(pcVar13 + -uVar6);
  piVar12 = local_f8 + 3;
  for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
    *piVar12 = *piVar10;
    piVar10 = piVar10 + 1;
    piVar12 = piVar12 + 1;
  }
  for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(char *)piVar12 = (char)*piVar10;
    piVar10 = (int *)((int)piVar10 + 1);
    piVar12 = (int *)((int)piVar12 + 1);
  }
  uVar6 = 0xffffffff;
  pcVar5 = &DAT_100589c0 + *(int *)(DAT_100c5ad8 + 0x38) * 0x8c4;
  do {
    pcVar13 = pcVar5;
    if (uVar6 == 0) break;
    uVar6 = uVar6 - 1;
    pcVar13 = pcVar5 + 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar13;
  } while (cVar1 != '\0');
  uVar6 = ~uVar6;
  pcVar5 = pcVar13 + -uVar6;
  pcVar13 = local_dc;
  for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
    *(undefined4 *)pcVar13 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcVar13 = pcVar13 + 4;
  }
  for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
    *pcVar13 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar13 = pcVar13 + 1;
  }
  uVar6 = 0xffffffff;
  pcVar5 = &DAT_100589cd + *(int *)(DAT_100c5ad8 + 0x38) * 0x8c4;
  do {
    pcVar13 = pcVar5;
    if (uVar6 == 0) break;
    uVar6 = uVar6 - 1;
    pcVar13 = pcVar5 + 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar13;
  } while (cVar1 != '\0');
  uVar6 = ~uVar6;
  pcVar5 = pcVar13 + -uVar6;
  pcVar13 = local_cf;
  for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
    *(undefined4 *)pcVar13 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcVar13 = pcVar13 + 4;
  }
  for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
    *pcVar13 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar13 = pcVar13 + 1;
  }
  ppuVar3 = find_current_vehicle_part_by_type_and_name(2,DAT_100d1dac);
  local_c2 = atoi(*ppuVar3 + 0x31);
  local_c2 = local_c2 + -1;
  ppuVar3 = find_current_vehicle_part_by_type_and_name(3,DAT_100d1dc0);
  local_be = atoi(*ppuVar3 + 0x31);
  local_be = local_be + -1;
  ppuVar3 = find_current_vehicle_part_by_type_and_name(4,DAT_100d1dbc);
  local_ba = atoi(*ppuVar3 + 0x31);
  local_ba = local_ba + -1;
  populate_vehicle_part_list_by_current_slot_names(&LAB_10034350,(int)piVar2,DAT_100d1db8);
  piVar10 = *(int **)piVar2[2];
  if (piVar10 == (int *)0x0) {
    uVar6 = 0xffffffff;
    pcVar5 = s_null_1004ce58;
    do {
      pcVar13 = pcVar5;
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      pcVar13 = pcVar5 + 1;
      cVar1 = *pcVar5;
      pcVar5 = pcVar13;
    } while (cVar1 != '\0');
    uVar6 = ~uVar6;
    pcVar5 = pcVar13 + -uVar6;
    pcVar13 = local_b6;
    for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
      *(undefined4 *)pcVar13 = *(undefined4 *)pcVar5;
      pcVar5 = pcVar5 + 4;
      pcVar13 = pcVar13 + 4;
    }
    for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *pcVar13 = *pcVar5;
      pcVar5 = pcVar5 + 1;
      pcVar13 = pcVar13 + 1;
    }
    pcVar5 = s_null_1004ce60;
  }
  else {
    strncpy(&DAT_100589da + *(int *)(DAT_100c5ad8 + 0x38) * 0x8c4,(char *)(*piVar10 + 0x3b),0xd);
    uVar6 = 0xffffffff;
    pcVar5 = (char *)(*piVar10 + 0x3b);
    do {
      pcVar13 = pcVar5;
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      pcVar13 = pcVar5 + 1;
      cVar1 = *pcVar5;
      pcVar5 = pcVar13;
    } while (cVar1 != '\0');
    uVar6 = ~uVar6;
    pcVar5 = pcVar13 + -uVar6;
    pcVar13 = local_b6;
    for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
      *(undefined4 *)pcVar13 = *(undefined4 *)pcVar5;
      pcVar5 = pcVar5 + 4;
      pcVar13 = pcVar13 + 4;
    }
    for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *pcVar13 = *pcVar5;
      pcVar5 = pcVar5 + 1;
      pcVar13 = pcVar13 + 1;
    }
    iVar8 = 1;
    bVar14 = true;
    pcVar5 = &DAT_100589e7 + *(int *)(DAT_100c5ad8 + 0x38) * 0x8c4;
    pcVar13 = &DAT_100f530c;
    do {
      if (iVar8 == 0) break;
      iVar8 = iVar8 + -1;
      bVar14 = *pcVar5 == *pcVar13;
      pcVar5 = pcVar5 + 1;
      pcVar13 = pcVar13 + 1;
    } while (bVar14);
    if (bVar14) {
      uVar6 = 0xffffffff;
      pcVar5 = s_null_1004ce50;
      do {
        pcVar13 = pcVar5;
        if (uVar6 == 0) break;
        uVar6 = uVar6 - 1;
        pcVar13 = pcVar5 + 1;
        cVar1 = *pcVar5;
        pcVar5 = pcVar13;
      } while (cVar1 != '\0');
      uVar6 = ~uVar6;
      pcVar5 = pcVar13 + -uVar6;
      pcVar13 = local_a9;
      for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
        *(undefined4 *)pcVar13 = *(undefined4 *)pcVar5;
        pcVar5 = pcVar5 + 4;
        pcVar13 = pcVar13 + 4;
      }
      for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
        *pcVar13 = *pcVar5;
        pcVar5 = pcVar5 + 1;
        pcVar13 = pcVar13 + 1;
      }
      goto LAB_100354d0;
    }
    piVar10 = *(int **)(piVar2[2] + 8);
    strncpy(&DAT_100589e7 + *(int *)(DAT_100c5ad8 + 0x38) * 0x8c4,(char *)(*piVar10 + 0x3b),0xd);
    pcVar5 = (char *)(*piVar10 + 0x3b);
  }
  uVar6 = 0xffffffff;
  do {
    pcVar13 = pcVar5;
    if (uVar6 == 0) break;
    uVar6 = uVar6 - 1;
    pcVar13 = pcVar5 + 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar13;
  } while (cVar1 != '\0');
  uVar6 = ~uVar6;
  pcVar5 = pcVar13 + -uVar6;
  pcVar13 = local_a9;
  for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
    *(undefined4 *)pcVar13 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcVar13 = pcVar13 + 4;
  }
  for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
    *pcVar13 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar13 = pcVar13 + 1;
  }
LAB_100354d0:
  piVar10 = *(int **)(piVar2[2] + 8);
  if (piVar10 == (int *)0x0) {
    uVar6 = 0xffffffff;
    pcVar5 = s_null_1004ce68;
    do {
      pcVar13 = pcVar5;
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      pcVar13 = pcVar5 + 1;
      cVar1 = *pcVar5;
      pcVar5 = pcVar13;
    } while (cVar1 != '\0');
    uVar6 = ~uVar6;
    pcVar5 = pcVar13 + -uVar6;
    pcVar13 = local_9c;
    for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
      *(undefined4 *)pcVar13 = *(undefined4 *)pcVar5;
      pcVar5 = pcVar5 + 4;
      pcVar13 = pcVar13 + 4;
    }
    for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *pcVar13 = *pcVar5;
      pcVar5 = pcVar5 + 1;
      pcVar13 = pcVar13 + 1;
    }
  }
  else {
    strncpy(&DAT_100589f4 + *(int *)(DAT_100c5ad8 + 0x38) * 0x8c4,(char *)(*piVar10 + 0x3b),0xd);
    uVar6 = 0xffffffff;
    pcVar5 = (char *)(*piVar10 + 0x3b);
    do {
      pcVar13 = pcVar5;
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      pcVar13 = pcVar5 + 1;
      cVar1 = *pcVar5;
      pcVar5 = pcVar13;
    } while (cVar1 != '\0');
    uVar6 = ~uVar6;
    pcVar5 = pcVar13 + -uVar6;
    pcVar13 = local_9c;
    for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
      *(undefined4 *)pcVar13 = *(undefined4 *)pcVar5;
      pcVar5 = pcVar5 + 4;
      pcVar13 = pcVar13 + 4;
    }
    for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *pcVar13 = *pcVar5;
      pcVar5 = pcVar5 + 1;
      pcVar13 = pcVar13 + 1;
    }
  }
  iVar8 = *(int *)(DAT_100c5ad8 + 0x38) * 0x8c4;
  local_8f = *(undefined4 *)(&DAT_1005899c + *(int *)(DAT_100c5ad8 + 0x38) * 0x8c4);
  local_87 = *(undefined4 *)(&DAT_100589a0 + iVar8);
  local_8b = *(undefined4 *)(&DAT_100589a4 + iVar8);
  local_83 = *(undefined4 *)(&DAT_100589a8 + iVar8);
  iVar8 = *(int *)(DAT_100c5ad8 + 0x38) * 0x8c4;
  local_7f = *(undefined4 *)(&DAT_100589ac + iVar8);
  local_77 = *(undefined4 *)(&DAT_100589b0 + iVar8);
  local_7b = *(undefined4 *)(&DAT_100589b4 + iVar8);
  local_73 = *(undefined4 *)(&DAT_100589b8 + iVar8);
  local_6f = *(undefined4 *)(&DAT_100589bc + *(int *)(DAT_100c5ad8 + 0x38) * 0x8c4);
  clear_pointer_list(piVar2);
  populate_matching_vehicle_part_selection_list(is_special_equipment_part_type,piVar2,DAT_100d1db4);
  iVar8 = 0;
  local_fc = 0;
  local_100 = 0;
  if (0 < piVar2[1]) {
    local_104 = local_64;
    do {
      piVar10 = *(int **)(piVar2[2] + local_fc * 4);
      if (piVar10 != (int *)0x0) {
        iVar9 = 5;
        bVar14 = true;
        pcVar5 = (char *)(*piVar10 + 0x2e);
        pcVar13 = s_null_1004ce70;
        do {
          if (iVar9 == 0) break;
          iVar9 = iVar9 + -1;
          bVar14 = *pcVar5 == *pcVar13;
          pcVar5 = pcVar5 + 1;
          pcVar13 = pcVar13 + 1;
        } while (bVar14);
        if (!bVar14) {
          if (iVar8 < 0x1e) {
            iVar11 = iVar8 * 0x1e;
            iVar9 = iVar8;
            do {
              iVar8 = _stricmp((char *)*piVar10,
                               &DAT_100585a0 + *(int *)(DAT_100c5ad8 + 0x38) * 0x8c4 + iVar11);
              if (iVar8 == 0) {
                iVar8 = iVar9 + 1;
                uVar4 = *(undefined4 *)
                         (&DAT_10058924 + (iVar9 + *(int *)(DAT_100c5ad8 + 0x38) * 0x231) * 4);
                local_100 = iVar8;
                goto LAB_100356d3;
              }
              iVar11 = iVar11 + 0x1e;
              iVar9 = iVar9 + 1;
              iVar8 = local_100;
            } while (iVar11 < 900);
          }
          uVar4 = 0;
LAB_100356d3:
          *(undefined4 *)(local_104 + -4) = uVar4;
          uVar6 = 0xffffffff;
          pcVar5 = (char *)(*piVar10 + 0x3b);
          do {
            pcVar13 = pcVar5;
            if (uVar6 == 0) break;
            uVar6 = uVar6 - 1;
            pcVar13 = pcVar5 + 1;
            cVar1 = *pcVar5;
            pcVar5 = pcVar13;
          } while (cVar1 != '\0');
          uVar6 = ~uVar6;
          pcVar5 = pcVar13 + -uVar6;
          pcVar13 = local_104;
          for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
            *(undefined4 *)pcVar13 = *(undefined4 *)pcVar5;
            pcVar5 = pcVar5 + 4;
            pcVar13 = pcVar13 + 4;
          }
          for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
            *pcVar13 = *pcVar5;
            pcVar5 = pcVar5 + 1;
            pcVar13 = pcVar13 + 1;
          }
          local_10c = local_10c + 1;
          local_104 = local_104 + 0x11;
        }
      }
      local_fc = local_fc + 1;
    } while (local_fc < piVar2[1]);
  }
  iVar8 = _stricmp(&DAT_100589c0 + *(int *)(DAT_100c5ad8 + 0x38) * 0x8c4,s_vstank_vdf_1004ce78);
  if (iVar8 == 0) {
    if (local_10c < 2) {
      local_10c = local_10c + 1;
    }
    else if (local_10c == 2) {
      uVar6 = 0xffffffff;
      local_46 = local_57;
      pcVar5 = local_53;
      do {
        pcVar13 = pcVar5;
        if (uVar6 == 0) break;
        uVar6 = uVar6 - 1;
        pcVar13 = pcVar5 + 1;
        cVar1 = *pcVar5;
        pcVar5 = pcVar13;
      } while (cVar1 != '\0');
      uVar6 = ~uVar6;
      local_10c = 3;
      pcVar5 = pcVar13 + -uVar6;
      pcVar13 = local_42;
      for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
        *(undefined4 *)pcVar13 = *(undefined4 *)pcVar5;
        pcVar5 = pcVar5 + 4;
        pcVar13 = pcVar13 + 4;
      }
      for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
        *pcVar13 = *pcVar5;
        pcVar5 = pcVar5 + 1;
        pcVar13 = pcVar13 + 1;
      }
    }
    uVar6 = 0xffffffff;
    pcVar5 = &DAT_1004ce84;
    do {
      pcVar13 = pcVar5;
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      pcVar13 = pcVar5 + 1;
      cVar1 = *pcVar5;
      pcVar5 = pcVar13;
    } while (cVar1 != '\0');
    uVar6 = ~uVar6;
    local_57 = 1;
    pcVar5 = pcVar13 + -uVar6;
    pcVar13 = local_53;
    for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
      *(undefined4 *)pcVar13 = *(undefined4 *)pcVar5;
      pcVar5 = pcVar5 + 4;
      pcVar13 = pcVar13 + 4;
    }
    for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *pcVar13 = *pcVar5;
      pcVar5 = pcVar5 + 1;
      pcVar13 = pcVar13 + 1;
    }
  }
  clear_pointer_list(piVar2);
  populate_matching_vehicle_part_selection_list(&LAB_10034360,piVar2,DAT_100d1db0);
  iVar8 = 0;
  do {
    if (*(int **)(iVar8 + piVar2[2]) == (int *)0x0) {
LAB_10035859:
      *(undefined4 *)((int)local_f8 + iVar8) = 0;
    }
    else {
      iVar9 = **(int **)(iVar8 + piVar2[2]);
      iVar11 = 5;
      bVar14 = true;
      pcVar5 = (char *)(iVar9 + 0x2e);
      pcVar13 = s_null_1004ce90;
      do {
        if (iVar11 == 0) break;
        iVar11 = iVar11 + -1;
        bVar14 = *pcVar5 == *pcVar13;
        pcVar5 = pcVar5 + 1;
        pcVar13 = pcVar13 + 1;
      } while (bVar14);
      if (bVar14) goto LAB_10035859;
      iVar11 = 1;
      bVar14 = true;
      pcVar5 = (char *)(iVar9 + 0x2e);
      pcVar13 = &DAT_100f5310;
      do {
        if (iVar11 == 0) break;
        iVar11 = iVar11 + -1;
        bVar14 = *pcVar5 == *pcVar13;
        pcVar5 = pcVar5 + 1;
        pcVar13 = pcVar13 + 1;
      } while (bVar14);
      if (bVar14) {
        pcVar5 = (char *)(iVar9 + 0x3e);
      }
      else {
        pcVar5 = (char *)(iVar9 + 0x31);
      }
      iVar9 = atoi(pcVar5);
      *(int *)((int)local_f8 + iVar8) = iVar9;
    }
    iVar8 = iVar8 + 4;
    if (0xb < iVar8) {
      (**(code **)(DAT_10058198 + 0x20))(param_1,local_f8 + 3,local_68,local_10c,local_f8);
      if (param_2 == 0) {
        cVar1 = *param_1;
        pcVar5 = param_1;
        while ((cVar1 != '\0' && (cVar1 != '\\'))) {
          pcVar13 = pcVar5 + 1;
          pcVar5 = pcVar5 + 1;
          cVar1 = *pcVar13;
        }
        if (*pcVar5 == '\\') {
          param_1 = pcVar5 + 1;
        }
        (**(code **)(DAT_10058198 + 8))(param_1,s_addon_1004ce98);
      }
      else {
        (**(code **)(DAT_10058198 + 8))(param_2,&DAT_100c5b04);
      }
      clear_pointer_list(piVar2);
      destroy_pointer_list_with_optional_item_destructor(piVar2,(undefined *)0x0);
      return;
    }
  } while( true );
}


