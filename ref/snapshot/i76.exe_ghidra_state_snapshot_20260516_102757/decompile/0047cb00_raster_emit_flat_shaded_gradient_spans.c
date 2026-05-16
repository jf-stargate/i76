/*
 * Program: i76.exe
 * Function: raster_emit_flat_shaded_gradient_spans
 * Entry: 0047cb00
 * Signature: undefined __cdecl raster_emit_flat_shaded_gradient_spans(byte * param_1, int * param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Restarted to delay deadcode elimination for space: stack */
/* [cgpt i76.exe geo raster span family renames v38; confidence=high] Span callback for flat-color
   spans with interpolated light/shade; uses palette shade table and packed span descriptors. */

void __cdecl raster_emit_flat_shaded_gradient_spans(byte *param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  uint uVar6;
  uint *puVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  int local_14;
  float local_10;
  float local_c;
  undefined1 *local_8;
  
  iVar1 = *param_2;
  iVar2 = param_2[8];
  iVar3 = param_2[5];
  iVar4 = param_2[7];
  puVar5 = *(undefined4 **)(param_1 + 0x30);
  uVar6 = (uint)*param_1;
  *puVar5 = *(undefined4 *)(param_1 + 0x28);
  puVar7 = (uint *)(*(int *)(param_1 + 0x2c) + 4);
  while (puVar7 != puVar5 + 1) {
    uVar11 = *puVar7;
    puVar7 = puVar7 + 1;
    local_10 = *(float *)(param_1 + 0x58);
    local_8 = (undefined1 *)
              ((uVar11 & 0x3ff) * iVar1 + (uVar11 >> 0x15) + iVar2 * iVar1 + iVar3 + iVar4);
    uVar10 = (uVar11 >> 10 & 0x7ff) - 1;
    local_c = (float)(uVar11 >> 0x15) * local_10 +
              (float)(uVar11 & 0x3ff) * *(float *)(param_1 + 0x5c) + *(float *)(param_1 + 0x18);
    local_14 = (int)uVar10 >> 4;
    _DAT_0059bc50 = (double)(local_c + (float)_DAT_004faf18);
    local_c = (float)(uVar10 & 0xf) * local_10 + local_c;
    _DAT_0059bba0 = (double)(local_10 + (float)_DAT_004faf18);
    local_10 = local_10 * _DAT_004be774;
    uVar11 = DAT_0059bc50;
    if (((ulonglong)_DAT_0059bc50 & 0xffffe000) != 0) {
      uVar11 = ~DAT_0059bc50 >> 0x13;
      _DAT_0059bc50 = (double)CONCAT44(DAT_0059bc50_4,uVar11);
      local_c = (float)uVar11;
    }
    uVar8 = DAT_0059bba0 * uVar10 + uVar11;
    if ((uVar8 & 0xffffe000) != 0) {
      iVar9 = (int)((~uVar8 >> 0x13) - uVar11) / (int)uVar10;
      _DAT_0059bba0 = (double)CONCAT44(DAT_0059bba0_4,iVar9);
      local_10 = (float)(iVar9 << 4);
    }
    DAT_0059bd38 = local_8 + (uVar10 & 0xf) + 1;
    if (local_8 != DAT_0059bd38) {
      do {
        uVar11 = DAT_0059bc50;
        iVar9 = DAT_0059bba0;
        *local_8 = (&DAT_0061b2a0)[(DAT_0059bc50 & 0x1f00) + uVar6];
        _DAT_0059bc50 = (double)CONCAT44(DAT_0059bc50_4,uVar11 + iVar9);
        local_8 = local_8 + 1;
      } while (local_8 != DAT_0059bd38);
    }
    if (-1 < local_14 + -1) {
      do {
        _DAT_0059bc50 = (double)(local_c + (float)_DAT_004faf18);
        local_c = local_c + local_10;
        iVar9 = DAT_0059bba0;
        uVar11 = DAT_0059bc50 + DAT_0059bba0;
        uVar10 = uVar11 + DAT_0059bba0;
        *local_8 = (&DAT_0061b2a0)[(DAT_0059bc50 & 0x1f00) + uVar6];
        uVar8 = uVar10 + iVar9;
        local_8[1] = (&DAT_0061b2a0)[(uVar11 & 0x1f00) + uVar6];
        uVar11 = uVar8 + iVar9;
        local_8[2] = (&DAT_0061b2a0)[(uVar10 & 0x1f00) + uVar6];
        uVar10 = uVar11 + iVar9;
        local_8[3] = (&DAT_0061b2a0)[(uVar8 & 0x1f00) + uVar6];
        uVar8 = uVar10 + iVar9;
        local_8[4] = (&DAT_0061b2a0)[(uVar11 & 0x1f00) + uVar6];
        uVar11 = uVar8 + iVar9;
        local_8[5] = (&DAT_0061b2a0)[(uVar10 & 0x1f00) + uVar6];
        uVar10 = uVar11 + iVar9;
        local_8[6] = (&DAT_0061b2a0)[(uVar8 & 0x1f00) + uVar6];
        uVar8 = uVar10 + iVar9;
        local_8[7] = (&DAT_0061b2a0)[(uVar11 & 0x1f00) + uVar6];
        uVar11 = uVar8 + iVar9;
        local_8[8] = (&DAT_0061b2a0)[(uVar10 & 0x1f00) + uVar6];
        uVar10 = uVar11 + iVar9;
        local_8[9] = (&DAT_0061b2a0)[(uVar8 & 0x1f00) + uVar6];
        uVar8 = uVar10 + iVar9;
        local_8[10] = (&DAT_0061b2a0)[(uVar11 & 0x1f00) + uVar6];
        uVar11 = uVar8 + iVar9;
        local_8[0xb] = (&DAT_0061b2a0)[(uVar10 & 0x1f00) + uVar6];
        uVar10 = uVar11 + iVar9;
        local_8[0xc] = (&DAT_0061b2a0)[(uVar8 & 0x1f00) + uVar6];
        uVar8 = uVar10 + iVar9;
        local_8[0xd] = (&DAT_0061b2a0)[(uVar11 & 0x1f00) + uVar6];
        local_8[0xe] = (&DAT_0061b2a0)[(uVar10 & 0x1f00) + uVar6];
        _DAT_0059bc50 = (double)CONCAT44(DAT_0059bc50_4,uVar8 + iVar9);
        local_8[0xf] = (&DAT_0061b2a0)[(uVar8 & 0x1f00) + uVar6];
        local_14 = local_14 + -1;
        local_8 = local_8 + 0x10;
      } while (local_14 != 0);
    }
  }
  return;
}


