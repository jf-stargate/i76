/*
 * Program: i76.exe
 * Function: zone_satellite_map_context_helper_00494170
 * Entry: 00494170
 * Signature: undefined __thiscall zone_satellite_map_context_helper_00494170(void * this, float * param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v20: was zone_satellite_map_zone_satellite_map_helper_00494170. Remove
   duplicated zone_satellite_map wording. */

void __thiscall zone_satellite_map_context_helper_00494170(void *this,float *param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  int iVar10;
  float *pfVar11;
  float local_40 [4];
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  undefined8 local_18;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  fVar1 = *(float *)this * *(float *)this;
  fVar3 = *(float *)((int)this + 4) * *(float *)((int)this + 4);
  fVar4 = *(float *)this * *(float *)((int)this + 4);
  fVar3 = fVar3 + fVar3;
  local_10 = 0;
  local_c = 0;
  local_8 = 0;
  local_4 = 0;
  fVar2 = *(float *)((int)this + 8) * *(float *)((int)this + 8);
  fVar2 = fVar2 + fVar2;
  fVar4 = fVar4 + fVar4;
  fVar5 = *(float *)this * *(float *)((int)this + 8);
  fVar5 = fVar5 + fVar5;
  fVar8 = *(float *)this * *(float *)((int)this + 0xc);
  local_18 = _DAT_004be8e0;
  fVar6 = *(float *)((int)this + 8) * *(float *)((int)this + 4);
  fVar8 = fVar8 + fVar8;
  fVar7 = *(float *)((int)this + 0xc) * *(float *)((int)this + 4);
  fVar9 = _DAT_004be8e8 - (fVar1 + fVar1);
  fVar1 = *(float *)((int)this + 0xc) * *(float *)((int)this + 8);
  fVar6 = fVar6 + fVar6;
  fVar7 = fVar7 + fVar7;
  fVar1 = fVar1 + fVar1;
  local_40[0] = (_DAT_004be8e8 - fVar3) - fVar2;
  local_40[1] = fVar4 - fVar1;
  local_40[2] = fVar7 + fVar5;
  local_40[3] = fVar1 + fVar4;
  local_30 = fVar9 - fVar2;
  local_2c = fVar6 - fVar8;
  local_28 = fVar5 - fVar7;
  local_24 = fVar6 + fVar8;
  local_20 = fVar9 - fVar3;
  pfVar11 = local_40;
  for (iVar10 = 0x10; iVar10 != 0; iVar10 = iVar10 + -1) {
    *param_1 = *pfVar11;
    pfVar11 = pfVar11 + 1;
    param_1 = param_1 + 1;
  }
  return;
}


