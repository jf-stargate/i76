/*
 * Program: i76.exe
 * Function: zone_satellite_map_context_helper_004942f0
 * Entry: 004942f0
 * Signature: undefined __thiscall zone_satellite_map_context_helper_004942f0(void * this, float * param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v20: was zone_satellite_map_zone_satellite_map_helper_004942f0. Remove
   duplicated zone_satellite_map wording. */

void __thiscall zone_satellite_map_context_helper_004942f0(void *this,float *param_1)

{
  int iVar1;
  int iVar2;
  float fVar3;
  uint uVar4;
  float local_10 [4];
  
  fVar3 = *(float *)this + *(float *)((int)this + 0x20) + *(float *)((int)this + 0x10);
  if (fVar3 <= _DAT_004be8ec) {
    uVar4 = (uint)(*(float *)this < *(float *)((int)this + 0x10));
    if (*(float *)(uVar4 * 0x10 + (int)this) < *(float *)((int)this + 0x20)) {
      uVar4 = 2;
    }
    iVar1 = *(int *)(&DAT_004faec8 + uVar4 * 4);
    iVar2 = *(int *)(&DAT_004faec8 + iVar1 * 4);
    fVar3 = SQRT(((*(float *)(uVar4 * 0x10 + (int)this) - _DAT_004be8d8) -
                 *(float *)(iVar1 * 0x10 + (int)this)) - *(float *)(iVar2 * 0x10 + (int)this));
    local_10[uVar4] = fVar3 * _DAT_004be8f0;
    fVar3 = _DAT_004be8f0 / fVar3;
    local_10[3] = (*(float *)((int)this + (iVar2 * 3 + iVar1) * 4) -
                  *(float *)((int)this + (iVar1 * 3 + iVar2) * 4)) * fVar3;
    local_10[iVar1] =
         (*(float *)((int)this + (iVar1 * 3 + uVar4) * 4) +
         *(float *)((int)this + (iVar1 + uVar4 * 3) * 4)) * fVar3;
    local_10[iVar2] =
         (*(float *)((int)this + (uVar4 + iVar2 * 3) * 4) +
         *(float *)((int)this + (iVar2 + uVar4 * 3) * 4)) * fVar3;
  }
  else {
    local_10[3] = SQRT(fVar3 - _DAT_004be8d8);
    fVar3 = _DAT_004be8f0 / local_10[3];
    local_10[3] = local_10[3] * _DAT_004be8f0;
    local_10[0] = (*(float *)((int)this + 0x1c) - *(float *)((int)this + 0x14)) * fVar3;
    local_10[1] = (*(float *)((int)this + 8) - *(float *)((int)this + 0x18)) * fVar3;
    local_10[2] = (*(float *)((int)this + 0xc) - *(float *)((int)this + 4)) * fVar3;
  }
  *param_1 = local_10[0];
  param_1[1] = local_10[1];
  param_1[2] = local_10[2];
  param_1[3] = local_10[3];
  return;
}


