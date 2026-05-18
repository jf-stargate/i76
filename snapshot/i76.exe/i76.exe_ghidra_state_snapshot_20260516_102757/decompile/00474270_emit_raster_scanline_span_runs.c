/*
 * Program: i76.exe
 * Function: emit_raster_scanline_span_runs
 * Entry: 00474270
 * Signature: undefined __thiscall emit_raster_scanline_span_runs(void * this, int param_1, int param_2)
 */


/* [cgpt i76.exe geo raster span family renames v38; confidence=high] Emits packed scanline span
   descriptors using y/x-left/x-right packing. */

void __thiscall emit_raster_scanline_span_runs(void *this,int param_1,int param_2)

{
  uint *puVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  int *piVar5;
  uint *puVar6;
  uint uVar7;
  uint *puVar8;
  
  puVar6 = *(uint **)(param_1 + 0x24);
  puVar8 = *(uint **)(param_1 + 0x20);
  uVar7 = puVar8[4];
  *(uint *)(*(int *)((int)this + 0xc) + uVar7 * 4) = puVar8[1];
  *(uint *)(*(int *)((int)this + 0x10) + uVar7 * 4) = puVar6[1];
  iVar3 = *(int *)(param_1 + 0x30);
  iVar2 = iVar3 * 4 + 4;
  puVar4 = (undefined4 *)((int)DAT_004f9d80 - iVar2);
  if (puVar4 < DAT_004f9d7c) {
    DAT_004f9d80 = puVar4;
    ensure_raster_scratch_arena();
    puVar4 = (undefined4 *)((int)DAT_004f9d80 - iVar2);
  }
  DAT_004f9d80 = puVar4;
  *(undefined4 **)(param_1 + 0x2c) = puVar4;
  *puVar4 = 0xffffffff;
  piVar5 = puVar4 + 1;
  do {
    if (uVar7 == puVar8[7]) {
      puVar1 = puVar8 + 9;
      puVar8 = puVar8 + 8;
      *(uint *)(*(int *)((int)this + 0xc) + uVar7 * 4) = *puVar1;
    }
    if (uVar7 == puVar6[7]) {
      puVar1 = puVar6 + 9;
      puVar6 = puVar6 + 8;
      *(uint *)(*(int *)((int)this + 0x10) + uVar7 * 4) = *puVar1;
    }
    if (*puVar8 >> 0x15 < *puVar6 >> 0x15) {
      *piVar5 = ((*puVar8 >> 0x15) * 0x7ff + (*puVar6 >> 0x15)) * 0x400 + uVar7;
      piVar5 = piVar5 + 1;
    }
    *puVar8 = *puVar8 + puVar8[6];
    uVar7 = uVar7 + 1;
    *puVar6 = *puVar6 + puVar6[6];
  } while ((int)uVar7 < param_2);
  *(int *)(param_1 + 0x28) = piVar5[-1];
  *(int **)(param_1 + 0x30) = piVar5 + -1;
  if (piVar5 + -1 == *(int **)(param_1 + 0x2c)) {
    DAT_004f9d80 = DAT_004f9d80 + iVar3 + 1;
  }
  return;
}


