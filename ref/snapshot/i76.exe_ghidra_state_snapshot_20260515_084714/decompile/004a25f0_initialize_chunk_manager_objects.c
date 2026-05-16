/*
 * Program: i76.exe
 * Function: initialize_chunk_manager_objects
 * Entry: 004a25f0
 * Signature: uint __stdcall initialize_chunk_manager_objects(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: creates heap/table and default .geo chunk objects */

uint initialize_chunk_manager_objects(void)

{
  undefined4 uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  uint uVar6;
  int iVar7;
  uint *puVar8;
  uint uVar9;
  uint uVar10;
  undefined4 *puVar11;
  undefined4 *puVar12;
  undefined8 uVar13;
  int iVar14;
  int iVar15;
  uint local_18;
  uint local_14;
  uint local_10;
  uint local_c;
  uint local_4;
  
  DAT_005aab04 = HeapCreate(0,0,0);
  puVar11 = &DAT_005aaad0;
  for (iVar7 = 0xd; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar11 = 0;
    puVar11 = puVar11 + 1;
  }
  local_18 = DAT_004f7d2c;
  local_14 = DAT_004f7d30;
  uVar4 = create_vehicle_child_object_and_copy_ids(0,&local_18);
  iVar14 = 0;
  puVar11 = &DAT_004faed8;
  puVar12 = (undefined4 *)(uVar4 + 0x18);
  for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar12 = *puVar11;
    puVar11 = puVar11 + 1;
    puVar12 = puVar12 + 1;
  }
  *(undefined4 *)(uVar4 + 0x10) = 0;
  *(undefined4 *)(uVar4 + 0x90) = 0x3f800000;
  *(undefined4 *)(uVar4 + 0x5c) = 0;
  iVar7 = 0;
  pcVar5 = format_8char_resource_basename_with_suffix(DAT_004f7d2c,DAT_004f7d30,s__geo_004fe724);
  cache_add_entry(uVar4,pcVar5,iVar7,iVar14);
  uVar9 = DAT_004f7d2c;
  local_4 = DAT_004f7d30;
  local_10 = DAT_004f7d2c;
  local_c = DAT_004f7d30;
  uVar10 = 0;
  do {
    iVar7 = toupper((int)*(char *)((int)&local_10 + uVar10));
    *(char *)((int)&local_10 + uVar10) = (char)iVar7;
    uVar3 = local_c;
    uVar2 = local_10;
    uVar10 = uVar10 + 1;
  } while (uVar10 < 8);
  uVar13 = __allshr(0x20,local_c);
  for (puVar8 = (uint *)(&DAT_005aaad0)
                        [((((uint)uVar13 ^ uVar2) & 0xdfdfdfdf) * 0x6cd + 0xaab) % 0xd];
      puVar8 != (uint *)0x0; puVar8 = (uint *)puVar8[4]) {
    if ((*puVar8 == uVar2) && (puVar8[1] == uVar3)) goto LAB_004a2708;
  }
  puVar8 = (uint *)0x0;
LAB_004a2708:
  if (puVar8 == (uint *)0x0) {
    puVar8 = HeapAlloc(DAT_005aab04,0,0x18);
    if (puVar8 != (uint *)0x0) {
      *puVar8 = uVar9;
      puVar8[1] = local_4;
      uVar13 = __allshr(0x20,local_4);
      uVar9 = ((((uint)uVar13 ^ uVar9) & 0xdfdfdfdf) * 0x6cd + 0xaab) % 0xd;
      puVar8[4] = (&DAT_005aaad0)[uVar9];
      (&DAT_005aaad0)[uVar9] = puVar8;
    }
    puVar8[2] = uVar4;
    puVar8[3] = 0x40a00000;
  }
  local_18 = DAT_004f7d24;
  local_14 = DAT_004f7d28;
  uVar4 = create_vehicle_child_object_and_copy_ids(0,&local_18);
  puVar11 = &DAT_004faed8;
  puVar12 = (undefined4 *)(uVar4 + 0x18);
  for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar12 = *puVar11;
    puVar11 = puVar11 + 1;
    puVar12 = puVar12 + 1;
  }
  uVar10 = 0;
  *(undefined4 *)(uVar4 + 0x90) = 0x3f800000;
  *(undefined4 *)(uVar4 + 0x10) = 0;
  *(undefined4 *)(uVar4 + 0x5c) = 0;
  iVar14 = 0;
  iVar7 = 0;
  pcVar5 = format_8char_resource_basename_with_suffix(DAT_004f7d24,DAT_004f7d28,s__geo_004fe724);
  cache_add_entry(uVar4,pcVar5,iVar7,iVar14);
  uVar9 = DAT_004f7d24;
  local_4 = DAT_004f7d28;
  local_10 = DAT_004f7d24;
  local_c = DAT_004f7d28;
  do {
    iVar7 = toupper((int)*(char *)((int)&local_10 + uVar10));
    *(char *)((int)&local_10 + uVar10) = (char)iVar7;
    uVar3 = local_c;
    uVar2 = local_10;
    uVar10 = uVar10 + 1;
  } while (uVar10 < 8);
  uVar13 = __allshr(0x20,local_c);
  for (puVar8 = (uint *)(&DAT_005aaad0)
                        [((((uint)uVar13 ^ uVar2) & 0xdfdfdfdf) * 0x6cd + 0xaab) % 0xd];
      puVar8 != (uint *)0x0; puVar8 = (uint *)puVar8[4]) {
    if ((*puVar8 == uVar2) && (puVar8[1] == uVar3)) goto LAB_004a286a;
  }
  puVar8 = (uint *)0x0;
LAB_004a286a:
  if (puVar8 == (uint *)0x0) {
    puVar8 = HeapAlloc(DAT_005aab04,0,0x18);
    if (puVar8 != (uint *)0x0) {
      *puVar8 = uVar9;
      puVar8[1] = local_4;
      uVar13 = __allshr(0x20,local_4);
      uVar9 = ((((uint)uVar13 ^ uVar9) & 0xdfdfdfdf) * 0x6cd + 0xaab) % 0xd;
      puVar8[4] = (&DAT_005aaad0)[uVar9];
      (&DAT_005aaad0)[uVar9] = puVar8;
    }
    puVar8[2] = uVar4;
    puVar8[3] = 0x40a00000;
  }
  local_18._0_1_ = s_CHUNK4_004f8160[0];
  local_18._1_1_ = s_CHUNK4_004f8160[1];
  local_18._2_1_ = s_CHUNK4_004f8160[2];
  local_18._3_1_ = s_CHUNK4_004f8160[3];
  local_14 = ram0x004f8164;
  iVar7 = create_vehicle_child_object_and_copy_ids(0,&local_18);
  puVar11 = &DAT_004faed8;
  puVar12 = (undefined4 *)(iVar7 + 0x18);
  for (iVar14 = 0x10; iVar14 != 0; iVar14 = iVar14 + -1) {
    *puVar12 = *puVar11;
    puVar11 = puVar11 + 1;
    puVar12 = puVar12 + 1;
  }
  uVar4 = 0;
  *(undefined4 *)(iVar7 + 0x90) = 0x3f800000;
  *(undefined4 *)(iVar7 + 0x10) = 0;
  *(undefined4 *)(iVar7 + 0x5c) = 0;
  iVar15 = 0;
  iVar14 = 0;
  pcVar5 = format_8char_resource_basename_with_suffix
                     (s_CHUNK4_004f8160._0_4_,ram0x004f8164,s__geo_004fe724);
  cache_add_entry(iVar7,pcVar5,iVar14,iVar15);
  uVar1 = s_CHUNK4_004f8160._0_4_;
  local_4 = ram0x004f8164;
  local_10._0_1_ = s_CHUNK4_004f8160[0];
  local_10._1_1_ = s_CHUNK4_004f8160[1];
  local_10._2_1_ = s_CHUNK4_004f8160[2];
  local_10._3_1_ = s_CHUNK4_004f8160[3];
  local_c = ram0x004f8164;
  do {
    iVar14 = toupper((int)*(char *)((int)&local_10 + uVar4));
    *(char *)((int)&local_10 + uVar4) = (char)iVar14;
    uVar10 = local_c;
    uVar9 = local_10;
    uVar4 = uVar4 + 1;
  } while (uVar4 < 8);
  uVar13 = __allshr(0x20,local_c);
  for (puVar8 = (uint *)(&DAT_005aaad0)
                        [((((uint)uVar13 ^ uVar9) & 0xdfdfdfdf) * 0x6cd + 0xaab) % 0xd];
      puVar8 != (uint *)0x0; puVar8 = (uint *)puVar8[4]) {
    if ((*puVar8 == uVar9) && (puVar8[1] == uVar10)) goto LAB_004a29cc;
  }
  puVar8 = (uint *)0x0;
LAB_004a29cc:
  if (puVar8 == (uint *)0x0) {
    pcVar5 = HeapAlloc(DAT_005aab04,0,0x18);
    if (pcVar5 != (char *)0x0) {
      *(undefined4 *)pcVar5 = uVar1;
      *(uint *)(pcVar5 + 4) = local_4;
      uVar13 = __allshr(0x20,local_4);
      uVar4 = ((((uint)uVar13 ^ uVar1) & 0xdfdfdfdf) * 0x6cd + 0xaab) % 0xd;
      *(undefined4 *)(pcVar5 + 0x10) = (&DAT_005aaad0)[uVar4];
      (&DAT_005aaad0)[uVar4] = pcVar5;
    }
    *(int *)(pcVar5 + 8) = iVar7;
    pcVar5[0xc] = '\0';
    pcVar5[0xd] = '\0';
    pcVar5[0xe] = -0x60;
    pcVar5[0xf] = '@';
  }
  local_18 = DAT_004f89d0;
  local_14 = DAT_004f89d4;
  uVar4 = create_vehicle_child_object_and_copy_ids(0,&local_18);
  puVar11 = &DAT_004faed8;
  puVar12 = (undefined4 *)(uVar4 + 0x18);
  for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar12 = *puVar11;
    puVar11 = puVar11 + 1;
    puVar12 = puVar12 + 1;
  }
  uVar10 = 0;
  *(undefined4 *)(uVar4 + 0x90) = 0x3f800000;
  *(undefined4 *)(uVar4 + 0x10) = 0;
  *(undefined4 *)(uVar4 + 0x5c) = 0;
  iVar14 = 0;
  iVar7 = 0;
  pcVar5 = format_8char_resource_basename_with_suffix(DAT_004f89d0,DAT_004f89d4,s__geo_004fe724);
  cache_add_entry(uVar4,pcVar5,iVar7,iVar14);
  uVar9 = DAT_004f89d0;
  local_4 = DAT_004f89d4;
  local_10 = DAT_004f89d0;
  local_c = DAT_004f89d4;
  do {
    iVar7 = toupper((int)*(char *)((int)&local_10 + uVar10));
    *(char *)((int)&local_10 + uVar10) = (char)iVar7;
    uVar3 = local_c;
    uVar2 = local_10;
    uVar10 = uVar10 + 1;
  } while (uVar10 < 8);
  uVar13 = __allshr(0x20,local_c);
  uVar10 = (((uint)uVar13 ^ uVar2) & 0xdfdfdfdf) * 0x6cd + 0xaab;
  uVar6 = uVar10 / 0xd;
  for (puVar8 = (uint *)(&DAT_005aaad0)[uVar10 % 0xd]; puVar8 != (uint *)0x0;
      puVar8 = (uint *)puVar8[4]) {
    uVar6 = *puVar8;
    if ((uVar6 == uVar2) && (puVar8[1] == uVar3)) goto LAB_004a2b2e;
  }
  puVar8 = (uint *)0x0;
LAB_004a2b2e:
  if (puVar8 == (uint *)0x0) {
    puVar8 = HeapAlloc(DAT_005aab04,0,0x18);
    uVar6 = 0;
    if (puVar8 != (uint *)0x0) {
      *puVar8 = uVar9;
      puVar8[1] = local_4;
      uVar13 = __allshr(0x20,local_4);
      uVar9 = ((((uint)uVar13 ^ uVar9) & 0xdfdfdfdf) * 0x6cd + 0xaab) % 0xd;
      uVar6 = (&DAT_005aaad0)[uVar9];
      puVar8[4] = uVar6;
      (&DAT_005aaad0)[uVar9] = puVar8;
    }
    puVar8[2] = uVar4;
    puVar8[3] = 0x40a00000;
  }
  return uVar6;
}


