/*
 * Program: i76.exe
 * Function: create_input_region_bitmap
 * Entry: 0049b800
 * Signature: undefined4 __cdecl create_input_region_bitmap(undefined4 * param_1)
 */


/* cgpt whole-binary semantic rename v1: string evidence cannot create bitmap for input region */

undefined4 __cdecl create_input_region_bitmap(undefined4 *param_1)

{
  undefined4 *lpMem;
  uint uVar1;
  int *piVar2;
  uint uVar3;
  undefined4 *puVar4;
  int iVar5;
  undefined4 *puVar6;
  int local_44 [13];
  undefined4 *local_10;
  int *local_c;
  undefined4 local_8;
  
  lpMem = HeapAlloc(DAT_005a7d9c,0,0xb8);
  *lpMem = *param_1;
  lpMem[1] = param_1[1];
  lpMem[2] = param_1[2];
  lpMem[0x2c] = param_1[0xf] | 0x200;
  lpMem[0x2a] = param_1[0xe];
  lpMem[0x2b] = 0xffffffff;
  iVar5 = 0x57;
  lpMem[0x2d] = param_1[0x10];
  local_8 = 0x57;
  uVar3 = DAT_00504c0c[2];
  lpMem[3] = uVar3;
  if ((*DAT_00504c0c & 0x100) == 0) {
    if ((int)DAT_00504c0c[1] < 0x57) {
      iVar5 = 0x2a;
    }
    piVar2 = (int *)DAT_00504c0c[iVar5 + 0x83];
  }
  else {
    if (*(ushort *)(DAT_006547e4 + 0xae) == 0) {
      uVar1 = 0x57;
    }
    else {
      uVar1 = (uint)*(ushort *)(DAT_006547e4 + 0xae);
    }
    piVar2 = (int *)DAT_00504c0c[uVar1 + 0x83];
    local_c = piVar2;
  }
  iVar5 = *piVar2;
  lpMem[0x25] = uVar3;
  uVar3 = (uint)lpMem[2] / (iVar5 + 2U);
  lpMem[0x26] = uVar3;
  if (0x4f < uVar3) {
    uVar3 = 0x4f;
  }
  lpMem[0x26] = uVar3;
  puVar4 = lpMem + 0x11;
  for (iVar5 = 0x14; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  lpMem[0x29] = 0;
  lpMem[0x28] = 0;
  lpMem[0x27] = 0;
  local_10 = lpMem;
  puVar4 = (undefined4 *)construct_bitmap_surface_context(local_44,lpMem[2],lpMem[3],0,0);
  puVar6 = lpMem + 4;
  for (iVar5 = 0xd; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar6 = *puVar4;
    puVar4 = puVar4 + 1;
    puVar6 = puVar6 + 1;
  }
  if (lpMem[4] == 0) {
    report_chunk_parse_error();
    HeapFree(DAT_005a7d9c,0,lpMem);
    return 0;
  }
  fill_bitmap_surface_context(lpMem + 4,0xff);
  g_static_text_overlay_list =
       allocate_linked_list_node_3field(g_static_text_overlay_list,(undefined4 *)0x0,(int)lpMem);
  return g_static_text_overlay_list;
}


