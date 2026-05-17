/*
 * Program: i76.exe
 * Function: raster_emit_flat_shaded_constant_spans
 * Entry: 0047cfc0
 * Signature: undefined __cdecl raster_emit_flat_shaded_constant_spans(byte * param_1, int * param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Restarted to delay deadcode elimination for space: stack */
/* [cgpt i76.exe geo raster span family renames v38; confidence=high] Span callback for flat-color
   spans with constant light/shade; uses palette shade table and packed span descriptors. */

void __cdecl raster_emit_flat_shaded_constant_spans(byte *param_1,int *param_2)

{
  byte bVar1;
  undefined1 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  uint *puVar8;
  uint uVar9;
  int iVar10;
  undefined1 *local_8;
  
  iVar3 = *param_2;
  iVar4 = param_2[8];
  iVar5 = param_2[5];
  iVar6 = param_2[7];
  bVar1 = *param_1;
  puVar7 = *(undefined4 **)(param_1 + 0x30);
  *puVar7 = *(undefined4 *)(param_1 + 0x28);
  puVar8 = (uint *)(*(int *)(param_1 + 0x2c) + 4);
  while (puVar8 != puVar7 + 1) {
    uVar9 = *puVar8;
    puVar8 = puVar8 + 1;
    _DAT_0059bc50 = (double)(*(float *)(param_1 + 0x18) + (float)_DAT_004faf18);
    local_8 = (undefined1 *)
              ((uVar9 >> 0x15) + iVar4 * iVar3 + iVar5 + iVar6 + (uVar9 & 0x3ff) * iVar3);
    uVar9 = (uVar9 >> 10 & 0x7ff) - 1;
    _DAT_0059bc50 = (double)((ulonglong)_DAT_0059bc50 & 0xffffffff00001f00);
    DAT_0059bd38 = local_8 + (uVar9 & 0xf) + 1;
    if (local_8 != DAT_0059bd38) {
      do {
        *local_8 = (&DAT_0061b2a0)[DAT_0059bc50 + (uint)bVar1];
        local_8 = local_8 + 1;
      } while (local_8 != DAT_0059bd38);
    }
    iVar10 = (int)uVar9 >> 4;
    if (-1 < iVar10 + -1) {
      do {
        uVar2 = (&DAT_0061b2a0)[CONCAT31((int3)((ulonglong)_DAT_0059bc50 >> 8),bVar1) & 0x1fff];
        *local_8 = uVar2;
        local_8[1] = uVar2;
        local_8[2] = uVar2;
        local_8[3] = uVar2;
        local_8[4] = uVar2;
        local_8[5] = uVar2;
        local_8[6] = uVar2;
        local_8[7] = uVar2;
        local_8[8] = uVar2;
        local_8[9] = uVar2;
        local_8[10] = uVar2;
        local_8[0xb] = uVar2;
        local_8[0xc] = uVar2;
        local_8[0xd] = uVar2;
        local_8[0xe] = uVar2;
        local_8[0xf] = uVar2;
        iVar10 = iVar10 + -1;
        local_8 = local_8 + 0x10;
      } while (iVar10 != 0);
    }
  }
  return;
}


