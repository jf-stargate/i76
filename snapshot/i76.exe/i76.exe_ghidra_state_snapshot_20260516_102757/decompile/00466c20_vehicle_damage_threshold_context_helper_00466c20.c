/*
 * Program: i76.exe
 * Function: vehicle_damage_threshold_context_helper_00466c20
 * Entry: 00466c20
 * Signature: float10 __cdecl vehicle_damage_threshold_context_helper_00466c20(int param_1, int param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set C v15: Readability pass set C: vehicle damage threshold context
   helper based on adjacent named subsystem context. */

float10 __cdecl vehicle_damage_threshold_context_helper_00466c20(int param_1,int param_2)

{
  int iVar1;
  float fVar2;
  float10 fVar3;
  
  iVar1 = *(int *)(param_1 + 0x158 + param_2 * 4);
  if ((iVar1 == 0) || (param_2 == 4)) {
    fVar2 = (float)*(int *)(param_1 + 0x178 + param_2 * 4) * _DAT_004be1d4;
  }
  else {
    fVar2 = (float)*(int *)(param_1 + 0x178 + param_2 * 4) / (float)iVar1;
  }
  iVar1 = *(int *)(param_1 + 0x168 + param_2 * 4);
  if ((iVar1 == 0) || (param_2 == 4)) {
    fVar3 = (float10)*(int *)(param_1 + 0x18c + param_2 * 4) * (float10)_DAT_004be1d4;
  }
  else {
    fVar3 = (float10)*(int *)(param_1 + 0x18c + param_2 * 4) / (float10)iVar1;
  }
  if ((float10)fVar2 <= fVar3) {
    fVar3 = (float10)fVar2;
  }
  return fVar3;
}


