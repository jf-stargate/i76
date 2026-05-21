/*
 * Program: i76.exe
 * Function: raster_emit_span_callback_mode1_flat
 * Entry: 0047d1e0
 * Signature: undefined __cdecl raster_emit_span_callback_mode1_flat(byte * param_1, int * param_2)
 */


/* WARNING: Restarted to delay deadcode elimination for space: stack */
/* [cgpt i76.exe geo raster span family renames v38; confidence=medium-high] Simple flat/mode1 span
   callback that writes directly to destination spans. */

void __cdecl raster_emit_span_callback_mode1_flat(byte *param_1,int *param_2)

{
  uint uVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined4 *puVar9;
  uint uVar10;
  uint *puVar11;
  int local_8;
  
  iVar5 = *param_2;
  iVar6 = param_2[8];
  iVar7 = param_2[7];
  iVar8 = param_2[5];
  puVar9 = *(undefined4 **)(param_1 + 0x30);
  *puVar9 = *(undefined4 *)(param_1 + 0x28);
  puVar11 = (uint *)(*(int *)(param_1 + 0x2c) + 4);
  while (puVar11 != puVar9 + 1) {
    uVar10 = *puVar11;
    puVar11 = puVar11 + 1;
    uVar1 = (uVar10 >> 10 & 0x7ff) - 1;
    param_1 = (byte *)((uVar10 >> 0x15) + iVar6 * iVar5 + iVar7 + iVar8 + (uVar10 & 0x3ff) * iVar5);
    DAT_0059bd38 = param_1 + (uVar1 & 0xf) + 1;
    if (param_1 != DAT_0059bd38) {
      do {
        *param_1 = (&DAT_0061b1a0)[*param_1];
        param_1 = param_1 + 1;
      } while (param_1 != DAT_0059bd38);
    }
    local_8 = (int)uVar1 >> 4;
    if (-1 < local_8 + -1) {
      do {
        bVar2 = (&DAT_0061b1a0)[param_1[1]];
        bVar3 = (&DAT_0061b1a0)[param_1[2]];
        bVar4 = (&DAT_0061b1a0)[param_1[3]];
        *param_1 = (&DAT_0061b1a0)[*param_1];
        param_1[1] = bVar2;
        param_1[2] = bVar3;
        param_1[3] = bVar4;
        bVar2 = (&DAT_0061b1a0)[param_1[5]];
        bVar3 = (&DAT_0061b1a0)[param_1[6]];
        bVar4 = (&DAT_0061b1a0)[param_1[7]];
        param_1[4] = (&DAT_0061b1a0)[param_1[4]];
        param_1[5] = bVar2;
        param_1[6] = bVar3;
        param_1[7] = bVar4;
        bVar2 = (&DAT_0061b1a0)[param_1[9]];
        bVar3 = (&DAT_0061b1a0)[param_1[10]];
        bVar4 = (&DAT_0061b1a0)[param_1[0xb]];
        param_1[8] = (&DAT_0061b1a0)[param_1[8]];
        param_1[9] = bVar2;
        param_1[10] = bVar3;
        param_1[0xb] = bVar4;
        bVar2 = (&DAT_0061b1a0)[param_1[0xd]];
        bVar3 = (&DAT_0061b1a0)[param_1[0xe]];
        bVar4 = (&DAT_0061b1a0)[param_1[0xf]];
        param_1[0xc] = (&DAT_0061b1a0)[param_1[0xc]];
        param_1[0xd] = bVar2;
        param_1[0xe] = bVar3;
        param_1[0xf] = bVar4;
        param_1 = param_1 + 0x10;
        local_8 = local_8 + -1;
      } while (local_8 != 0);
    }
  }
  return;
}


