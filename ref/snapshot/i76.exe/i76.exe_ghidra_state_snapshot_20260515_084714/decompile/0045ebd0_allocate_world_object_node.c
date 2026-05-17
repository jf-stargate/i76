/*
 * Program: i76.exe
 * Function: allocate_world_object_node
 * Entry: 0045ebd0
 * Signature: LPVOID __cdecl allocate_world_object_node(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe geometry/texture rename v8; confidence=high] Allocates and initializes a 0xb0-byte
   world object node; with non-null parent inserts as child/sibling, otherwise initializes root
   object list. */

LPVOID __cdecl allocate_world_object_node(int param_1)

{
  LPVOID pvVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  pvVar1 = HeapAlloc(g_world_object_node_heap,8,0xb0);
  if (pvVar1 == (LPVOID)0x0) {
    return (LPVOID)0x0;
  }
  *(undefined4 *)((int)pvVar1 + 0x14) = 0xffffffff;
  *(undefined4 *)((int)pvVar1 + 0x58) = 0xffffffff;
  *(undefined4 *)((int)pvVar1 + 0x84) = 0;
  *(undefined4 *)((int)pvVar1 + 0x88) = 0;
  *(undefined4 *)((int)pvVar1 + 0x8c) = 0;
  *(undefined2 *)((int)pvVar1 + 8) = 0;
  *(undefined4 *)((int)pvVar1 + 0x10) = 0;
  *(undefined4 *)((int)pvVar1 + 0xa0) = 0;
  *(undefined4 *)((int)pvVar1 + 100) = 0;
  *(undefined4 *)((int)pvVar1 + 0x60) = 0;
  *(undefined4 *)((int)pvVar1 + 0x68) = 0;
  *(undefined4 *)((int)pvVar1 + 0xa4) = 0;
  *(undefined4 *)((int)pvVar1 + 0x5c) = 0;
  *(undefined4 *)((int)pvVar1 + 0x6c) = 0;
  *(undefined4 *)((int)pvVar1 + 0x70) = 0;
  *(undefined4 *)((int)pvVar1 + 0xa8) = 0;
  *(undefined4 *)((int)pvVar1 + 0x78) = 0;
  *(undefined4 *)((int)pvVar1 + 0x74) = 0;
  *(undefined4 *)((int)pvVar1 + 0x94) = 0;
  *(undefined4 *)((int)pvVar1 + 0x7c) = 0;
  *(undefined4 *)((int)pvVar1 + 0x80) = 0;
  *(undefined4 *)((int)pvVar1 + 0x98) = 0;
  *(undefined4 *)((int)pvVar1 + 0x90) = 0;
  *(undefined4 *)((int)pvVar1 + 0x9c) = 0;
  puVar3 = &DAT_004faed8;
  puVar4 = (undefined4 *)((int)pvVar1 + 0x18);
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  if (param_1 != 0) {
    if (*(int *)(param_1 + 100) != 0) {
      *(LPVOID *)(*(int *)(param_1 + 100) + 0x68) = pvVar1;
      *(undefined4 *)((int)pvVar1 + 0x60) = *(undefined4 *)(param_1 + 100);
    }
    *(int *)((int)pvVar1 + 0x68) = param_1;
    *(LPVOID *)(param_1 + 100) = pvVar1;
    *(undefined2 *)((int)pvVar1 + 8) = *(undefined2 *)(param_1 + 8);
    *(undefined4 *)((int)pvVar1 + 0xc) = *(undefined4 *)(param_1 + 0xc);
    return pvVar1;
  }
  _DAT_0054ad2c = pvVar1;
  _DAT_0054ad30 = pvVar1;
  *(undefined4 *)((int)pvVar1 + 0xc) = 1;
  return pvVar1;
}


