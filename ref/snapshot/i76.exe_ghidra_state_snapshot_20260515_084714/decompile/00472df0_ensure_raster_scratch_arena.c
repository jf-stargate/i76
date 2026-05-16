/*
 * Program: i76.exe
 * Function: ensure_raster_scratch_arena
 * Entry: 00472df0
 * Signature: undefined __stdcall ensure_raster_scratch_arena(void)
 */


/* [cgpt i76.exe geo raster span family renames v38; confidence=high] Ensures/refreshes the software
   rasterizer scratch arena used by command records, edges, and span lists. */

void ensure_raster_scratch_arena(void)

{
  undefined4 *puVar1;
  void *pvVar2;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004bba56;
  local_c = ExceptionList;
  if (DAT_0058dabc == (int *)0x0) {
    ExceptionList = &local_c;
    puVar1 = operator_new(0xc);
    local_4 = 0;
    if (puVar1 == (undefined4 *)0x0) {
      puVar1 = (undefined4 *)0x0;
      DAT_0058dab8 = (undefined4 *)0x0;
    }
    else {
      *puVar1 = 0;
      pvVar2 = operator_new(0x10000);
      puVar1[1] = pvVar2;
      puVar1[2] = 0x10000;
      DAT_0058dab8 = puVar1;
    }
  }
  else {
    if (*DAT_0058dabc == 0) {
      ExceptionList = &local_c;
      puVar1 = operator_new(0xc);
      local_4 = 1;
      if (puVar1 == (undefined4 *)0x0) {
        puVar1 = (undefined4 *)0x0;
      }
      else {
        *puVar1 = 0;
        pvVar2 = operator_new(0x10000);
        puVar1[1] = pvVar2;
        puVar1[2] = 0x10000;
      }
      *DAT_0058dabc = (int)puVar1;
    }
    puVar1 = (undefined4 *)*DAT_0058dabc;
  }
  DAT_0058dabc = puVar1;
  DAT_004f9d80 = puVar1[2] + puVar1[1] & 0xffffffe0;
  DAT_004f9d7c = puVar1[1];
  ExceptionList = local_c;
  return;
}


