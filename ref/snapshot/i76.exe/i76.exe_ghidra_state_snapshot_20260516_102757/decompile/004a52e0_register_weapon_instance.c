/*
 * Program: i76.exe
 * Function: register_weapon_instance
 * Entry: 004a52e0
 * Signature: int __cdecl register_weapon_instance(int param_1, int param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: string evidence cannot register weapon with no POF object
    */

int __cdecl register_weapon_instance(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  LPVOID pvVar6;
  float *pfVar7;
  uint uVar8;
  int iVar9;
  int *piVar10;
  int iVar11;
  undefined4 *puVar12;
  undefined4 *puVar13;
  float *pfVar14;
  float local_80 [6];
  float local_68;
  float local_64;
  float local_60;
  float local_40 [6];
  float local_28;
  float local_24;
  float local_20;
  
  iVar9 = g_weapon_runtime_slot_count;
  if (g_weapon_runtime_slot_count < 0x41a) {
    iVar4 = 0;
    if (0 < g_loaded_vehicle_runtime_count) {
      piVar10 = &g_loaded_vehicle_runtime_table;
      do {
        if (*piVar10 == *(int *)(param_1 + 0xac)) goto LAB_004a532c;
        iVar4 = iVar4 + 1;
        piVar10 = piVar10 + 0xb2;
      } while (iVar4 < g_loaded_vehicle_runtime_count);
    }
    iVar4 = -1;
LAB_004a532c:
    iVar1 = iVar4 * 0x2c8;
    puVar12 = &g_loaded_vehicle_runtime_table + iVar4 * 0xb2;
    iVar11 = 0;
    piVar10 = (int *)(&DAT_005be530 + iVar1);
    do {
      if (*piVar10 == *(int *)(param_1 + 0xa0)) goto LAB_004a5358;
      iVar11 = iVar11 + 1;
      piVar10 = piVar10 + 0x16;
    } while (iVar11 < 7);
    iVar11 = -1;
LAB_004a5358:
    if (iVar11 == -1) goto LAB_004a5820;
    iVar2 = g_weapon_runtime_slot_count * 0x4c;
    iVar3 = g_weapon_runtime_slot_count * 0x13;
    (&DAT_005aab0c)[g_weapon_runtime_slot_count * 0x13] = *(undefined4 *)(param_1 + 0xa4);
    (&DAT_005aab10)[iVar9 * 0x13] = *(undefined4 *)(param_1 + 0xa8);
    iVar5 = param_2 * 0xd8;
    (&DAT_005aab14)[iVar9 * 0x13] = *(undefined4 *)(&DAT_005d893c + iVar5);
    *(undefined4 *)(&DAT_005aab18 + iVar2) = *(undefined4 *)(&DAT_005d8938 + iVar5);
    *(undefined4 *)(&DAT_005aab1c + iVar2) = *(undefined4 *)(&DAT_005d893c + iVar5);
    if (*(uint *)(param_1 + 0x6c) < *(uint *)(param_1 + 0xb0)) {
      *(uint *)(&DAT_005aab28 + iVar2) = *(uint *)(param_1 + 0x6c);
    }
    else {
      *(uint *)(&DAT_005aab28 + iVar2) = *(uint *)(param_1 + 0xb0);
    }
    (&DAT_005aab38)[iVar9 * 0x13] = param_2;
    *(undefined4 *)(&DAT_005aab2c + iVar2) = 0;
    *(undefined4 *)(&DAT_005aab34 + iVar2) = 0;
    *(undefined4 *)(&DAT_005aab30 + iVar2) = 0;
    (&DAT_005aab20)[iVar9 * 0x13] = puVar12;
    (&DAT_005aab24)[iVar9 * 0x13] = iVar11;
    (&DAT_005be4dc)[iVar4 * 0xb2] = 0xffffffff;
    iVar5 = g_weapon_runtime_slot_count;
    *(undefined4 *)(&DAT_005aab44 + iVar2) = 0;
    *(undefined4 *)(&DAT_005aab48 + iVar2) = 0;
    *(undefined4 *)(&DAT_005aab50 + iVar2) = 0;
    iVar4 = (&DAT_005aab0c)[iVar9 * 0x13];
    (&g_weapon_runtime_slot_table)[iVar3] = iVar5;
    (&DAT_005aab3c)[iVar9 * 0x13] = 1;
    (&DAT_005aab40)[iVar9 * 0x13] = 1;
    if (puVar12[iVar11 * 0x16 + 0x19] == 2) {
      if ((puVar12[iVar11 * 0x16 + 0x18] != 1) ||
         (_DAT_004beb30 <= *(double *)(puVar12 + iVar11 * 0x16 + 0x24))) {
        if ((puVar12[iVar11 * 0x16 + 0x18] != 2) ||
           (*(double *)(puVar12 + iVar11 * 0x16 + 0x24) <= _DAT_004beb30)) goto LAB_004a5635;
        *(float *)(iVar4 + 0x30) = -*(float *)(iVar4 + 0x30);
        *(float *)(iVar4 + 0x34) = -*(float *)(iVar4 + 0x34);
        *(undefined4 *)(iVar4 + 0x38) = *(undefined4 *)(iVar4 + 0x38);
        *(float *)(iVar4 + 0x28) = --*(float *)(iVar4 + 0x28);
        *(float *)(iVar4 + 0x2c) = --*(float *)(iVar4 + 0x2c);
        *(float *)(iVar4 + 0x24) = -*(float *)(iVar4 + 0x24);
        *(float *)(iVar4 + 0x18) = -*(float *)(iVar4 + 0x18);
        *(float *)(iVar4 + 0x1c) = -*(float *)(iVar4 + 0x1c);
        *(float *)(iVar4 + 0x20) = -*(float *)(iVar4 + 0x20);
      }
      else {
        *(float *)(iVar4 + 0x30) = -*(float *)(iVar4 + 0x30);
        *(float *)(iVar4 + 0x34) = -*(float *)(iVar4 + 0x34);
        *(undefined4 *)(iVar4 + 0x38) = *(undefined4 *)(iVar4 + 0x38);
        *(float *)(iVar4 + 0x28) = --*(float *)(iVar4 + 0x28);
        *(float *)(iVar4 + 0x2c) = --*(float *)(iVar4 + 0x2c);
        *(float *)(iVar4 + 0x24) = -*(float *)(iVar4 + 0x24);
        *(float *)(iVar4 + 0x18) = -*(float *)(iVar4 + 0x18);
        *(float *)(iVar4 + 0x1c) = -*(float *)(iVar4 + 0x1c);
        *(float *)(iVar4 + 0x20) = -*(float *)(iVar4 + 0x20);
      }
      world_object_callback_table_entry_helper_0046ee40(iVar4,(undefined4 *)(iVar4 + 0x18));
    }
LAB_004a5635:
    if (puVar12[iVar11 * 0x16 + 0x19] == 3) {
      *(uint *)(&DAT_005be798 + iVar1) = *(uint *)(&DAT_005be798 + iVar1) | 4;
      *(undefined4 *)(&DAT_005aab4c + iVar2) = 4;
      iVar4 = 0;
      iVar9 = (&DAT_005aab10)[iVar9 * 0x13];
      do {
        iVar1 = *(int *)(iVar9 + 100);
        if (iVar1 == 0) break;
        if (*(int *)(iVar1 + 0x6c) == 0x3f) {
          iVar4 = iVar4 + 1;
        }
        iVar9 = iVar1;
      } while (iVar4 < 2);
      if ((1 < iVar4) && (pvVar6 = allocate_world_object_node(0), pvVar6 != (LPVOID)0x0)) {
        *(uint *)(*(int *)(iVar9 + 0x68) + 0x10) =
             *(uint *)(*(int *)(iVar9 + 0x68) + 0x10) | 0x200000;
        *(undefined4 *)((int)pvVar6 + 0x6c) = *(undefined4 *)(*(int *)(iVar9 + 0x68) + 0x6c);
        *(undefined4 *)((int)pvVar6 + 0x10) = *(undefined4 *)(*(int *)(iVar9 + 0x68) + 0x10);
        puVar12 = (undefined4 *)(*(int *)(iVar9 + 0x68) + 0x18);
        puVar13 = (undefined4 *)((int)pvVar6 + 0x18);
        for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
          *puVar13 = *puVar12;
          puVar12 = puVar12 + 1;
          puVar13 = puVar13 + 1;
        }
        *(uint *)((int)pvVar6 + 0x10) = *(uint *)((int)pvVar6 + 0x10) | 1;
        *(undefined4 *)((int)pvVar6 + 0x5c) = 0;
        puVar12 = &DAT_004faed8;
        puVar13 = (undefined4 *)((int)pvVar6 + 0x18);
        for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
          *puVar13 = *puVar12;
          puVar12 = puVar12 + 1;
          puVar13 = puVar13 + 1;
        }
        *(undefined4 *)((int)pvVar6 + 0x40) = *(undefined4 *)(iVar9 + 0x40);
        *(undefined4 *)((int)pvVar6 + 0x44) = *(undefined4 *)(iVar9 + 0x44);
        *(undefined4 *)((int)pvVar6 + 0x50) = *(undefined4 *)(iVar9 + 0x50);
        *(undefined4 *)((int)pvVar6 + 0x54) = *(undefined4 *)(iVar9 + 0x54);
        iVar4 = *(int *)(iVar9 + 0x68);
        *(undefined4 *)(iVar9 + 0x40) = 0;
        *(undefined4 *)(iVar9 + 0x50) = 0;
        *(undefined4 *)(iVar9 + 0x44) = 0;
        *(undefined4 *)(iVar9 + 0x54) = 0;
        radar_context_setup_helper_0045f310(iVar9);
        attach_world_object_as_first_child((int)pvVar6,iVar4);
        attach_world_object_as_first_child(iVar9,(int)pvVar6);
        *(undefined4 *)((int)pvVar6 + 0x5c) = 0;
      }
      goto LAB_004a5820;
    }
    if (iVar4 != 0) {
      pfVar7 = (float *)compute_transform_relative_to_ancestor(local_40,iVar4,0);
      pfVar14 = local_40;
      for (iVar9 = 0x10; iVar9 != 0; iVar9 = iVar9 + -1) {
        *pfVar14 = *pfVar7;
        pfVar7 = pfVar7 + 1;
        pfVar14 = pfVar14 + 1;
      }
      pfVar7 = (float *)compute_transform_relative_to_ancestor(local_80,*(int *)(param_1 + 0xac),0);
      pfVar14 = local_80;
      for (iVar9 = 0x10; iVar9 != 0; iVar9 = iVar9 + -1) {
        *pfVar14 = *pfVar7;
        pfVar7 = pfVar7 + 1;
        pfVar14 = pfVar14 + 1;
      }
      if (puVar12[iVar11 * 0x16 + 0x19] == 6) {
        if (puVar12[iVar11 * 0x16 + 0x18] != 3) {
          *(uint *)(&DAT_005be798 + iVar1) = *(uint *)(&DAT_005be798 + iVar1) | 0x10;
          *(undefined4 *)(&DAT_005aab4c + iVar2) = 0x10;
          goto LAB_004a5820;
        }
        uVar8 = 8;
      }
      else {
        uVar8 = 1;
        if (local_60 * local_20 + local_64 * local_24 + local_68 * local_28 < _DAT_004beab8) {
          uVar8 = 2;
        }
      }
      *(uint *)(&DAT_005be798 + iVar1) = *(uint *)(&DAT_005be798 + iVar1) | uVar8;
      *(uint *)(&DAT_005aab4c + iVar2) = uVar8;
      goto LAB_004a5820;
    }
  }
  report_chunk_parse_error();
LAB_004a5820:
  iVar9 = g_weapon_runtime_slot_count;
  g_weapon_runtime_slot_count = g_weapon_runtime_slot_count + 1;
  return iVar9;
}


