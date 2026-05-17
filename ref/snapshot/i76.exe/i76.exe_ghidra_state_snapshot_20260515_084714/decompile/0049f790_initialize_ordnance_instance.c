/*
 * Program: i76.exe
 * Function: initialize_ordnance_instance
 * Entry: 0049f790
 * Signature: undefined __cdecl initialize_ordnance_instance(int * param_1)
 */


/* cgpt whole-binary semantic rename v1: string evidence Ordinance %d */

void __cdecl initialize_ordnance_instance(int *param_1)

{
  int iVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  undefined3 extraout_var;
  LPVOID pvVar5;
  int *piVar6;
  HANDLE pvVar7;
  char *_Source;
  uint uVar8;
  uint uVar9;
  int iVar10;
  int *piVar11;
  int iVar12;
  undefined4 uVar13;
  undefined4 *puVar14;
  int *piVar15;
  undefined4 *puVar16;
  char local_50 [80];
  
  iVar3 = find_selected_mission_runtime_index(*param_1);
  iVar1 = DAT_005a810c;
  if (iVar3 == -1) {
    iVar10 = DAT_005a810c * 0xd0;
    piVar11 = &g_mission_runtime_vehicle_table + DAT_005a810c * 0x34;
    *piVar11 = *param_1;
    (&DAT_00655284)[iVar1 * 0x34] = param_1[1];
    iVar4 = 0;
    iVar3 = 0;
    do {
      if (iVar4 != 0) break;
      iVar12 = iVar3 + 1;
      bVar2 = ensure_world_object_geometry_variant_binding(param_1[1],iVar3);
      iVar4 = CONCAT31(extraout_var,bVar2);
      iVar3 = iVar12;
    } while (iVar12 < 6);
    (&DAT_006552bc)[iVar1 * 0x34] = iVar4;
    pvVar5 = allocate_world_object_node(0);
    *(undefined4 *)((int)pvVar5 + 0x6c) = 0x33;
    *(undefined4 *)((int)pvVar5 + 0x70) = 0;
    *(undefined4 *)((int)pvVar5 + 0x60) = 0;
    *(undefined4 *)((int)pvVar5 + 100) = 0;
    *(undefined4 *)((int)pvVar5 + 0x10) = 0x101;
    (&DAT_0065528c)[iVar1 * 0x34] = pvVar5;
    (&DAT_00655290)[iVar1 * 0x34] = 0;
    (&DAT_00655294)[iVar1 * 0x34] = 0;
    piVar6 = register_active_world_object_entry((int)pvVar5,0,(int *)0x0);
    (&DAT_00655288)[iVar1 * 0x34] = piVar6;
    (&DAT_0065529c)[iVar1 * 0x34] = 0x32;
    (&DAT_006552a0)[iVar1 * 0x34] = 0;
    (&DAT_006552a4)[iVar1 * 0x34] = 0;
    (&DAT_006552a8)[iVar1 * 0x34] = 0;
    uVar13 = 0xa0;
    iVar3 = is_damage_side_effects_suppressed();
    if ((iVar3 != 0) &&
       ((((iVar3 = *piVar11, iVar3 == 0xe || (iVar3 == 0xf)) || (iVar3 == 0x10)) || (iVar3 == 0x11))
       )) {
      uVar13 = 0x28;
    }
    (&DAT_006552ac)[iVar1 * 0x34] = uVar13;
    (&DAT_006552b0)[iVar1 * 0x34] = 0xa0;
    sprintf(local_50,s_Ordinance__d_004fe6f8,*param_1);
    pvVar7 = HeapCreate(0,0,0);
    (&DAT_00655298)[iVar1 * 0x34] = pvVar7;
    (&DAT_006552b4)[iVar1 * 0x34] = param_1[2];
    (&DAT_006552b8)[iVar1 * 0x34] = param_1[3];
    (&DAT_006552d8)[iVar1 * 0x34] = param_1[6];
    iVar3 = *piVar11;
    (&DAT_006552dc)[iVar1 * 0x34] = param_1[7];
    (&DAT_006552e4)[iVar1 * 0x34] = param_1[8];
    (&DAT_006552c0)[iVar1 * 0x34] = 0;
    (&DAT_006552e0)[iVar1 * 0x34] = 0xffffffff;
    switch(iVar3) {
    case 2:
      (&DAT_006552c0)[iVar1 * 0x34] = 1;
      (&DAT_006552e0)[iVar1 * 0x34] = 0;
      break;
    case 3:
      (&DAT_006552c0)[iVar1 * 0x34] = 1;
      (&DAT_006552e0)[iVar1 * 0x34] = 1;
      break;
    case 4:
      (&DAT_006552c0)[iVar1 * 0x34] = 1;
      (&DAT_006552e0)[iVar1 * 0x34] = 3;
      break;
    case 5:
      (&DAT_006552c0)[iVar1 * 0x34] = 1;
      (&DAT_006552e0)[iVar1 * 0x34] = 5;
      break;
    case 6:
      (&DAT_006552e0)[iVar1 * 0x34] = 1;
      break;
    case 7:
      (&DAT_006552c0)[iVar1 * 0x34] = 1;
      (&DAT_006552e0)[iVar1 * 0x34] = 4;
      break;
    case 8:
    case 0x14:
      (&DAT_006552c0)[iVar1 * 0x34] = 1;
    case 1:
    case 0x12:
      (&DAT_006552e0)[iVar1 * 0x34] = 2;
      break;
    case 0x11:
    case 0x15:
      (&DAT_006552c0)[iVar1 * 0x34] = 1;
      break;
    case 0x16:
      (&DAT_006552e0)[iVar1 * 0x34] = 4;
    }
    (&DAT_006552c4)[iVar1 * 0x34] = 0;
    (&DAT_006552e8)[iVar1 * 0x34] = param_1[4];
    (&DAT_006552f0)[iVar1 * 0x34] = param_1[10];
    (&DAT_006552f4)[iVar1 * 0x34] = param_1[0xb];
    uVar8 = 0xffffffff;
    piVar6 = param_1 + 0xc;
    do {
      piVar15 = piVar6;
      if (uVar8 == 0) break;
      uVar8 = uVar8 - 1;
      piVar15 = (int *)((int)piVar6 + 1);
      iVar3 = *piVar6;
      piVar6 = piVar15;
    } while ((char)iVar3 != '\0');
    uVar8 = ~uVar8;
    puVar14 = (undefined4 *)((int)piVar15 - uVar8);
    puVar16 = (undefined4 *)(&DAT_006552f8 + iVar10);
    for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
      *puVar16 = *puVar14;
      puVar14 = puVar14 + 1;
      puVar16 = puVar16 + 1;
    }
    for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
      *(undefined1 *)puVar16 = *(undefined1 *)puVar14;
      puVar14 = (undefined4 *)((int)puVar14 + 1);
      puVar16 = (undefined4 *)((int)puVar16 + 1);
    }
    (&DAT_00655308)[iVar1 * 0x34] = param_1[0x10];
    uVar8 = 0xffffffff;
    (&DAT_0065530c)[iVar1 * 0x34] = param_1[0x11];
    piVar6 = param_1 + 0x12;
    do {
      piVar15 = piVar6;
      if (uVar8 == 0) break;
      uVar8 = uVar8 - 1;
      piVar15 = (int *)((int)piVar6 + 1);
      iVar3 = *piVar6;
      piVar6 = piVar15;
    } while ((char)iVar3 != '\0');
    uVar8 = ~uVar8;
    puVar14 = (undefined4 *)((int)piVar15 - uVar8);
    puVar16 = (undefined4 *)(&DAT_00655310 + iVar10);
    for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
      *puVar16 = *puVar14;
      puVar14 = puVar14 + 1;
      puVar16 = puVar16 + 1;
    }
    for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
      *(undefined1 *)puVar16 = *(undefined1 *)puVar14;
      puVar14 = (undefined4 *)((int)puVar14 + 1);
      puVar16 = (undefined4 *)((int)puVar16 + 1);
    }
    (&DAT_00655320)[iVar1 * 0x34] = param_1[0x16];
    uVar8 = 0xffffffff;
    (&DAT_00655324)[iVar1 * 0x34] = param_1[0x17];
    piVar6 = param_1 + 0x18;
    do {
      piVar15 = piVar6;
      if (uVar8 == 0) break;
      uVar8 = uVar8 - 1;
      piVar15 = (int *)((int)piVar6 + 1);
      iVar3 = *piVar6;
      piVar6 = piVar15;
    } while ((char)iVar3 != '\0');
    uVar8 = ~uVar8;
    puVar14 = (undefined4 *)((int)piVar15 - uVar8);
    puVar16 = (undefined4 *)(&DAT_00655328 + iVar10);
    for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
      *puVar16 = *puVar14;
      puVar14 = puVar14 + 1;
      puVar16 = puVar16 + 1;
    }
    for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
      *(undefined1 *)puVar16 = *(undefined1 *)puVar14;
      puVar14 = (undefined4 *)((int)puVar14 + 1);
      puVar16 = (undefined4 *)((int)puVar16 + 1);
    }
    (&DAT_00655338)[iVar1 * 0x34] = param_1[0x1c];
    uVar8 = 0xffffffff;
    (&DAT_0065533c)[iVar1 * 0x34] = param_1[0x1d];
    piVar6 = param_1 + 0x1e;
    do {
      piVar15 = piVar6;
      if (uVar8 == 0) break;
      uVar8 = uVar8 - 1;
      piVar15 = (int *)((int)piVar6 + 1);
      iVar3 = *piVar6;
      piVar6 = piVar15;
    } while ((char)iVar3 != '\0');
    uVar8 = ~uVar8;
    puVar14 = (undefined4 *)((int)piVar15 - uVar8);
    puVar16 = (undefined4 *)(&DAT_00655340 + iVar10);
    for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
      *puVar16 = *puVar14;
      puVar14 = puVar14 + 1;
      puVar16 = puVar16 + 1;
    }
    for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
      *(undefined1 *)puVar16 = *(undefined1 *)puVar14;
      puVar14 = (undefined4 *)((int)puVar14 + 1);
      puVar16 = (undefined4 *)((int)puVar16 + 1);
    }
    iVar3 = *piVar11;
    if (((iVar3 == 0x11) || (iVar3 == 0xc)) ||
       ((iVar3 == 0xe || ((iVar3 == 0x15 || (iVar3 == 0xd)))))) {
      _Source = (char *)find_object_texture_slot_name((&DAT_00655284)[iVar1 * 0x34],0);
      if ((_Source == (char *)0x0) || (*_Source == '\0')) {
        (&DAT_006552c8)[iVar1 * 0x34] = 0;
        (&DAT_006552cc)[iVar1 * 0x34] = 0;
        (&DAT_006552d0)[iVar1 * 0x34] = 0;
        (&DAT_006552d4)[iVar1 * 0x34] = 0;
        (&DAT_006552c4)[iVar1 * 0x34] = 0;
      }
      else {
        strncpy((char *)(&DAT_006552c8 + iVar1 * 0x34),_Source,0x10);
        (&DAT_006552c4)[iVar1 * 0x34] = 1;
      }
    }
    DAT_005a810c = DAT_005a810c + 1;
    *(undefined4 *)((&DAT_00655288)[iVar1 * 0x34] + 0x10) = 0x3f800000;
    *(undefined4 *)((&DAT_00655288)[iVar1 * 0x34] + 0x14) = 3;
  }
  return;
}


