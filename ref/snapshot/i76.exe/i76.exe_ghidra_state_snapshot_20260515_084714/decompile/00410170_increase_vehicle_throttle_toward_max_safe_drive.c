/*
 * Program: i76.exe
 * Function: increase_vehicle_throttle_toward_max_safe_drive
 * Entry: 00410170
 * Signature: undefined __cdecl increase_vehicle_throttle_toward_max_safe_drive(float param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v4: Raises vehicle throttle/drive command toward the safe maximum drive delta. */

void __cdecl increase_vehicle_throttle_toward_max_safe_drive(float param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  float10 fVar4;
  float10 fVar5;
  
  if (param_1 == DAT_005244c8) {
    DAT_005244c4 = 1;
  }
  fVar1 = *(float *)(*(int *)(*(int *)((int)param_1 + 0x70) + 0x108) + 0xa81c);
  iVar3 = get_vehicle_runtime_context((int)param_1);
  fVar2 = *(float *)(iVar3 + 0xe4);
  fVar4 = solve_vehicle_max_drive_brake_delta(param_1,1.0);
  fVar5 = (float10)_DAT_004bc758 - (float10)fVar1 * (float10)_DAT_004bc754;
  fVar4 = (fVar4 - (float10)fVar2) * (float10)fVar1 + (float10)fVar2;
  if (fVar5 < fVar4) {
    fVar4 = (float10)(float)fVar5;
  }
  *(float *)(iVar3 + 0xe4) = (float)fVar4;
  return;
}


