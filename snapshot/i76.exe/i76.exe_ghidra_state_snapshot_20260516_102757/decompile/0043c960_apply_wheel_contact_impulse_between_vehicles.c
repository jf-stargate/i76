/*
 * Program: i76.exe
 * Function: apply_wheel_contact_impulse_between_vehicles
 * Entry: 0043c960
 * Signature: undefined __cdecl apply_wheel_contact_impulse_between_vehicles(int param_1, int param_2, float param_3, int param_4, float * param_5, undefined4 * param_6)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v3: Computes and applies an impulse response between a vehicle and a wheel/contact
   object in local transform space. */

void __cdecl
apply_wheel_contact_impulse_between_vehicles
          (int param_1,int param_2,float param_3,int param_4,float *param_5,undefined4 *param_6)

{
  int iVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float *pfVar7;
  int iVar8;
  int iVar9;
  float fVar10;
  float *pfVar11;
  float local_bc;
  float local_b8;
  float local_b0;
  float local_ac;
  float local_a8;
  float local_a4;
  float local_a0;
  float local_9c;
  float local_98 [4];
  float local_88;
  float local_84;
  float local_80;
  float local_7c;
  float local_78;
  float local_58;
  float local_54;
  float local_50;
  float local_4c [3];
  float local_40 [16];
  
  iVar8 = *(int *)(param_1 + 0x70);
  iVar1 = *(int *)(param_2 + 0x70);
  pfVar7 = (float *)compute_transform_relative_to_ancestor(local_40,param_2,0);
  fVar6 = (float)*(double *)(param_2 + 0x40);
  fVar2 = (float)*(double *)(param_2 + 0x50);
  pfVar11 = local_98;
  for (iVar9 = 0x10; iVar9 != 0; iVar9 = iVar9 + -1) {
    *pfVar11 = *pfVar7;
    pfVar7 = pfVar7 + 1;
    pfVar11 = pfVar11 + 1;
  }
  fVar3 = fVar2 * *(float *)(iVar8 + 200) - fVar6 * *(float *)(iVar8 + 0xd0);
  fVar4 = fVar6 * *(float *)(iVar8 + 0xcc);
  fVar5 = -(fVar2 * *(float *)(iVar8 + 0xcc));
  local_b8 = *(float *)(iVar8 + 0xc0) + fVar4 * local_7c + fVar3 * local_88 + fVar5 * local_98[1];
  fVar10 = *(float *)(iVar8 + 0xc4) + fVar4 * local_78 + fVar3 * local_84 + fVar5 * local_98[2];
  local_bc = *(float *)(iVar8 + 0xbc) + fVar4 * local_80 + fVar3 * local_98[3] + fVar5 * local_98[0]
  ;
  fVar3 = local_bc * local_bc;
  if (((fVar3 < _DAT_004bd14c) && (local_b8 * local_b8 < _DAT_004bd14c)) &&
     (fVar10 * fVar10 < _DAT_004bd14c)) {
    return;
  }
  if (param_4 == 0) {
    fVar10 = -(((fVar10 * local_98[2] + local_b8 * local_98[1] + local_bc * local_98[0]) *
                *(float *)(iVar1 + 0xc) * param_3) /
              SQRT(fVar10 * fVar10 + local_b8 * local_b8 + fVar3));
    local_bc = local_98[0] * fVar10;
    local_b8 = local_98[1] * fVar10;
    fVar10 = local_98[2] * fVar10;
  }
  else {
    fVar3 = -(*(float *)(iVar1 + 0xc) * param_3) /
            SQRT(fVar10 * fVar10 + local_b8 * local_b8 + fVar3);
    local_bc = local_bc * fVar3;
    local_b8 = local_b8 * fVar3;
    fVar10 = fVar10 * fVar3;
  }
  fVar4 = fVar2 * local_80 + fVar6 * local_98[0];
  fVar3 = fVar2 * local_7c + fVar6 * local_98[1];
  fVar2 = fVar2 * local_78 + fVar6 * local_98[2];
  zone_satellite_map_context_helper_00493ca0
            (local_bc,local_b8,fVar10,fVar4,fVar3,fVar2,&local_58,local_4c);
  *param_5 = *param_5 + local_58;
  param_5[1] = param_5[1] + local_54;
  param_5[2] = param_5[2] + local_50;
  local_b0 = fVar2 * local_b8 - fVar3 * fVar10;
  local_ac = fVar4 * fVar10 - fVar2 * local_bc;
  local_a8 = fVar3 * local_bc - fVar4 * local_b8;
  local_a4 = local_b0;
  local_a0 = local_ac;
  local_9c = local_a8;
  iVar8 = mat3_transform_vec3(&local_b0,&local_a4,local_98);
  fVar2 = *(float *)(iVar8 + 4);
  param_6[2] = 0;
  *param_6 = 0;
  param_6[1] = fVar2 + (float)param_6[1];
  return;
}


