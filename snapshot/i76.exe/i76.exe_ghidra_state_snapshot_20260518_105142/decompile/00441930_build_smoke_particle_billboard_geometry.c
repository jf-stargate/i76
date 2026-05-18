/*
 * Program: i76.exe
 * Function: build_smoke_particle_billboard_geometry
 * Entry: 00441930
 * Signature: undefined __cdecl build_smoke_particle_billboard_geometry(float * param_1, int * param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v9 vehicle effect/collision/particle cluster: Builds billboard/quad geometry for one
   smoke/effect particle chain using camera/view data and particle age. */

void __cdecl build_smoke_particle_billboard_geometry(float *param_1,int *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  undefined4 uVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  int iVar19;
  undefined4 *puVar20;
  
  fVar1 = param_1[0x10];
  fVar2 = param_1[0x16];
  fVar3 = param_1[0x14];
  fVar4 = param_1[0x11];
  dVar7 = *(double *)(param_2 + 10);
  fVar5 = param_1[0x13];
  dVar8 = *(double *)(param_2 + 0xe);
  dVar9 = *(double *)(param_2 + 0xc);
  dVar10 = *(double *)(param_2 + 0xc);
  fVar6 = param_1[0x17];
  dVar11 = *(double *)(param_1 + 0x1a);
  dVar12 = *(double *)(param_2 + 10);
  fVar17 = param_1[0x15] * (float)*(double *)(param_2 + 0xc) +
           param_1[0x12] * (float)*(double *)(param_2 + 10) +
           param_1[0x18] * (float)*(double *)(param_2 + 0xe) + (float)*(double *)(param_1 + 0x1e);
  dVar13 = *(double *)(param_2 + 0xe);
  dVar14 = *(double *)(param_1 + 0x1c);
  if ((fVar17 <= (float)_DAT_004bd2a0) && (param_1[0x42] <= fVar17)) {
    fVar18 = _DAT_004bd26c / fVar17;
    iVar19 = *(int *)(&DAT_004f1728 + (param_2[1] % 0x14 + *param_2 * 0x14) * 4);
    if ((0x2f < iVar19) || (iVar19 < 0)) {
      iVar19 = 0;
    }
    uVar15 = (&DAT_0052b960)[iVar19];
    puVar20 = i76_runtime_prepare_terrain_polygon_material_or_light();
    puVar20[3] = 9;
    *puVar20 = 4;
    puVar20[2] = 0x8c;
    puVar20[1] = uVar15;
    fVar16 = param_1[2] * fVar18;
    fVar18 = param_1[3] * fVar18;
    fVar2 = (fVar5 * (float)dVar9 + fVar2 * (float)dVar8 + fVar1 * (float)dVar7 + (float)dVar11) *
            fVar16 + *param_1;
    fVar1 = (fVar6 * (float)dVar13 + fVar4 * (float)dVar12 + fVar3 * (float)dVar10 + (float)dVar14)
            * fVar18 + param_1[1];
    fVar3 = _DAT_004bd2ac;
    if (*param_2 == 3) {
      fVar3 = _DAT_004bd2a8;
    }
    fVar16 = fVar16 * fVar3;
    fVar18 = fVar18 * _DAT_004bd2ac;
    fVar3 = fVar2 - fVar16;
    fVar4 = fVar1 - fVar18;
    fVar18 = fVar18 + fVar1;
    puVar20[7] = fVar3;
    puVar20[8] = fVar4;
    puVar20[9] = fVar17;
    fVar16 = fVar16 + fVar2;
    puVar20[10] = DAT_004fa8e8;
    puVar20[0xb] = DAT_004fa8ec;
    uVar15 = DAT_004fa8f0;
    puVar20[0xd] = fVar3;
    puVar20[0xe] = fVar18;
    puVar20[0xf] = fVar17;
    puVar20[0xc] = uVar15;
    puVar20[0x10] = DAT_004fa8f4;
    puVar20[0x11] = DAT_004fa8f8;
    uVar15 = DAT_004fa8fc;
    puVar20[0x13] = fVar16;
    puVar20[0x12] = uVar15;
    puVar20[0x14] = fVar18;
    puVar20[0x15] = fVar17;
    puVar20[0x16] = DAT_004fa900;
    puVar20[0x17] = DAT_004fa904;
    uVar15 = DAT_004fa908;
    puVar20[0x19] = fVar16;
    puVar20[0x1a] = fVar4;
    puVar20[0x18] = uVar15;
    puVar20[0x1b] = fVar17;
    puVar20[0x1c] = DAT_004fa90c;
    puVar20[0x1d] = DAT_004fa910;
    uVar15 = DAT_004fa914;
    puVar20[4] = fVar17;
    puVar20[0x1e] = uVar15;
    i76_runtime_bin_terrain_primitive_for_scan_or_span_render(fVar17);
    return;
  }
  return;
}


