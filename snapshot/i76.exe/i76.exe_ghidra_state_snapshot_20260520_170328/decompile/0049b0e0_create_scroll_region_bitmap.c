/*
 * Program: i76.exe
 * Function: create_scroll_region_bitmap
 * Entry: 0049b0e0
 * Signature: undefined4 __cdecl create_scroll_region_bitmap(undefined4 * param_1)
 */


/* cgpt whole-binary semantic rename v1: string evidence cannot create bitmap for scroll region */

undefined4 __cdecl create_scroll_region_bitmap(undefined4 *param_1)

{
  int *piVar1;
  undefined4 *lpMem;
  int *piVar2;
  undefined4 *puVar3;
  uint uVar4;
  int iVar5;
  int *piVar6;
  int local_34 [13];
  
  lpMem = HeapAlloc(g_runtime_text_overlay_heap,0,0x98);
  if (lpMem[0x11] == 1) {
    param_1[0x10] = param_1[0x10] | 0x10;
  }
  *lpMem = *param_1;
  lpMem[1] = param_1[1];
  uVar4 = param_1[2];
  if (0x4f < uVar4) {
    uVar4 = 0x4f;
  }
  lpMem[0x12] = uVar4;
  lpMem[0x11] = param_1[3];
  lpMem[0x23] = param_1[0xf];
  lpMem[0x18] = param_1[0xe];
  lpMem[0x1a] = 0xffffffff;
  lpMem[0x24] = 0xbf800000;
  lpMem[0x25] = param_1[0x10];
  lpMem[0x18] = param_1[0xe];
  lpMem[0x19] = 0xffffffff;
  iVar5 = DAT_005a7d88;
  lpMem[0x14] = 0;
  lpMem[0x13] = iVar5;
  lpMem[0x16] = 0;
  lpMem[2] = DAT_005a7d80 * uVar4;
  if ((*(byte *)(param_1 + 0x10) & 0x10) == 0) {
    lpMem[3] = DAT_005a7d88 * lpMem[0x11];
  }
  else {
    lpMem[3] = DAT_005a7d88;
  }
  piVar1 = lpMem + 4;
  piVar2 = (int *)construct_bitmap_surface_context(local_34,lpMem[2],lpMem[3],0,0);
  piVar6 = piVar1;
  for (iVar5 = 0xd; iVar5 != 0; iVar5 = iVar5 + -1) {
    *piVar6 = *piVar2;
    piVar2 = piVar2 + 1;
    piVar6 = piVar6 + 1;
  }
  if (*piVar1 == 0) {
    report_error();
    HeapFree(g_runtime_text_overlay_heap,0,lpMem);
    return 0;
  }
  fill_bitmap_surface_context(piVar1,0xff);
  if ((*(byte *)(lpMem + 0x25) & 8) == 0) {
    lpMem[0x15] = lpMem[0x11];
  }
  else {
    lpMem[0x15] = 0;
  }
  puVar3 = HeapAlloc(g_runtime_text_overlay_heap,0,(lpMem[0x11] + 5) * 0x54);
  lpMem[0x17] = puVar3;
  for (uVar4 = (lpMem[0x11] + 5) * 0x15 & 0x3fffffff; uVar4 != 0; uVar4 = uVar4 - 1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  for (iVar5 = 0; iVar5 != 0; iVar5 = iVar5 + -1) {
    *(undefined1 *)puVar3 = 0;
    puVar3 = (undefined4 *)((int)puVar3 + 1);
  }
  g_scrolling_status_overlay_list =
       allocate_linked_list_node_3field
                 (g_scrolling_status_overlay_list,(undefined4 *)0x0,(int)lpMem);
  return g_scrolling_status_overlay_list;
}


