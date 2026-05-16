/*
 * Program: i76.exe
 * Function: initialize_or_resize_runtime_text_overlay_buffers
 * Entry: 0049aee0
 * Signature: undefined __cdecl initialize_or_resize_runtime_text_overlay_buffers(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe runtime loop refinement v23; confidence=HIGH] Allocates/resizes runtime text/status
   overlay buffers and related display resources. */

void __cdecl initialize_or_resize_runtime_text_overlay_buffers(int param_1)

{
  ushort uVar1;
  undefined4 *puVar2;
  int iVar3;
  int *piVar4;
  undefined4 *puVar5;
  int iVar6;
  uint uVar7;
  int *piVar8;
  int local_44 [13];
  int *local_10;
  undefined4 local_c;
  uint *local_8;
  
  if (param_1 == 0) {
    g_scrolling_status_overlay_list = (undefined4 *)0x0;
    g_runtime_text_overlay_heap = HeapCreate(0,0,0);
  }
  iVar3 = 0x57;
  local_c = 0x57;
  if ((*DAT_00504c0c & 0x100) == 0) {
    if ((int)DAT_00504c0c[1] < 0x57) {
      iVar3 = 0x2a;
    }
    piVar4 = (int *)DAT_00504c0c[iVar3 + 0x83];
  }
  else {
    local_8 = DAT_00504c0c + 0x83;
    uVar1 = *(ushort *)(DAT_006547e4 + 0xae);
    if (uVar1 == 0) {
      uVar1 = 0x57;
    }
    piVar4 = (int *)local_8[uVar1];
    local_10 = piVar4;
  }
  DAT_005a7d80 = *piVar4;
  DAT_005a7d88 = 0xe;
  _DAT_005a7d8c = 0;
  _DAT_005a7d84 = 0;
  puVar2 = g_scrolling_status_overlay_list;
  if (param_1 != 0) {
    for (; puVar2 != (undefined4 *)0x0; puVar2 = (undefined4 *)*puVar2) {
      iVar3 = puVar2[2];
      *(undefined4 *)(iVar3 + 0x68) = 0xffffffff;
      *(undefined4 *)(iVar3 + 0x90) = 0xbf800000;
      *(undefined4 *)(iVar3 + 100) = 0xffffffff;
      *(int *)(iVar3 + 0x4c) = DAT_005a7d88;
      *(undefined4 *)(iVar3 + 0x50) = 0;
      *(undefined4 *)(iVar3 + 0x58) = 0;
      *(int *)(iVar3 + 8) = *(int *)(iVar3 + 0x48) * DAT_005a7d80;
      if ((*(byte *)(iVar3 + 0x94) & 0x10) == 0) {
        *(int *)(iVar3 + 0xc) = *(int *)(iVar3 + 0x44) * DAT_005a7d88;
      }
      else {
        *(int *)(iVar3 + 0xc) = DAT_005a7d88;
      }
      release_bitmap_surface_context((int *)(iVar3 + 0x10));
      piVar4 = (int *)construct_bitmap_surface_context
                                (local_44,*(int *)(iVar3 + 8),*(uint *)(iVar3 + 0xc),0,0);
      piVar8 = (int *)(iVar3 + 0x10);
      for (iVar6 = 0xd; iVar6 != 0; iVar6 = iVar6 + -1) {
        *piVar8 = *piVar4;
        piVar4 = piVar4 + 1;
        piVar8 = piVar8 + 1;
      }
      fill_bitmap_surface_context((int *)(iVar3 + 0x10),0xff);
      if ((*(byte *)(iVar3 + 0x94) & 8) == 0) {
        *(undefined4 *)(iVar3 + 0x54) = *(undefined4 *)(iVar3 + 0x44);
      }
      else {
        *(undefined4 *)(iVar3 + 0x54) = 0;
      }
      HeapFree(g_runtime_text_overlay_heap,0,*(LPVOID *)(iVar3 + 0x5c));
      puVar5 = HeapAlloc(g_runtime_text_overlay_heap,0,(*(int *)(iVar3 + 0x44) + 5) * 0x54);
      *(undefined4 **)(iVar3 + 0x5c) = puVar5;
      for (uVar7 = (*(int *)(iVar3 + 0x44) + 5) * 0x15 & 0x3fffffff; uVar7 != 0; uVar7 = uVar7 - 1)
      {
        *puVar5 = 0;
        puVar5 = puVar5 + 1;
      }
      for (iVar3 = 0; iVar3 != 0; iVar3 = iVar3 + -1) {
        *(undefined1 *)puVar5 = 0;
        puVar5 = (undefined4 *)((int)puVar5 + 1);
      }
    }
  }
  return;
}


