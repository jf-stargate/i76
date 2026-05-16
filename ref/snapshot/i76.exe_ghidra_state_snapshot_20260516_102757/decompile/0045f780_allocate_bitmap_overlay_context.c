/*
 * Program: i76.exe
 * Function: allocate_bitmap_overlay_context
 * Entry: 0045f780
 * Signature: undefined4 * __stdcall allocate_bitmap_overlay_context(void)
 */


/* cgpt rename v2: Allocates and initializes a bitmap overlay/context with an embedded bitmap
   surface context. */

undefined4 * allocate_bitmap_overlay_context(void)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  int local_34 [13];
  
  puVar1 = HeapAlloc(DAT_0054b1f0,0,0xb8);
  puVar1[3] = puVar1[3] & 0xffffffe9 | 1;
  *puVar1 = 1;
  puVar1[1] = 0;
  puVar1[2] = 0;
  puVar1[0x15] = 0;
  puVar1[0x1e] = 0;
  puVar1[0x16] = 0;
  puVar1[0x17] = 0;
  puVar1[0x18] = 0;
  puVar1[0x19] = 0;
  puVar1[0x1a] = 0;
  puVar1[0x1b] = 0;
  puVar1[0x1c] = 0;
  puVar1[0x1d] = 0;
  puVar2 = &DAT_004faed8;
  puVar4 = puVar1 + 4;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar4 = puVar4 + 1;
  }
  puVar1[0x14] = 0;
  puVar2 = (undefined4 *)construct_bitmap_surface_context(local_34,0,0,0,0);
  puVar4 = puVar1 + 0x20;
  for (iVar3 = 0xd; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar4 = puVar4 + 1;
  }
  return puVar1;
}


