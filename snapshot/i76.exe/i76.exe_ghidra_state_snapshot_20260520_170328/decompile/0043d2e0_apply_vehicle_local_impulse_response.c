/*
 * Program: i76.exe
 * Function: apply_vehicle_local_impulse_response
 * Entry: 0043d2e0
 * Signature: undefined __cdecl apply_vehicle_local_impulse_response(int param_1, float * param_2, float param_3, float param_4, float param_5)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v9 vehicle effect/collision/particle cluster: Applies a local impulse/response vector
   to a vehicle-like runtime object with speed and damping limits. */

void __cdecl
apply_vehicle_local_impulse_response
          (int param_1,float *param_2,float param_3,float param_4,float param_5)

{
  int iVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float *pfVar5;
  int iVar6;
  float *pfVar7;
  float local_8c [2];
  float local_84;
  float local_80 [16];
  float local_40 [16];
  
  pfVar5 = (float *)compose_matrix_or_transform_b((void *)(param_1 + 0x18),local_40);
  pfVar7 = local_80;
  for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
    *pfVar7 = *pfVar5;
    pfVar5 = pfVar5 + 1;
    pfVar7 = pfVar7 + 1;
  }
  transform_vec3_array_by_matrix(local_8c,param_2,1,local_80);
  if (local_8c[0] <= _DAT_004bd148) {
    if (local_84 <= _DAT_004bd148) {
      iVar6 = 2;
    }
    else {
      iVar6 = 0;
    }
  }
  else if (local_84 <= _DAT_004bd148) {
    iVar6 = 3;
  }
  else {
    iVar6 = 1;
  }
  iVar1 = *(int *)(param_1 + 0x70);
  fVar2 = (float)(&DAT_004bd0a4)[iVar6 * 3];
  fVar3 = (float)(&DAT_004bd0a8)[iVar6 * 3];
  *(float *)(iVar1 + 200) = (float)(&DAT_004bd0a0)[iVar6 * 3] * param_3;
  *(float *)(iVar1 + 0xcc) = fVar2 * param_3;
  fVar2 = _DAT_004bd130;
  *(float *)(iVar1 + 0xd0) = fVar3 * param_3;
  if (fVar2 < *(float *)(iVar1 + 0xac)) {
    *(float *)(iVar1 + 0xbc) = *(float *)(iVar1 + 0xbc) * param_5;
    *(float *)(iVar1 + 0xc0) = *(float *)(iVar1 + 0xc0) * param_5;
    *(float *)(iVar1 + 0xc4) = *(float *)(iVar1 + 0xc4) * param_5;
  }
  fVar3 = _DAT_004bd1f0;
  fVar2 = *(float *)(iVar1 + 0xc0) - param_4 * _DAT_004bd1ec;
  *(float *)(iVar1 + 0xc0) = fVar2;
  if (fVar3 < fVar2) {
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


