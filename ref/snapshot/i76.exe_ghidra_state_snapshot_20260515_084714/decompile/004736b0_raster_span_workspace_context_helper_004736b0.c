/*
 * Program: i76.exe
 * Function: raster_span_workspace_context_helper_004736b0
 * Entry: 004736b0
 * Signature: undefined4 * __thiscall raster_span_workspace_context_helper_004736b0(void * this, int param_1)
 */


/* cgpt readability rename set C v15: Readability pass set C: raster span workspace context helper
   based on adjacent named subsystem context. */

undefined4 * __thiscall raster_span_workspace_context_helper_004736b0(void *this,int param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  uint uVar3;
  int iVar4;
  
  *(int *)((int)this + 0x34) = param_1;
  puVar2 = operator_new(param_1 * 0x28);
  iVar4 = *(int *)((int)this + 0x34);
  *(undefined4 **)((int)this + 4) = puVar2;
  puVar1 = puVar2 + iVar4;
  *(undefined4 **)((int)this + 8) = puVar1;
  puVar1 = puVar1 + iVar4;
  *(undefined4 **)((int)this + 0xc) = puVar1;
  puVar1 = puVar1 + iVar4;
  *(undefined4 **)((int)this + 0x10) = puVar1;
  puVar1 = puVar1 + iVar4;
  *(undefined4 **)((int)this + 0x14) = puVar1;
  puVar1 = puVar1 + iVar4;
  *(undefined4 **)((int)this + 0x18) = puVar1;
  puVar1 = puVar1 + iVar4;
  *(undefined4 **)((int)this + 0x1c) = puVar1;
  puVar1 = puVar1 + iVar4;
  *(undefined4 **)((int)this + 0x20) = puVar1;
  *(undefined4 **)((int)this + 0x24) = puVar1 + iVar4;
  *(undefined4 **)((int)this + 0x28) = puVar1 + iVar4 + iVar4;
  for (uVar3 = (uint)(iVar4 * 0x28) >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  for (iVar4 = 0; iVar4 != 0; iVar4 = iVar4 + -1) {
    *(undefined1 *)puVar2 = 0;
    puVar2 = (undefined4 *)((int)puVar2 + 1);
  }
  DAT_0058dabc = DAT_0058dab8;
  DAT_004f9d80 = 0xffffffff;
  DAT_004f9d7c = 0xffffffff;
  *(undefined4 *)((int)this + 0x38) = 0;
  *(undefined4 **)((int)this + 0x30) = (undefined4 *)((int)this + 0x2c);
  *(undefined4 *)this = 0;
  *(undefined4 *)((int)this + 0x2c) = 0;
  DAT_0058dac0 = 0;
  return this;
}


