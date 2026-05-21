/*
 * Program: i76shell.dll
 * Function: export_vehicle_scene_with_selected_parts
 * Entry: 10035930
 * Signature: undefined __cdecl export_vehicle_scene_with_selected_parts(char * param_1, int param_2, int param_3, int param_4, int param_5)
 */


void __cdecl
export_vehicle_scene_with_selected_parts
          (char *param_1,int param_2,int param_3,int param_4,int param_5)

{
  char cVar1;
  int *piVar2;
  int *piVar3;
  undefined **ppuVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  char *pcVar8;
  int iVar9;
  int *piVar10;
  int iVar11;
  char *pcVar12;
  bool bVar13;
  int local_d0;
  int local_cc;
  int local_c8;
  char local_c0 [13];
  undefined4 local_b3;
  undefined4 local_af;
  undefined4 local_ab;
  undefined4 local_a7;
  undefined4 local_a3;
  undefined4 local_9f;
  undefined4 local_9b;
  undefined4 local_97;
  undefined4 local_93;
  undefined4 local_8f;
  undefined4 local_8b;
  undefined4 local_87;
  undefined *local_83;
  undefined *local_7f;
  undefined *local_7b;
  undefined1 local_77;
  undefined1 local_76;
  undefined1 local_75;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  int local_58 [20];
  undefined4 local_8;
  undefined4 local_4;
  
  piVar3 = create_pointer_list_default_16();
  uVar6 = 0xffffffff;
  pcVar8 = s_vehscn_vcf_1004cea0;
  do {
    pcVar12 = pcVar8;
    if (uVar6 == 0) break;
    uVar6 = uVar6 - 1;
    pcVar12 = pcVar8 + 1;
    cVar1 = *pcVar8;
    pcVar8 = pcVar12;
  } while (cVar1 != '\0');
  uVar6 = ~uVar6;
  pcVar8 = pcVar12 + -uVar6;
  pcVar12 = local_c0;
  for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
    *(undefined4 *)pcVar12 = *(undefined4 *)pcVar8;
    pcVar8 = pcVar8 + 4;
    pcVar12 = pcVar12 + 4;
  }
  for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
    *pcVar12 = *pcVar8;
    pcVar8 = pcVar8 + 1;
    pcVar12 = pcVar12 + 1;
  }
  iVar9 = *(int *)(DAT_100c5ad8 + 0x38) * 0x8c4;
  local_b3 = *(undefined4 *)(&DAT_1005899c + *(int *)(DAT_100c5ad8 + 0x38) * 0x8c4);
  local_af = *(undefined4 *)(&DAT_100589a0 + iVar9);
  local_ab = *(undefined4 *)(&DAT_100589a4 + iVar9);
  local_a7 = *(undefined4 *)(&DAT_100589a8 + iVar9);
  local_93 = 0;
  local_8f = 0;
  local_8b = 0;
  local_87 = 0;
  iVar9 = *(int *)(DAT_100c5ad8 + 0x38) * 0x8c4;
  local_a3 = *(undefined4 *)(&DAT_100589ac + *(int *)(DAT_100c5ad8 + 0x38) * 0x8c4);
  local_9f = *(undefined4 *)(&DAT_100589b0 + iVar9);
  local_9b = *(undefined4 *)(&DAT_100589b4 + iVar9);
  local_97 = *(undefined4 *)(&DAT_100589b8 + iVar9);
  if (param_3 == 0) {
    ppuVar4 = find_current_vehicle_part_by_type_and_name(2,DAT_100d1dac);
  }
  else {
    ppuVar4 = (undefined **)**(undefined4 **)(param_3 + 8);
  }
  local_83 = ppuVar4[3];
  if (param_3 == 0) {
    ppuVar4 = find_current_vehicle_part_by_type_and_name(3,DAT_100d1dc0);
  }
  else {
    ppuVar4 = *(undefined ***)(*(int *)(param_3 + 8) + 4);
  }
  local_7b = ppuVar4[3];
  if (param_3 == 0) {
    ppuVar4 = find_current_vehicle_part_by_type_and_name(4,DAT_100d1dbc);
  }
  else {
    ppuVar4 = *(undefined ***)(*(int *)(param_3 + 8) + 8);
  }
  local_7f = ppuVar4[3];
  local_77 = 1;
  local_76 = 1;
  local_75 = 1;
  local_6c = 0xffffffff;
  local_68 = 0xffffffff;
  if (param_3 == 0) {
    populate_equipped_vehicle_part_selection_list(&LAB_10034350,(int)piVar3,DAT_100d1db8);
    if (piVar3[1] != 0) {
      local_74 = *(undefined4 *)(*(int *)piVar3[2] + 0xc);
      local_70 = *(undefined4 *)(*(int *)(piVar3[2] + 4) + 0xc);
      local_64 = *(undefined4 *)(*(int *)(piVar3[2] + 8) + 0xc);
      local_60 = *(undefined4 *)(*(int *)(piVar3[2] + 0xc) + 0xc);
    }
  }
  else {
    iVar9 = *(int *)(param_3 + 8);
    local_74 = *(undefined4 *)(*(int *)(iVar9 + 0xc) + 0xc);
    local_70 = *(undefined4 *)(*(int *)(iVar9 + 0x10) + 0xc);
    local_64 = *(undefined4 *)(*(int *)(iVar9 + 0x14) + 0xc);
    local_60 = *(undefined4 *)(*(int *)(iVar9 + 0x18) + 0xc);
  }
  if (param_4 == 0) {
    clear_pointer_list(piVar3);
    populate_matching_vehicle_part_selection_list
              (is_special_equipment_part_type,piVar3,DAT_100d1db4);
    iVar9 = 0;
    local_cc = 0;
    local_d0 = 0;
    local_c8 = 0;
    if (0 < piVar3[1]) {
      piVar10 = local_58;
      do {
        piVar2 = *(int **)(piVar3[2] + local_cc * 4);
        if (piVar2 == (int *)0x0) {
LAB_10035e1b:
          *piVar10 = -1;
        }
        else {
          iVar5 = 5;
          bVar13 = true;
          pcVar8 = (char *)(*piVar2 + 0x2e);
          pcVar12 = s_null_1004cebc;
          do {
            if (iVar5 == 0) break;
            iVar5 = iVar5 + -1;
            bVar13 = *pcVar8 == *pcVar12;
            pcVar8 = pcVar8 + 1;
            pcVar12 = pcVar12 + 1;
          } while (bVar13);
          if (bVar13) goto LAB_10035e1b;
          if (iVar9 < 0x1e) {
            iVar11 = iVar9 * 0x1e;
            iVar5 = iVar9;
            do {
              iVar9 = _stricmp((char *)*piVar2,
                               &DAT_100585a0 + *(int *)(DAT_100c5ad8 + 0x38) * 0x8c4 + iVar11);
              if (iVar9 == 0) {
                iVar9 = iVar5 + 1;
                iVar5 = *(int *)(&DAT_10058924 + (iVar5 + *(int *)(DAT_100c5ad8 + 0x38) * 0x231) * 4
                                );
                local_d0 = iVar9;
                goto LAB_10035e00;
              }
              iVar11 = iVar11 + 0x1e;
              iVar5 = iVar5 + 1;
              iVar9 = local_d0;
            } while (iVar11 < 900);
          }
          iVar5 = 0;
LAB_10035e00:
          piVar10[-1] = iVar5;
          *piVar10 = piVar2[3];
          local_c8 = local_c8 + 1;
          piVar10[1] = -1;
        }
        local_cc = local_cc + 1;
        piVar10 = piVar10 + 3;
      } while (local_cc < piVar3[1]);
    }
  }
  else {
    iVar5 = 0;
    iVar9 = 0;
    local_cc = 0;
    local_d0 = 0;
    local_c8 = 0;
    if (0 < *(int *)(param_4 + 4)) {
      piVar10 = local_58;
      do {
        piVar2 = *(int **)(*(int *)(param_4 + 8) + local_cc * 4);
        if (piVar2 == (int *)0x0) {
LAB_10035bef:
          *piVar10 = -1;
        }
        else {
          iVar5 = 5;
          bVar13 = true;
          pcVar8 = (char *)(*piVar2 + 0x2e);
          pcVar12 = s_null_1004ceac;
          do {
            if (iVar5 == 0) break;
            iVar5 = iVar5 + -1;
            bVar13 = *pcVar8 == *pcVar12;
            pcVar8 = pcVar8 + 1;
            pcVar12 = pcVar12 + 1;
          } while (bVar13);
          if (bVar13) goto LAB_10035bef;
          if (iVar9 < 0x1e) {
            iVar11 = iVar9 * 0x1e;
            iVar5 = iVar9;
            do {
              iVar9 = _stricmp((char *)*piVar2,
                               &DAT_100585a0 + *(int *)(DAT_100c5ad8 + 0x38) * 0x8c4 + iVar11);
              if (iVar9 == 0) {
                iVar9 = iVar5 + 1;
                iVar5 = *(int *)(&DAT_10058924 + (iVar5 + *(int *)(DAT_100c5ad8 + 0x38) * 0x231) * 4
                                );
                local_d0 = iVar9;
                goto LAB_10035bbe;
              }
              iVar11 = iVar11 + 0x1e;
              iVar5 = iVar5 + 1;
              iVar9 = local_d0;
            } while (iVar11 < 900);
          }
          iVar5 = 0;
LAB_10035bbe:
          piVar10[-1] = iVar5;
          *piVar10 = piVar2[3];
          piVar10[1] = -1;
          local_c8 = local_c8 + 1;
        }
        iVar5 = local_cc + 1;
        piVar10 = piVar10 + 3;
        local_cc = iVar5;
      } while (iVar5 < *(int *)(param_4 + 4));
    }
    local_cc = 0;
    if (0 < *(int *)(param_5 + 4)) {
      piVar10 = local_58 + iVar5 * 3;
      do {
        piVar2 = *(int **)(*(int *)(param_5 + 8) + local_cc * 4);
        if (piVar2 == (int *)0x0) {
LAB_10035ced:
          *piVar10 = -1;
        }
        else {
          iVar5 = 5;
          bVar13 = true;
          pcVar8 = (char *)(*piVar2 + 0x2e);
          pcVar12 = s_null_1004ceb4;
          do {
            if (iVar5 == 0) break;
            iVar5 = iVar5 + -1;
            bVar13 = *pcVar8 == *pcVar12;
            pcVar8 = pcVar8 + 1;
            pcVar12 = pcVar12 + 1;
          } while (bVar13);
          if (bVar13) goto LAB_10035ced;
          if (iVar9 < 0x1e) {
            iVar11 = iVar9 * 0x1e;
            iVar5 = iVar9;
            do {
              iVar9 = _stricmp((char *)*piVar2,
                               &DAT_100585a0 + *(int *)(DAT_100c5ad8 + 0x38) * 0x8c4 + iVar11);
              if (iVar9 == 0) {
                iVar9 = iVar5 + 1;
                iVar5 = *(int *)(&DAT_10058924 + (iVar5 + *(int *)(DAT_100c5ad8 + 0x38) * 0x231) * 4
                                );
                local_d0 = iVar9;
                goto LAB_10035cd2;
              }
              iVar11 = iVar11 + 0x1e;
              iVar5 = iVar5 + 1;
              iVar9 = local_d0;
            } while (iVar11 < 900);
          }
          iVar5 = 0;
LAB_10035cd2:
          piVar10[-1] = iVar5;
          *piVar10 = piVar2[3];
          local_c8 = local_c8 + 1;
          piVar10[1] = -1;
        }
        local_cc = local_cc + 1;
        piVar10 = piVar10 + 3;
      } while (local_cc < *(int *)(param_5 + 4));
    }
  }
  local_8 = 0;
  local_4 = *(undefined4 *)(&DAT_10058a04 + *(int *)(DAT_100c5ad8 + 0x38) * 0x8c4);
  (**(code **)(DAT_10058198 + 0x24))(param_1,local_c0,local_c8);
  if (param_2 == 0) {
    cVar1 = *param_1;
    pcVar8 = param_1;
    while ((cVar1 != '\0' && (cVar1 != '\\'))) {
      pcVar12 = pcVar8 + 1;
      pcVar8 = pcVar8 + 1;
      cVar1 = *pcVar12;
    }
    if (*pcVar8 == '\\') {
      param_1 = pcVar8 + 1;
    }
    (**(code **)(DAT_10058198 + 8))(param_1,s_addon_1004cec4);
  }
  else {
    (**(code **)(DAT_10058198 + 8))(param_2,&DAT_100c5b04);
  }
  clear_pointer_list(piVar3);
  destroy_pointer_list_with_optional_item_destructor(piVar3,(undefined *)0x0);
  return;
}


