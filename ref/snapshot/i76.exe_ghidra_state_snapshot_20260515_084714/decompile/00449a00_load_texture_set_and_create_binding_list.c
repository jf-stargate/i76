/*
 * Program: i76.exe
 * Function: load_texture_set_and_create_binding_list
 * Entry: 00449a00
 * Signature: LPVOID __cdecl load_texture_set_and_create_binding_list(byte * param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe image payload renames v27; confidence=high] Loads a texture set, creates object
   texture bindings, and installs texture animation state as needed. */

LPVOID __cdecl load_texture_set_and_create_binding_list(byte *param_1)

{
  byte *pbVar1;
  byte bVar2;
  code *pcVar3;
  uint uVar4;
  int iVar5;
  char *pcVar6;
  uint *puVar7;
  LPVOID pvVar8;
  int *piVar9;
  undefined4 *puVar10;
  byte *pbVar11;
  code *pcVar12;
  
  if (param_1 == (byte *)0x0) {
    return (LPVOID)0x0;
  }
  uVar4 = 0;
  bVar2 = *param_1;
  pbVar11 = param_1;
  while (bVar2 != 0) {
    uVar4 = uVar4 * 2 ^ bVar2 & 0xdf;
    pbVar1 = pbVar11 + 1;
    pbVar11 = pbVar11 + 1;
    bVar2 = *pbVar1;
  }
  pcVar6 = (char *)(&g_texture_set_cache_hash)[(uVar4 * 0x6cd + 0xaab) % 0x7ed];
  pcVar12 = _stricmp_exref;
  while ((pcVar3 = _stricmp_exref, _stricmp_exref = pcVar3, pcVar6 != (char *)0x0 &&
         (iVar5 = _stricmp(pcVar6,(char *)param_1), pcVar12 = pcVar3, iVar5 != 0))) {
    pcVar6 = *(char **)(pcVar6 + 0x30);
  }
  if (pcVar6 == (char *)0x0) {
    pcVar6 = strchr((char *)param_1,0x2e);
    if (pcVar6 == (char *)0x0) {
      iVar5 = 0;
    }
    else {
      iVar5 = (*pcVar12)(pcVar6,&DAT_004f25e8);
    }
    if (iVar5 == 0) {
      pbVar11 = HeapAlloc(g_texture_set_cache_heap,0,0x34);
      iVar5 = 0;
      if (pbVar11 != (byte *)0x0) {
        strncpy((char *)pbVar11,(char *)param_1,0xf);
        pbVar11[0x10] = 1;
        pbVar11[0x11] = 0;
        pbVar11[0x12] = 0;
        pbVar11[0x13] = 0;
        pbVar11[0x1c] = 1;
        pbVar11[0x1d] = 0;
        pbVar11[0x1e] = 0;
        pbVar11[0x1f] = 0;
        pbVar11[0x20] = 1;
        pbVar11[0x21] = 0;
        pbVar11[0x22] = 0;
        pbVar11[0x23] = 0;
        pcVar6 = HeapAlloc(g_texture_name_array_heap,0,0x10);
        *(char **)(pbVar11 + 0x2c) = pcVar6;
        strncpy(pcVar6,(char *)param_1,0xf);
        uVar4 = hash_texture_set_name_mod_0x7ed(pbVar11);
        *(undefined4 *)(pbVar11 + 0x30) = (&g_texture_set_cache_hash)[uVar4];
        (&g_texture_set_cache_hash)[uVar4] = pbVar11;
        iVar5 = 1;
        pcVar12 = _stricmp_exref;
      }
    }
    else {
      puVar7 = open_resource_file_into_memory((char *)param_1);
      iVar5 = 0;
      if (puVar7 != (uint *)0x0) {
        strncpy((char *)(puVar7 + 1),(char *)param_1,0xf);
        iVar5 = register_texture_set_cache_record_from_header((int)puVar7);
        release_resource_file_reference((char *)param_1);
      }
    }
    if (iVar5 == 0) {
      pcVar6 = (char *)0x0;
    }
    else {
      uVar4 = hash_texture_set_name_mod_0x7ed(param_1);
      pcVar6 = (char *)(&g_texture_set_cache_hash)[uVar4];
      while ((pcVar6 != (char *)0x0 && (iVar5 = (*pcVar12)(pcVar6,param_1), iVar5 != 0))) {
        pcVar6 = *(char **)(pcVar6 + 0x30);
      }
    }
  }
  else {
    *(int *)(pcVar6 + 0x10) = *(int *)(pcVar6 + 0x10) + 1;
  }
  if (pcVar6 == (char *)0x0) {
    return (LPVOID)0x0;
  }
  pvVar8 = HeapAlloc(g_texture_slot_binding_heap,0,0x48);
  if (pvVar8 == (LPVOID)0x0) goto LAB_00449ca7;
  *(LPVOID *)pvVar8 = pvVar8;
  strncpy((char *)((int)pvVar8 + 0x14),(char *)param_1,0xf);
  *(char **)((int)pvVar8 + 0x30) = pcVar6;
  iVar5 = 0;
  if (0 < *(int *)(pcVar6 + 0x1c)) {
    puVar10 = (undefined4 *)((int)pvVar8 + 0x24);
    do {
      *puVar10 = 0;
      iVar5 = iVar5 + 1;
      puVar10 = puVar10 + 1;
    } while (iVar5 < *(int *)(pcVar6 + 0x1c));
  }
  strncpy((char *)((int)pvVar8 + 4),*(char **)(pcVar6 + 0x2c),0xf);
  uVar4 = 0;
  *(undefined4 *)((int)pvVar8 + 0x3c) = 2;
  *(undefined4 *)((int)pvVar8 + 0x34) = 0;
  *(undefined4 *)((int)pvVar8 + 0x38) = 0;
  bVar2 = *param_1;
  pbVar11 = param_1;
  while (bVar2 != 0) {
    uVar4 = uVar4 * 2 ^ bVar2 & 0xdf;
    pbVar1 = pbVar11 + 1;
    pbVar11 = pbVar11 + 1;
    bVar2 = *pbVar1;
  }
  uVar4 = ((uVar4 ^ (uint)pvVar8) * 0x6cd + 0xaab) % 0x7ed;
  *(undefined4 *)((int)pvVar8 + 0x40) = (&g_texture_slot_binding_hash)[uVar4];
  (&g_texture_slot_binding_hash)[uVar4] = pvVar8;
  uVar4 = ((int)pvVar8 * 0x6cd + 0xaabU) % 0x71;
  piVar9 = (int *)(&g_texture_bindings_by_object_hash)[uVar4];
  if (piVar9 == (int *)0x0) {
LAB_00449c6f:
    piVar9 = HeapAlloc(g_texture_object_binding_list_heap,0,0xc);
    if (piVar9 == (int *)0x0) goto LAB_00449ca7;
    piVar9[2] = (&g_texture_bindings_by_object_hash)[uVar4];
    (&g_texture_bindings_by_object_hash)[uVar4] = piVar9;
    *piVar9 = (int)pvVar8;
    piVar9[1] = 0;
  }
  else {
    do {
      if ((LPVOID)*piVar9 == pvVar8) break;
      piVar9 = (int *)piVar9[2];
    } while (piVar9 != (int *)0x0);
    if (piVar9 == (int *)0x0) goto LAB_00449c6f;
  }
  *(int *)((int)pvVar8 + 0x44) = piVar9[1];
  piVar9[1] = (int)pvVar8;
LAB_00449ca7:
  if (pvVar8 == (LPVOID)0x0) {
    return (LPVOID)0x0;
  }
  if ((*(uint *)(pcVar6 + 0x18) & 1) != 0) {
    if ((*(uint *)(pcVar6 + 0x18) & 2) != 0) {
      install_texture_animation_pingpong_timer
                ((uint)pvVar8,param_1,_DAT_004bd3bc / *(float *)(pcVar6 + 0x14),0.0,
                 *(float *)(pcVar6 + 0x20),1);
      return pvVar8;
    }
    install_texture_animation_linear_timer
              ((uint)pvVar8,param_1,_DAT_004bd3bc / *(float *)(pcVar6 + 0x14),0.0,
               *(float *)(pcVar6 + 0x20),6.307143e-39);
  }
  return pvVar8;
}


