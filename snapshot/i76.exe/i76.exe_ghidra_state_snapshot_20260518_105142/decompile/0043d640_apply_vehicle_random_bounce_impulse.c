/*
 * Program: i76.exe
 * Function: apply_vehicle_random_bounce_impulse
 * Entry: 0043d640
 * Signature: undefined __cdecl apply_vehicle_random_bounce_impulse(int param_1, float param_2, float param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe vehicle drivetrain/contact renames v33; confidence=medium-high] Applies randomized
   bounce/impact impulse to vehicle velocity fields and marks an impact/bounce flag. */

void __cdecl apply_vehicle_random_bounce_impulse(int param_1,float param_2,float param_3)

{
  int iVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  
  uVar5 = rand();
  uVar7 = (int)uVar5 >> 0x1f;
  iVar1 = *(int *)(param_1 + 0x70);
  iVar6 = ((uVar5 ^ uVar7) - uVar7 & 3 ^ uVar7) - uVar7;
  fVar2 = (float)(&DAT_004bd0a4)[iVar6 * 3];
  fVar3 = (float)(&DAT_004bd0a8)[iVar6 * 3];
  *(float *)(iVar1 + 200) = (float)(&DAT_004bd0a0)[iVar6 * 3] * param_2;
  *(float *)(iVar1 + 0xcc) = fVar2 * param_2;
  fVar2 = param_3 * _DAT_004bd1f8;
  *(float *)(iVar1 + 0xd0) = fVar3 * param_2;
  fVar2 = *(float *)(iVar1 + 0xc0) - fVar2;
  *(float *)(iVar1 + 0xc0) = fVar2;
  if (_DAT_004bd1f0 < fVar2) {
    *(undefined4 *)(iVar1 + 0xc0) = 0x41a00000;
  }
  fVar4 = _DAT_004bd150;
  fVar2 = SQRT(*(float *)(iVar1 + 0xc4) * *(float *)(iVar1 + 0xc4) +
               *(float *)(iVar1 + 0xc0) * *(float *)(iVar1 + 0xc0) +
               *(float *)(iVar1 + 0xbc) * *(float *)(iVar1 + 0xbc));
  *(float *)(iVar1 + 0xac) = fVar2;
  fVar3 = _DAT_004bd188;
  if (fVar4 < fVar2) {
    fVar3 = _DAT_004bd134 / fVar2;
  }
  *(float *)(iVar1 + 0xb0) = fVar3;
  *(uint *)(iVar1 + 0x454) = *(uint *)(iVar1 + 0x454) | 4;
  return;
}


