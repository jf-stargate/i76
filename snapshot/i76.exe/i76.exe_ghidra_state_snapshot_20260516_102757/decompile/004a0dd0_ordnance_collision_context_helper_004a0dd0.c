/*
 * Program: i76.exe
 * Function: ordnance_collision_context_helper_004a0dd0
 * Entry: 004a0dd0
 * Signature: undefined __cdecl ordnance_collision_context_helper_004a0dd0(int param_1, float param_2, float param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set D v16: Readability pass set D: ordnance collision context helper
   based on adjacent named subsystem context. */

void __cdecl ordnance_collision_context_helper_004a0dd0(int param_1,float param_2,float param_3)

{
  float *pfVar1;
  int iVar2;
  float *pfVar3;
  float local_c0 [16];
  float local_80 [16];
  float local_40 [16];
  
  pfVar1 = (float *)zone_satellite_map_context_helper_00493da0(local_c0,param_2 * _DAT_004bea44);
  pfVar3 = local_40;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *pfVar3 = *pfVar1;
    pfVar1 = pfVar1 + 1;
    pfVar3 = pfVar3 + 1;
  }
  pfVar1 = (float *)zone_satellite_map_context_helper_00493e00(local_c0,param_3 * _DAT_004bea44);
  pfVar3 = local_80;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *pfVar3 = *pfVar1;
    pfVar1 = pfVar1 + 1;
    pfVar3 = pfVar3 + 1;
  }
  if (_DAT_004bea34 < param_2) {
    pfVar1 = compose_matrix_or_transform_a(local_c0,local_40,(float *)(param_1 + 0x18));
    pfVar3 = (float *)(param_1 + 0x18);
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *pfVar3 = *pfVar1;
      pfVar1 = pfVar1 + 1;
      pfVar3 = pfVar3 + 1;
    }
  }
  if (_DAT_004bea34 < param_3) {
    pfVar1 = compose_matrix_or_transform_a(local_c0,local_80,(float *)(param_1 + 0x18));
    pfVar3 = (float *)(param_1 + 0x18);
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *pfVar3 = *pfVar1;
      pfVar1 = pfVar1 + 1;
      pfVar3 = pfVar3 + 1;
    }
  }
  return;
}


