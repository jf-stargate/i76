/*
 * Program: i76.exe
 * Function: release_radar_context
 * Entry: 0045faf0
 * Signature: undefined __cdecl release_radar_context(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: string evidence: radar and HeapFree */

void __cdecl release_radar_context(int param_1)

{
  int iVar1;
  LPVOID pvVar2;
  uint uVar3;
  float fVar4;
  float fVar5;
  uint *puVar6;
  uint *puVar7;
  uint uVar8;
  bool bVar9;
  float fVar10;
  uint *puVar11;
  bool bVar12;
  int iVar13;
  int *piVar14;
  undefined3 extraout_var;
  LPVOID pvVar15;
  uint *puVar16;
  uint uVar17;
  float *pfVar18;
  undefined3 extraout_var_00;
  int *piVar19;
  uint *puVar20;
  undefined4 *puVar21;
  int iVar22;
  undefined4 *puVar23;
  float10 fVar24;
  undefined8 uVar25;
  float local_b0;
  uint *local_a8;
  float local_88;
  float local_84;
  float local_3c [3];
  undefined4 local_30 [3];
  float local_24 [3];
  float local_18 [3];
  float local_c [3];
  
  iVar1 = *(int *)(param_1 + 0x70);
  iVar22 = 0;
  bVar9 = false;
  *(uint *)(iVar1 + 0xc) = *(uint *)(iVar1 + 0xc) & 0xfffffff7;
  iVar13 = is_damage_side_effects_suppressed();
  if ((iVar13 == 0) && (iVar13 = get_active_player_or_camera_world_object_entry(), iVar13 != 0)) {
    iVar13 = *(int *)(iVar1 + 0x78);
    piVar14 = (int *)get_active_player_or_camera_world_object_entry();
    if (iVar13 != *piVar14) {
      radar_context_helper_0045f970(iVar13,iVar1);
      return;
    }
  }
  if (*(int *)(iVar1 + 0x78) != 0) {
    update_radar_contacts_for_vehicle_weapon_directions(*(int *)(iVar1 + 0x78));
    bVar12 = radar_render_context_helper_00461680(*(int *)(iVar1 + 0x78));
    iVar22 = CONCAT31(extraout_var,bVar12);
  }
  if ((((*(uint *)(iVar1 + 0xc) & 1) == 0) || (((byte)*(uint *)(iVar1 + 0xc) & 4) == 4)) ||
     (iVar22 == 1)) {
    pvVar2 = *(LPVOID *)(iVar1 + 4);
    while (pvVar2 != (LPVOID)0x0) {
      *(undefined4 *)(iVar1 + 4) = *(undefined4 *)((int)pvVar2 + 0x20);
      HeapFree(DAT_0054b1f8,0,pvVar2);
      pvVar2 = *(LPVOID *)(iVar1 + 4);
    }
    if (*(int *)(iVar1 + 0x54) != 0) {
      *(undefined1 *)(*(int *)(iVar1 + 0x54) + 0x1c) = 0x69;
    }
    uVar17 = *(uint *)(iVar1 + 0xc) & 0xffffffed;
    *(undefined4 *)(iVar1 + 0x54) = 0;
    *(uint *)(iVar1 + 0xc) = uVar17;
    puVar21 = &DAT_004faed8;
    puVar23 = (undefined4 *)(iVar1 + 0x10);
    for (iVar13 = 0x10; iVar13 != 0; iVar13 = iVar13 + -1) {
      *puVar23 = *puVar21;
      puVar21 = puVar21 + 1;
      puVar23 = puVar23 + 1;
    }
    *(undefined4 *)(iVar1 + 0x50) = 0;
    *(uint *)(iVar1 + 0xc) = uVar17 | 8;
    return;
  }
  local_a8 = *(uint **)(iVar1 + 4);
  *(undefined4 *)(iVar1 + 4) = 0;
  piVar14 = DAT_0054b1ec;
  do {
    while( true ) {
      if (piVar14 == (int *)0x0) {
        if (bVar9) {
          return;
        }
        if (*(int *)(iVar1 + 0x54) != 0) {
          *(undefined1 *)(*(int *)(iVar1 + 0x54) + 0x1c) = 0x69;
        }
        *(undefined4 *)(iVar1 + 0x54) = 0;
        *(uint *)(iVar1 + 0xc) = *(uint *)(iVar1 + 0xc) & 0xffffffed;
        puVar21 = &DAT_004faed8;
        puVar23 = (undefined4 *)(iVar1 + 0x10);
        for (iVar13 = 0x10; iVar13 != 0; iVar13 = iVar13 + -1) {
          *puVar23 = *puVar21;
          puVar21 = puVar21 + 1;
          puVar23 = puVar23 + 1;
        }
        *(undefined4 *)(iVar1 + 0x50) = 0;
        return;
      }
      bVar12 = false;
      pvVar2 = (LPVOID)piVar14[2];
      if (pvVar2 != *(LPVOID *)(iVar1 + 0x78)) break;
LAB_0045fe6b:
      piVar14 = (int *)*piVar14;
    }
    pvVar15 = release_world_object_tree_reference(pvVar2,s_radar_004f7694);
    for (puVar20 = local_a8; puVar20 != (uint *)0x0; puVar20 = (uint *)puVar20[8]) {
      if ((LPVOID)*puVar20 == pvVar2) goto LAB_0045fbe5;
    }
    puVar20 = (uint *)0x0;
LAB_0045fbe5:
    if (puVar20 == (uint *)0x0) {
      if ((*(byte *)(*(int *)(iVar1 + 0x78) + 0x10) & 0x20) == 0) {
        if ((pvVar15 != (LPVOID)0x0) &&
           (((*(int *)((int)pvVar2 + 0x6c) == 0x5a || (*(int *)((int)pvVar2 + 0x6c) == 0x5b)) ||
            (uVar17 = vehicle_damage_component_runtime_context_helper_00466de0((int)pvVar2),
            uVar17 != 0)))) {
          fVar10 = _DAT_004f760c;
          pfVar18 = (float *)compose_world_object_runtime_transform(local_24,*(int *)(iVar1 + 0x78))
          ;
          fVar4 = *pfVar18;
          fVar5 = pfVar18[2];
          pfVar18 = (float *)compose_world_object_runtime_transform(local_c,(int)pvVar2);
          if ((fVar5 - pfVar18[2]) * (fVar5 - pfVar18[2]) + (fVar4 - *pfVar18) * (fVar4 - *pfVar18)
              <= fVar10 * fVar10) {
            uVar17 = *(uint *)(iVar1 + 0x78);
            puVar20 = *(uint **)(iVar1 + 4);
            puVar16 = HeapAlloc(DAT_0054b1f8,0,0x24);
            if (puVar16 != (uint *)0x0) {
              *puVar16 = (uint)pvVar2;
              radar_render_context_helper_00460c80(puVar16,uVar17);
              *(undefined1 *)(puVar16 + 7) = 0x69;
              puVar11 = puVar20;
              puVar7 = (uint *)0x0;
              while ((puVar6 = puVar11, puVar6 != (uint *)0x0 &&
                     ((float)puVar6[5] <= (float)puVar16[5]))) {
                puVar7 = puVar6;
                puVar11 = (uint *)puVar6[8];
              }
              if (puVar7 == (uint *)0x0) {
                puVar16[8] = (uint)puVar20;
                puVar20 = puVar16;
              }
              else {
                puVar16[8] = puVar7[8];
                puVar7[8] = (uint)puVar16;
              }
            }
            *(uint **)(iVar1 + 4) = puVar20;
            if ((*(uint **)(iVar1 + 0x54) != (uint *)0x0) && (*(uint **)(iVar1 + 0x54) == puVar20))
            {
              *(undefined1 *)(puVar20 + 7) = 0xff;
            }
            bVar12 = true;
          }
        }
        if (pvVar15 == (LPVOID)0x0) {
          piVar19 = (int *)*piVar14;
          goto LAB_00460173;
        }
      }
LAB_0045fe46:
      if (((bVar12) && (iVar13 = is_vehicle_or_actor_runtime_world_object((int)pvVar2), iVar13 != 0)
          ) && (bVar12 = radar_render_context_helper_00461680((int)pvVar2),
               CONCAT31(extraout_var_00,bVar12) != 0)) {
        pvVar2 = *(LPVOID *)(iVar1 + 4);
        while (pvVar2 != (LPVOID)0x0) {
          *(undefined4 *)(iVar1 + 4) = *(undefined4 *)((int)pvVar2 + 0x20);
          HeapFree(DAT_0054b1f8,0,pvVar2);
          pvVar2 = *(LPVOID *)(iVar1 + 4);
        }
        if (*(int *)(iVar1 + 0x54) != 0) {
          *(undefined1 *)(*(int *)(iVar1 + 0x54) + 0x1c) = 0x69;
        }
        uVar17 = *(uint *)(iVar1 + 0xc) & 0xffffffed;
        *(uint *)(iVar1 + 0xc) = uVar17;
        *(undefined4 *)(iVar1 + 0x54) = 0;
        puVar21 = &DAT_004faed8;
        puVar23 = (undefined4 *)(iVar1 + 0x10);
        for (iVar13 = 0x10; iVar13 != 0; iVar13 = iVar13 + -1) {
          *puVar23 = *puVar21;
          puVar21 = puVar21 + 1;
          puVar23 = puVar23 + 1;
        }
        *(undefined4 *)(iVar1 + 0x50) = 0;
        *(uint *)(iVar1 + 0xc) = uVar17 | 8;
        return;
      }
      goto LAB_0045fe6b;
    }
    uVar17 = *(uint *)(iVar1 + 0x78);
    puVar16 = (uint *)world_object_geometry_context_helper_00458930(local_30,uVar17,*puVar20);
    uVar3 = puVar16[2];
    puVar20[1] = *puVar16;
    puVar20[2] = uVar3;
    fVar24 = (float10)world_object_geometry_context_helper_00458970(uVar17);
    local_b0 = (float)fVar24;
    if (fVar24 < (float10)_DAT_004be128) {
      local_b0 = local_b0 - _DAT_004be12c;
    }
    fVar4 = (float)puVar20[1];
    fVar5 = (float)puVar20[2];
    uVar25 = mission_flow_map_context_helper_0049d400(local_b0);
    local_84 = (float)((ulonglong)uVar25 >> 0x20);
    local_88 = (float)uVar25;
    puVar20[3] = (uint)(fVar4 * local_84 - fVar5 * local_88);
    puVar20[4] = (uint)(fVar4 * local_88 + fVar5 * local_84);
    fVar24 = (float10)world_object_geometry_context_helper_004589f0(uVar17,*puVar20);
    puVar20[5] = (uint)(float)fVar24;
    fVar24 = get_multiplayer_or_runtime_seconds();
    if ((float)puVar20[6] <= (float)fVar24) {
      fVar4 = (float)puVar20[6];
      while (fVar4 < (float)fVar24) {
        puVar20[6] = (uint)((float)puVar20[6] - _DAT_004be130);
        if ((byte)puVar20[7] < 0x69) {
          *(byte *)(puVar20 + 7) = (byte)puVar20[7] + 3;
        }
        fVar4 = (float)puVar20[6];
      }
    }
    if ((pvVar15 != (LPVOID)0x0) &&
       (((*(int *)((int)pvVar2 + 0x6c) == 0x5a || (*(int *)((int)pvVar2 + 0x6c) == 0x5b)) ||
        (uVar17 = vehicle_damage_component_runtime_context_helper_00466de0((int)pvVar2), uVar17 != 0
        )))) {
      fVar10 = _DAT_004f760c;
      pfVar18 = (float *)compose_world_object_runtime_transform(local_18,*(int *)(iVar1 + 0x78));
      fVar4 = *pfVar18;
      fVar5 = pfVar18[2];
      pfVar18 = (float *)compose_world_object_runtime_transform(local_3c,(int)pvVar2);
      if ((fVar5 - pfVar18[2]) * (fVar5 - pfVar18[2]) + (fVar4 - *pfVar18) * (fVar4 - *pfVar18) <=
          fVar10 * fVar10) {
        puVar16 = (uint *)0x0;
        puVar7 = local_a8;
        if (&stack0x00000000 != (undefined1 *)0xa8) {
          for (; puVar7 != (uint *)0x0; puVar7 = (uint *)puVar7[8]) {
            if (puVar7 == puVar20) {
              if (puVar16 == (uint *)0x0) {
                local_a8 = (uint *)puVar7[8];
              }
              else {
                puVar16[8] = puVar7[8];
              }
              break;
            }
            puVar16 = puVar7;
          }
        }
        uVar3 = *(uint *)(iVar1 + 4);
        uVar17 = 0;
        while ((uVar8 = uVar3, uVar8 != 0 && (*(float *)(uVar8 + 0x14) <= (float)puVar20[5]))) {
          uVar17 = uVar8;
          uVar3 = *(uint *)(uVar8 + 0x20);
        }
        if (uVar17 == 0) {
          puVar20[8] = *(uint *)(iVar1 + 4);
          *(uint **)(iVar1 + 4) = puVar20;
        }
        else {
          puVar20[8] = *(uint *)(uVar17 + 0x20);
          *(uint **)(uVar17 + 0x20) = puVar20;
        }
        if ((*(uint **)(iVar1 + 0x54) != (uint *)0x0) && (*(uint **)(iVar1 + 0x54) == puVar20)) {
          *(undefined1 *)(puVar20 + 7) = 0xff;
          bVar9 = true;
        }
        bVar12 = true;
        goto LAB_0045fe46;
      }
    }
    if ((((*(byte *)(*(int *)(iVar1 + 0x78) + 0x10) & 0x20) == 0) &&
        (puVar21 = *(undefined4 **)(iVar1 + 0x54), puVar21 != (undefined4 *)0x0)) &&
       ((LPVOID)*puVar21 == pvVar2)) {
      *(undefined1 *)(puVar21 + 7) = 0x69;
      *(uint *)(iVar1 + 0xc) = *(uint *)(iVar1 + 0xc) & 0xffffffed;
      *(undefined4 *)(iVar1 + 0x54) = 0;
      puVar21 = &DAT_004faed8;
      puVar23 = (undefined4 *)(iVar1 + 0x10);
      for (iVar13 = 0x10; iVar13 != 0; iVar13 = iVar13 + -1) {
        *puVar23 = *puVar21;
        puVar21 = puVar21 + 1;
        puVar23 = puVar23 + 1;
      }
      *(undefined4 *)(iVar1 + 0x50) = 0;
    }
    if (((*(byte *)(*(int *)(iVar1 + 0x78) + 0x10) & 0x20) != 0) && (pvVar15 != (LPVOID)0x0))
    goto LAB_0045fe46;
    puVar20 = (uint *)0x0;
    for (puVar16 = local_a8; puVar16 != (uint *)0x0; puVar16 = (uint *)puVar16[8]) {
      if ((LPVOID)*puVar16 == pvVar2) {
        if (puVar20 == (uint *)0x0) {
          local_a8 = (uint *)puVar16[8];
        }
        else {
          puVar20[8] = puVar16[8];
        }
        HeapFree(DAT_0054b1f8,0,puVar16);
        break;
      }
      puVar20 = puVar16;
    }
    if (pvVar15 != (LPVOID)0x0) goto LAB_0045fe46;
    piVar19 = (int *)*piVar14;
LAB_00460173:
    unlink_and_free_linked_list_node_3field((int *)&DAT_0054b1ec,piVar14);
    piVar14 = piVar19;
  } while( true );
}


