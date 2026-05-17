/*
 * Program: i76.exe
 * Function: zone_satellite_map_context_helper_004937c0
 * Entry: 004937c0
 * Signature: undefined __stdcall zone_satellite_map_context_helper_004937c0(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v19: was zone_satellite_map_zone_satellite_map_helper_004937c0. Remove
   duplicated zone_satellite_map wording. */

void zone_satellite_map_context_helper_004937c0(void)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float *pfVar4;
  int iVar5;
  float *pfVar6;
  bool bVar7;
  float local_90 [16];
  float local_50 [4];
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  double local_28;
  double local_20;
  double local_18;
  float local_10;
  float local_c;
  float local_8;
  
  pfVar4 = (float *)&DAT_004faed8;
  pfVar6 = local_50;
  for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
    *pfVar6 = *pfVar4;
    pfVar4 = pfVar4 + 1;
    pfVar6 = pfVar6 + 1;
  }
  local_50[0] = DAT_006442c0;
  local_30 = DAT_006442c0;
  local_40 = 0.1;
  local_10 = 1000.0;
  local_c = 1000.0;
  local_8 = 16000.0;
  pfVar4 = compose_matrix_or_transform_a(local_90,local_50,(float *)(DAT_006442d4 + 0x40));
  pfVar6 = local_50;
  for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
    *pfVar6 = *pfVar4;
    pfVar4 = pfVar4 + 1;
    pfVar6 = pfVar6 + 1;
  }
  noop_world_object_callback_stub();
  bVar7 = false;
  pfVar4 = DAT_005dd320;
  for (iVar5 = DAT_006442ec; iVar5 != 0 && bVar7 == iVar5 < 0; iVar5 = iVar5 + -1) {
    fVar1 = *pfVar4;
    fVar2 = pfVar4[2];
    fVar3 = local_30 * pfVar4[2] + local_3c * pfVar4[1] + local_50[2] * *pfVar4 + (float)local_18;
    *pfVar4 = local_38 * pfVar4[2] + local_50[3] * pfVar4[1] + local_50[0] * *pfVar4 +
              (float)local_28;
    pfVar4[2] = fVar3;
    fVar3 = fVar3 + local_10;
    if ((int)pfVar4[1] < (int)local_8) {
      local_8 = pfVar4[1];
    }
    pfVar4[1] = local_34 * fVar2 + local_40 * pfVar4[1] + local_50[1] * fVar1 + (float)local_20;
    pfVar4 = pfVar4 + 3;
    if ((int)local_c <= (int)fVar3) {
      local_c = fVar3;
    }
    bVar7 = SBORROW4(iVar5,1);
  }
  DAT_006543ac = 0xc3960000;
  _DAT_006442f4 = local_8 * _DAT_004be8a8;
  _DAT_006543a4 = (local_c - _DAT_004be8b8) - _DAT_004be8b0;
  return;
}


