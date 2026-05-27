/*
 * Program: i76.exe
 * Function: cache_add_entry
 * Entry: 004461e0
 * Signature: undefined4 __cdecl cache_add_entry(int param_1, char * param_2, int param_3, int param_4)
 */


/* [cgpt i76.exe GEO runtime/render renames v30; confidence=medium-high] Adds a runtime cache record
   to a hash/cache table. */

undefined4 __cdecl cache_add_entry(int param_1,char *param_2,int param_3,int param_4)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  
  if (param_4 == 0 && param_3 == 0) {
    piVar1 = HeapAlloc(DAT_0052db9c,0,0x3c);
    piVar1[3] = -1;
    piVar1[4] = -1;
    *piVar1 = param_1;
    piVar1[1] = 0;
    piVar1[2] = 0;
    *(undefined1 *)(piVar1 + 5) = 0;
    *(undefined1 *)(piVar1 + 9) = 0;
    uVar5 = (param_1 * 0x6cd + 0xaabU) % 0x7ed;
    piVar1[0xe] = (&g_geometry_binding_hash)[uVar5];
    (&g_geometry_binding_hash)[uVar5] = piVar1;
    if (piVar1 == (int *)0x0) {
      report_error();
    }
    *piVar1 = param_1;
    puVar2 = HeapAlloc(DAT_0052dba0,0,0x74);
    piVar1[0xd] = (int)puVar2;
    for (iVar4 = 0x1d; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar2 = 0;
      puVar2 = puVar2 + 1;
    }
    iVar4 = piVar1[0xd];
  }
  else {
    for (piVar1 = (int *)(&g_geometry_binding_hash)[(param_1 * 0x6cd + 0xaabU) % 0x7ed];
        piVar1 != (int *)0x0; piVar1 = (int *)piVar1[0xe]) {
      if (*piVar1 == param_1) goto LAB_004462ca;
    }
    piVar1 = (int *)0x0;
LAB_004462ca:
    iVar4 = piVar1[0xd];
    if (0 < param_3) {
      iVar3 = param_3 + -1;
      if (0 < iVar3) {
        do {
          iVar4 = *(int *)(iVar4 + 0x70);
          iVar3 = iVar3 + -1;
        } while (iVar3 != 0);
      }
      if (*(int *)(iVar4 + 0x70) == 0) {
        puVar2 = HeapAlloc(DAT_0052dba0,0,0x74);
        *(undefined4 **)(iVar4 + 0x70) = puVar2;
        for (iVar3 = 0x1d; iVar3 != 0; iVar3 = iVar3 + -1) {
          *puVar2 = 0;
          puVar2 = puVar2 + 1;
        }
      }
      iVar4 = *(int *)(iVar4 + 0x70);
    }
  }
  if (param_2 != (char *)0x0) {
    strncpy((char *)(param_4 * 0x10 + iVar4),param_2,0xf);
  }
  return 1;
}


