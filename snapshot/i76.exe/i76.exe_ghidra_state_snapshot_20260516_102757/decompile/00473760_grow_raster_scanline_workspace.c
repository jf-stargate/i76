/*
 * Program: i76.exe
 * Function: grow_raster_scanline_workspace
 * Entry: 00473760
 * Signature: undefined __thiscall grow_raster_scanline_workspace(void * this, int param_1)
 */


/* [cgpt i76.exe geo raster span family renames v38; confidence=high] Grows/reallocates the software
   rasterizer scanline workspace arrays. */

void __thiscall grow_raster_scanline_workspace(void *this,int param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  uint uVar10;
  int iVar11;
  int iVar12;
  undefined4 *puVar13;
  undefined4 *puVar14;
  
  if (*(int *)((int)this + 0x38) < param_1) {
    iVar12 = *(int *)((int)this + 0x34);
    *(int *)((int)this + 0x38) = param_1;
    if (iVar12 < param_1) {
      for (; iVar12 < param_1; iVar12 = iVar12 * 2) {
      }
      puVar9 = operator_new(iVar12 * 0x28);
      puVar1 = puVar9 + iVar12;
      puVar2 = puVar1 + iVar12;
      puVar3 = puVar2 + iVar12;
      puVar4 = puVar3 + iVar12;
      puVar5 = puVar4 + iVar12;
      puVar6 = puVar5 + iVar12;
      puVar7 = puVar6 + iVar12;
      puVar8 = puVar7 + iVar12;
      puVar13 = puVar9;
      for (uVar10 = (uint)(iVar12 * 0x28) >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
        *puVar13 = 0;
        puVar13 = puVar13 + 1;
      }
      for (iVar11 = 0; iVar11 != 0; iVar11 = iVar11 + -1) {
        *(undefined1 *)puVar13 = 0;
        puVar13 = (undefined4 *)((int)puVar13 + 1);
      }
      puVar13 = *(undefined4 **)((int)this + 4);
      puVar14 = puVar9;
      for (uVar10 = *(uint *)((int)this + 0x34) & 0x3fffffff; uVar10 != 0; uVar10 = uVar10 - 1) {
        *puVar14 = *puVar13;
        puVar13 = puVar13 + 1;
        puVar14 = puVar14 + 1;
      }
      for (iVar11 = 0; iVar11 != 0; iVar11 = iVar11 + -1) {
        *(undefined1 *)puVar14 = *(undefined1 *)puVar13;
        puVar13 = (undefined4 *)((int)puVar13 + 1);
        puVar14 = (undefined4 *)((int)puVar14 + 1);
      }
      puVar13 = *(undefined4 **)((int)this + 8);
      puVar14 = puVar1;
      for (uVar10 = *(uint *)((int)this + 0x34) & 0x3fffffff; uVar10 != 0; uVar10 = uVar10 - 1) {
        *puVar14 = *puVar13;
        puVar13 = puVar13 + 1;
        puVar14 = puVar14 + 1;
      }
      for (iVar11 = 0; iVar11 != 0; iVar11 = iVar11 + -1) {
        *(undefined1 *)puVar14 = *(undefined1 *)puVar13;
        puVar13 = (undefined4 *)((int)puVar13 + 1);
        puVar14 = (undefined4 *)((int)puVar14 + 1);
      }
      puVar13 = *(undefined4 **)((int)this + 0xc);
      puVar14 = puVar2;
      for (uVar10 = *(uint *)((int)this + 0x34) & 0x3fffffff; uVar10 != 0; uVar10 = uVar10 - 1) {
        *puVar14 = *puVar13;
        puVar13 = puVar13 + 1;
        puVar14 = puVar14 + 1;
      }
      for (iVar11 = 0; iVar11 != 0; iVar11 = iVar11 + -1) {
        *(undefined1 *)puVar14 = *(undefined1 *)puVar13;
        puVar13 = (undefined4 *)((int)puVar13 + 1);
        puVar14 = (undefined4 *)((int)puVar14 + 1);
      }
      puVar13 = *(undefined4 **)((int)this + 0x10);
      puVar14 = puVar3;
      for (uVar10 = *(uint *)((int)this + 0x34) & 0x3fffffff; uVar10 != 0; uVar10 = uVar10 - 1) {
        *puVar14 = *puVar13;
        puVar13 = puVar13 + 1;
        puVar14 = puVar14 + 1;
      }
      for (iVar11 = 0; iVar11 != 0; iVar11 = iVar11 + -1) {
        *(undefined1 *)puVar14 = *(undefined1 *)puVar13;
        puVar13 = (undefined4 *)((int)puVar13 + 1);
        puVar14 = (undefined4 *)((int)puVar14 + 1);
      }
      puVar13 = *(undefined4 **)((int)this + 0x24);
      puVar14 = puVar8;
      for (uVar10 = *(uint *)((int)this + 0x34) & 0x3fffffff; uVar10 != 0; uVar10 = uVar10 - 1) {
        *puVar14 = *puVar13;
        puVar13 = puVar13 + 1;
        puVar14 = puVar14 + 1;
      }
      for (iVar11 = 0; iVar11 != 0; iVar11 = iVar11 + -1) {
        *(undefined1 *)puVar14 = *(undefined1 *)puVar13;
        puVar13 = (undefined4 *)((int)puVar13 + 1);
        puVar14 = (undefined4 *)((int)puVar14 + 1);
      }
      puVar13 = *(undefined4 **)((int)this + 0x14);
      puVar14 = puVar4;
      for (uVar10 = *(uint *)((int)this + 0x34) & 0x3fffffff; uVar10 != 0; uVar10 = uVar10 - 1) {
        *puVar14 = *puVar13;
        puVar13 = puVar13 + 1;
        puVar14 = puVar14 + 1;
      }
      for (iVar11 = 0; iVar11 != 0; iVar11 = iVar11 + -1) {
        *(undefined1 *)puVar14 = *(undefined1 *)puVar13;
        puVar13 = (undefined4 *)((int)puVar13 + 1);
        puVar14 = (undefined4 *)((int)puVar14 + 1);
      }
      puVar13 = *(undefined4 **)((int)this + 0x18);
      puVar14 = puVar5;
      for (uVar10 = *(uint *)((int)this + 0x34) & 0x3fffffff; uVar10 != 0; uVar10 = uVar10 - 1) {
        *puVar14 = *puVar13;
        puVar13 = puVar13 + 1;
        puVar14 = puVar14 + 1;
      }
      for (iVar11 = 0; iVar11 != 0; iVar11 = iVar11 + -1) {
        *(undefined1 *)puVar14 = *(undefined1 *)puVar13;
        puVar13 = (undefined4 *)((int)puVar13 + 1);
        puVar14 = (undefined4 *)((int)puVar14 + 1);
      }
      puVar13 = *(undefined4 **)((int)this + 0x1c);
      puVar14 = puVar6;
      for (uVar10 = *(uint *)((int)this + 0x34) & 0x3fffffff; uVar10 != 0; uVar10 = uVar10 - 1) {
        *puVar14 = *puVar13;
        puVar13 = puVar13 + 1;
        puVar14 = puVar14 + 1;
      }
      for (iVar11 = 0; iVar11 != 0; iVar11 = iVar11 + -1) {
        *(undefined1 *)puVar14 = *(undefined1 *)puVar13;
        puVar13 = (undefined4 *)((int)puVar13 + 1);
        puVar14 = (undefined4 *)((int)puVar14 + 1);
      }
      puVar13 = *(undefined4 **)((int)this + 0x20);
      puVar14 = puVar7;
      for (uVar10 = *(uint *)((int)this + 0x34) & 0x3fffffff; uVar10 != 0; uVar10 = uVar10 - 1) {
        *puVar14 = *puVar13;
        puVar13 = puVar13 + 1;
        puVar14 = puVar14 + 1;
      }
      for (iVar11 = 0; iVar11 != 0; iVar11 = iVar11 + -1) {
        *(undefined1 *)puVar14 = *(undefined1 *)puVar13;
        puVar13 = (undefined4 *)((int)puVar13 + 1);
        puVar14 = (undefined4 *)((int)puVar14 + 1);
      }
      puVar13 = *(undefined4 **)((int)this + 0x28);
      puVar14 = puVar8 + iVar12;
      for (uVar10 = *(uint *)((int)this + 0x34) & 0x3fffffff; uVar10 != 0; uVar10 = uVar10 - 1) {
        *puVar14 = *puVar13;
        puVar13 = puVar13 + 1;
        puVar14 = puVar14 + 1;
      }
      for (iVar11 = 0; iVar11 != 0; iVar11 = iVar11 + -1) {
        *(undefined1 *)puVar14 = *(undefined1 *)puVar13;
        puVar13 = (undefined4 *)((int)puVar13 + 1);
        puVar14 = (undefined4 *)((int)puVar14 + 1);
      }
      operator_delete(*(void **)((int)this + 4));
      *(undefined4 **)((int)this + 4) = puVar9;
      *(undefined4 **)((int)this + 8) = puVar1;
      *(undefined4 **)((int)this + 0xc) = puVar2;
      *(undefined4 **)((int)this + 0x10) = puVar3;
      *(undefined4 **)((int)this + 0x24) = puVar8;
      *(undefined4 **)((int)this + 0x14) = puVar4;
      *(undefined4 **)((int)this + 0x18) = puVar5;
      *(undefined4 **)((int)this + 0x1c) = puVar6;
      *(undefined4 **)((int)this + 0x20) = puVar7;
      *(undefined4 **)((int)this + 0x28) = puVar8 + iVar12;
      *(int *)((int)this + 0x34) = iVar12;
    }
  }
  return;
}


