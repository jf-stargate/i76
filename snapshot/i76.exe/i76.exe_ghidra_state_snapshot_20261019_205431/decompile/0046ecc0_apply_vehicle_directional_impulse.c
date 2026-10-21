/*
 * Program: i76.exe
 * Function: apply_vehicle_directional_impulse
 * Entry: 0046ecc0
 * Signature: undefined __cdecl apply_vehicle_directional_impulse(int param_1, float * param_2, float param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe vehicle engine/suspension rename v28; confidence=high] Applies a direction-scaled
   impulse into vehicle runtime/physics state. */

void __cdecl apply_vehicle_directional_impulse(int param_1,float *param_2,float param_3)

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
  float fVar10;
  float fVar11;
  float fVar12;
  int iVar13;
  int iVar14;
  
  iVar14 = world_object_has_optional_runtime_flag(param_1);
  if (iVar14 != 0) {
    iVar14 = get_vehicle_runtime_context(param_1);
    iVar14 = *(int *)(iVar14 + 0x398);
    iVar13 = *(int *)(iVar14 + 0x70);
    if (param_3 <= (float)_DAT_004be518) {
      if (param_3 < (float)_DAT_004be528) {
        param_3 = 0.0;
      }
    }
    else {
      param_3 = 1.0;
    }
    fVar1 = *(float *)(iVar14 + 0x2c);
    fVar2 = *(float *)(iVar14 + 0x28);
    fVar3 = *(float *)(iVar14 + 0x34);
    fVar4 = *(float *)(iVar14 + 0x38);
    fVar5 = param_2[2];
    fVar6 = *(float *)(iVar14 + 0x24);
    fVar7 = param_2[1];
    fVar8 = param_2[1];
    fVar9 = *(float *)(iVar14 + 0x30);
    fVar10 = *param_2;
    fVar11 = param_2[2];
    fVar12 = *param_2;
    *(float *)(iVar13 + 0x2c) =
         (*(float *)(iVar14 + 0x18) * *param_2 +
         *(float *)(iVar14 + 0x20) * param_2[2] + *(float *)(iVar14 + 0x1c) * param_2[1]) * param_3
         + *(float *)(iVar13 + 0x2c);
    *(float *)(iVar13 + 0x30) =
         (fVar6 * fVar10 + fVar2 * fVar7 + fVar1 * fVar5) * param_3 + *(float *)(iVar13 + 0x30);
    *(float *)(iVar13 + 0x34) =
         (fVar9 * fVar12 + fVar4 * fVar11 + fVar3 * fVar8) * param_3 + *(float *)(iVar13 + 0x34);
  }
  return;
}


