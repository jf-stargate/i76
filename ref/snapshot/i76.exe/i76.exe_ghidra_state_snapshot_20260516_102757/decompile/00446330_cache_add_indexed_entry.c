/*
 * Program: i76.exe
 * Function: cache_add_indexed_entry
 * Entry: 00446330
 * Signature: undefined4 __cdecl cache_add_indexed_entry(int param_1, int param_2)
 */


/* i76 first-pass rename
   old_name: FUN_00446330
   suggested_name: cache_add_indexed_entry
   basis: Generic cache insertion variant/indexed add helper. */

undefined4 __cdecl cache_add_indexed_entry(int param_1,int param_2)

{
  void *_Src;
  int *piVar1;
  void *_Dst;
  LPVOID pvVar2;
  int iVar3;
  uint uVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  int *local_4;
  
  for (local_4 = (int *)(&g_geometry_binding_hash)[(param_1 * 0x6cd + 0xaabU) % 0x7ed];
      local_4 != (int *)0x0; local_4 = (int *)local_4[0xe]) {
    if (*local_4 == param_1) goto LAB_0044637a;
  }
  local_4 = (int *)0x0;
LAB_0044637a:
  if (local_4 == (int *)0x0) {
    return 0;
  }
  piVar1 = HeapAlloc(DAT_0052db9c,0,0x3c);
  piVar1[1] = 0;
  piVar1[2] = 0;
  *piVar1 = param_2;
  piVar1[3] = -1;
  piVar1[4] = -1;
  *(undefined1 *)(piVar1 + 5) = 0;
  *(undefined1 *)(piVar1 + 9) = 0;
  uVar4 = (param_2 * 0x6cd + 0xaabU) % 0x7ed;
  piVar1[0xe] = (&g_geometry_binding_hash)[uVar4];
  (&g_geometry_binding_hash)[uVar4] = piVar1;
  if (piVar1 == (int *)0x0) {
    report_chunk_parse_error();
  }
  *piVar1 = param_2;
  _Dst = HeapAlloc(DAT_0052dba0,0,0x74);
  piVar1[0xd] = (int)_Dst;
  _Src = (void *)local_4[0xd];
  while (_Src != (void *)0x0) {
    memmove(_Dst,_Src,0x70);
    _Src = *(void **)((int)_Src + 0x70);
    if (_Src == (void *)0x0) break;
    pvVar2 = HeapAlloc(DAT_0052dba0,0,0x74);
    *(LPVOID *)((int)_Dst + 0x70) = pvVar2;
    _Dst = pvVar2;
  }
  *(undefined4 *)((int)_Dst + 0x70) = 0;
  *(undefined4 *)(param_2 + 0x84) = *(undefined4 *)(param_1 + 0x84);
  *(undefined4 *)(param_2 + 0x88) = *(undefined4 *)(param_1 + 0x88);
  *(undefined4 *)(param_2 + 0x8c) = *(undefined4 *)(param_1 + 0x8c);
  *(undefined4 *)(param_2 + 0x90) = *(undefined4 *)(param_1 + 0x90);
  puVar5 = (undefined4 *)(param_1 + 0x94);
  puVar6 = (undefined4 *)(param_2 + 0x94);
  for (iVar3 = 6; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar6 = *puVar5;
    puVar5 = puVar5 + 1;
    puVar6 = puVar6 + 1;
  }
  piVar1[3] = local_4[3];
  piVar1[2] = local_4[2];
  piVar1[4] = -1;
  strncpy((char *)(piVar1 + 5),(char *)(local_4 + 5),0xf);
  uVar4 = load_geometry_resource_into_cache((uint *)(piVar1 + 5));
  piVar1[1] = uVar4;
  *(uint *)(param_2 + 0x5c) = uVar4;
  return 1;
}


