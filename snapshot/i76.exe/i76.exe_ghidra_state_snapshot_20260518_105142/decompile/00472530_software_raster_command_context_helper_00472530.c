/*
 * Program: i76.exe
 * Function: software_raster_command_context_helper_00472530
 * Entry: 00472530
 * Signature: undefined __cdecl software_raster_command_context_helper_00472530(float * param_1, int param_2, int param_3, int param_4, int param_5)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set C v15: Readability pass set C: software raster command context helper
   based on adjacent named subsystem context. */

void __cdecl
software_raster_command_context_helper_00472530
          (float *param_1,int param_2,int param_3,int param_4,int param_5)

{
  float *pfVar1;
  float *pfVar2;
  float *pfVar3;
  float *pfVar4;
  float *pfVar5;
  float *pfVar6;
  float fVar7;
  float fVar8;
  bool bVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float *pfVar13;
  int iVar14;
  float *pfVar15;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  int local_c;
  int local_8;
  int local_4;
  
  pfVar15 = param_1;
  set_bitmap_surface_clip_rect((int *)param_1[0xf],param_2,param_3,param_4,param_5);
  fVar11 = _DAT_004be5dc;
  fVar8 = param_1[0xf];
  local_10 = *(float *)((int)fVar8 + 0x1c);
  local_c = *(int *)((int)fVar8 + 0x20);
  local_8 = *(int *)((int)fVar8 + 0x24);
  local_4 = *(int *)((int)fVar8 + 0x28);
  param_1[7] = (float)(int)local_10;
  param_1[8] = (float)local_c;
  param_1[0x42] = 0.1;
  param_1[0x45] = 0.1;
  param_1[9] = (float)local_8;
  param_1[0x48] = 0.1;
  param_1[10] = (float)local_4;
  fVar11 = fVar11 / param_1[2];
  fVar10 = _DAT_004be5dc / param_1[3];
  param_1[0x40] = (param_1[7] - *param_1) * fVar11;
  pfVar13 = param_1 + 8;
  pfVar1 = param_1 + 9;
  pfVar2 = param_1 + 10;
  pfVar3 = param_1 + 1;
  fVar12 = fVar10 * (*pfVar13 - *pfVar3);
  fVar8 = *param_1;
  pfVar4 = param_1 + 1;
  fVar7 = fVar11 * (*pfVar1 - fVar8);
  fVar10 = fVar10 * (*pfVar2 - *pfVar4);
  param_1[0x41] = fVar12;
  param_1[0x4b] = 0.1;
  param_1[0x43] = fVar7;
  param_1[0x44] = fVar12;
  param_1[0x46] = fVar7;
  param_1[0x47] = fVar10;
  pfVar5 = param_1 + 7;
  fVar7 = *param_1;
  bVar9 = _DAT_004be5b4 <= param_1[0xd] * param_1[4];
  param_1[0x49] = fVar11 * (*pfVar5 - fVar7);
  param_1[0x4a] = fVar10;
  param_1 = (float *)(param_1[0xd] * param_1[4]);
  if (bVar9) {
    param_1 = (float *)0x47c35000;
  }
  pfVar6 = pfVar15 + 0x4c;
  fVar10 = ((float)param_1 / pfVar15[2]) * (*pfVar5 - fVar7);
  fVar7 = ((float)param_1 / pfVar15[3]) * (*pfVar13 - *pfVar3);
  fVar8 = ((float)param_1 / pfVar15[2]) * (*pfVar1 - fVar8);
  fVar11 = ((float)param_1 / pfVar15[3]) * (*pfVar2 - *pfVar4);
  pfVar15[0x4e] = (float)param_1;
  pfVar15[0x50] = fVar7;
  pfVar15[0x51] = (float)param_1;
  local_1c = _DAT_004be5e0;
  pfVar15[0x52] = fVar8;
  pfVar15[0x4d] = fVar7;
  local_18 = _DAT_004be5e0;
  *pfVar6 = fVar10;
  pfVar15[0x54] = (float)param_1;
  local_14 = _DAT_004be5e0;
  pfVar15[0x55] = fVar10;
  pfVar15[0x56] = fVar11;
  pfVar15[0x4f] = fVar8;
  pfVar15[0x57] = (float)param_1;
  pfVar15[0x53] = fVar11;
  pfVar13 = (float *)i76_runtime_compute_plane_or_triangle_normal4
                               (&local_10,&local_1c,pfVar6,pfVar15 + 0x55);
  pfVar15[0x28] = *pfVar13;
  pfVar15[0x29] = pfVar13[1];
  pfVar15[0x2a] = pfVar13[2];
  pfVar15[0x2b] = pfVar13[3];
  pfVar13 = (float *)i76_runtime_compute_plane_or_triangle_normal4
                               (&local_10,&local_1c,pfVar15 + 0x4f,pfVar15 + 0x52);
  pfVar15[0x2c] = *pfVar13;
  pfVar15[0x2d] = pfVar13[1];
  pfVar15[0x2e] = pfVar13[2];
  pfVar15[0x2f] = pfVar13[3];
  pfVar13 = (float *)i76_runtime_compute_plane_or_triangle_normal4
                               (&local_10,&local_1c,pfVar6,pfVar15 + 0x4f);
  pfVar15[0x30] = *pfVar13;
  pfVar15[0x31] = pfVar13[1];
  pfVar15[0x32] = pfVar13[2];
  pfVar15[0x33] = pfVar13[3];
  pfVar13 = (float *)i76_runtime_compute_plane_or_triangle_normal4
                               (&local_10,&local_1c,pfVar15 + 0x52,pfVar15 + 0x55);
  pfVar15[0x34] = *pfVar13;
  pfVar15[0x35] = pfVar13[1];
  pfVar15[0x36] = pfVar13[2];
  pfVar15[0x37] = pfVar13[3];
  pfVar13 = (float *)i76_runtime_compute_plane_or_triangle_normal4
                               (&local_10,pfVar6,pfVar15 + 0x4f,pfVar15 + 0x52);
  pfVar15[0x38] = *pfVar13;
  pfVar15[0x39] = pfVar13[1];
  pfVar15[0x3a] = pfVar13[2];
  pfVar15[0x3b] = pfVar13[3];
  pfVar13 = (float *)i76_runtime_compute_plane_or_triangle_normal4
                               (&local_10,pfVar15 + 0x40,pfVar15 + 0x43,pfVar15 + 0x46);
  pfVar15[0x3c] = *pfVar13;
  pfVar15[0x3d] = pfVar13[1];
  pfVar15[0x3e] = pfVar13[2];
  iVar14 = 4;
  pfVar15[0x3f] = pfVar13[3];
  pfVar13 = pfVar15 + 0x4d;
  do {
    local_1c = pfVar13[-1] + local_1c;
    local_18 = local_18 + *pfVar13;
    local_14 = pfVar13[1] + local_14;
    pfVar13 = pfVar13 + 3;
    iVar14 = iVar14 + -1;
  } while (iVar14 != 0);
  local_1c = local_1c * _DAT_004be5e4;
  local_18 = local_18 * _DAT_004be5e4;
  local_14 = local_14 * _DAT_004be5e4;
  pfVar15 = pfVar15 + 0x29;
  iVar14 = 6;
  do {
    if (local_18 * *pfVar15 + local_14 * pfVar15[1] + local_1c * pfVar15[-1] + pfVar15[2] <
        (float)_DAT_004be5c0) {
      pfVar15[-1] = -pfVar15[-1];
      *pfVar15 = -*pfVar15;
      pfVar15[1] = -pfVar15[1];
      pfVar15[2] = -pfVar15[2];
    }
    pfVar15 = pfVar15 + 4;
    iVar14 = iVar14 + -1;
  } while (iVar14 != 0);
  return;
}


