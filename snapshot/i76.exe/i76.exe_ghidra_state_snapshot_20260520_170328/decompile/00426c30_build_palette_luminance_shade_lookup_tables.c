/*
 * Program: i76.exe
 * Function: build_palette_luminance_shade_lookup_tables
 * Entry: 00426c30
 * Signature: undefined __stdcall build_palette_luminance_shade_lookup_tables(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v8 display/d3d cluster: Builds palette-derived luminance/shading lookup tables from
   the game RGB palette and fills gray ramp tables used by the display backend. */

void build_palette_luminance_shade_lookup_tables(void)

{
  float fVar1;
  uint uVar2;
  uint uVar3;
  uint3 *puVar4;
  uint *puVar5;
  uint *puVar6;
  int iVar7;
  float *pfVar8;
  float10 fVar9;
  float local_84;
  float local_80 [32];
  
  local_84 = 0.0;
  puVar4 = (uint3 *)&DAT_005dcfa8;
  do {
    fVar1 = ((float)(ushort)((ushort)*puVar4 >> 8) * _DAT_004bcd1c -
            (float)(*puVar4 & 0xff) * _DAT_004bcd20) -
            (float)*(byte *)((int)puVar4 + 2) * _DAT_004bcd24;
    if (local_84 < fVar1) {
      local_84 = fVar1;
    }
    puVar4 = (uint3 *)((int)puVar4 + 3);
  } while ((int)puVar4 < 0x5dd2a5);
  iVar7 = 0x20;
  pfVar8 = local_80;
  do {
    fVar9 = (float10)_CIpow();
    iVar7 = iVar7 + -1;
    *pfVar8 = (float)(fVar9 * (float10)local_84);
    pfVar8 = pfVar8 + 1;
  } while (iVar7 != 0);
  DAT_005280b0 = 0x10;
  uVar2 = ftol();
  uVar2 = uVar2 & 0xff;
  uVar3 = ftol();
  uVar3 = uVar3 & 0xff;
  puVar5 = &DAT_00526790;
  do {
    puVar6 = puVar5 + 1;
    *puVar5 = ((uVar2 | 0xffffff00) << 8 | uVar2) << 8 | uVar2;
    puVar5[0x30] = ((uVar3 | 0xffffff00) << 8 | uVar3) << 8 | uVar3;
    puVar5 = puVar6;
  } while ((int)puVar6 < 0x5267d0);
  puVar5 = &DAT_005267d0;
  do {
    uVar2 = ftol();
    uVar2 = uVar2 & 0xff;
    puVar6 = puVar5 + 1;
    *puVar5 = ((uVar2 | 0xffffff00) << 8 | uVar2) << 8 | uVar2;
    puVar5 = puVar6;
  } while ((int)puVar6 < 0x526850);
  return;
}


