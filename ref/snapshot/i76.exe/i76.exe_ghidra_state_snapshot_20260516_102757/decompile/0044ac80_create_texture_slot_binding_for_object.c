/*
 * Program: i76.exe
 * Function: create_texture_slot_binding_for_object
 * Entry: 0044ac80
 * Signature: uint * __cdecl create_texture_slot_binding_for_object(uint param_1, byte * param_2, undefined4 param_3, uint param_4)
 */


/* [cgpt i76.exe GEO runtime/render renames v30; confidence=medium-high] Creates a per-object
   texture-slot binding record for a named slot and texture-set cache record. */

uint * __cdecl
create_texture_slot_binding_for_object(uint param_1,byte *param_2,undefined4 param_3,uint param_4)

{
  byte *pbVar1;
  byte bVar2;
  uint *puVar3;
  int iVar4;
  uint uVar5;
  uint *puVar6;
  
  puVar3 = HeapAlloc(g_texture_slot_binding_heap,0,0x48);
  if (puVar3 == (uint *)0x0) {
    return (uint *)0x0;
  }
  *puVar3 = param_1;
  strncpy((char *)(puVar3 + 5),(char *)param_2,0xf);
  puVar3[0xc] = param_4;
  iVar4 = 0;
  if (0 < *(int *)(param_4 + 0x1c)) {
    puVar6 = puVar3 + 9;
    do {
      *puVar6 = 0;
      iVar4 = iVar4 + 1;
      puVar6 = puVar6 + 1;
    } while (iVar4 < *(int *)(param_4 + 0x1c));
  }
  strncpy((char *)(puVar3 + 1),*(char **)(param_4 + 0x2c),0xf);
  puVar3[0xf] = 2;
  puVar3[0xd] = 0;
  puVar3[0xe] = 0;
  uVar5 = 0;
  bVar2 = *param_2;
  while (bVar2 != 0) {
    uVar5 = uVar5 * 2 ^ bVar2 & 0xdf;
    pbVar1 = param_2 + 1;
    param_2 = param_2 + 1;
    bVar2 = *pbVar1;
  }
  uVar5 = ((uVar5 ^ param_1) * 0x6cd + 0xaab) % 0x7ed;
  puVar3[0x10] = (&g_texture_slot_binding_hash)[uVar5];
  (&g_texture_slot_binding_hash)[uVar5] = puVar3;
  uVar5 = (param_1 * 0x6cd + 0xaab) % 0x71;
  puVar6 = (uint *)(&g_texture_bindings_by_object_hash)[uVar5];
  if (puVar6 != (uint *)0x0) {
    do {
      if (*puVar6 == param_1) break;
      puVar6 = (uint *)puVar6[2];
    } while (puVar6 != (uint *)0x0);
    if (puVar6 != (uint *)0x0) goto LAB_0044ada4;
  }
  puVar6 = HeapAlloc(g_texture_object_binding_list_heap,0,0xc);
  if (puVar6 == (uint *)0x0) {
    return puVar3;
  }
  puVar6[2] = (&g_texture_bindings_by_object_hash)[uVar5];
  (&g_texture_bindings_by_object_hash)[uVar5] = puVar6;
  *puVar6 = param_1;
  puVar6[1] = 0;
LAB_0044ada4:
  puVar3[0x11] = puVar6[1];
  puVar6[1] = (uint)puVar3;
  return puVar3;
}


