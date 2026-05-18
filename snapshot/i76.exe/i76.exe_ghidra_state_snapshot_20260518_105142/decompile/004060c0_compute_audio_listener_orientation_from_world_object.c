/*
 * Program: i76.exe
 * Function: compute_audio_listener_orientation_from_world_object
 * Entry: 004060c0
 * Signature: undefined __cdecl compute_audio_listener_orientation_from_world_object(undefined4 * param_1, int * param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v4: Builds a listener/orientation transform from a world object's forward/right
   vectors or the default listener matrix. */

void __cdecl compute_audio_listener_orientation_from_world_object(undefined4 *param_1,int *param_2)

{
  int iVar1;
  float fVar2;
  undefined4 *puVar3;
  int iVar4;
  float *pfVar5;
  float *pfVar6;
  float local_50 [4];
  float local_40 [6];
  float local_28;
  float local_20;
  
  iVar1 = *param_2;
  if (iVar1 == 0) {
    puVar3 = (undefined4 *)zone_satellite_map_context_helper_004942f0(&DAT_004faed8,local_50);
    *param_1 = *puVar3;
    param_1[1] = puVar3[1];
    param_1[2] = puVar3[2];
    param_1[3] = puVar3[3];
    return;
  }
  pfVar5 = (float *)&DAT_004faed8;
  pfVar6 = local_40;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    *pfVar6 = *pfVar5;
    pfVar5 = pfVar5 + 1;
    pfVar6 = pfVar6 + 1;
  }
  local_40[0] = *(float *)(iVar1 + 0x38);
  local_28 = *(float *)(iVar1 + 0x30);
  fVar2 = local_28 * local_28 + local_40[0] * local_40[0];
  if ((float)_DAT_004bc570 <= fVar2) {
    fVar2 = (float)_DAT_004bc578 / SQRT(fVar2);
    local_40[0] = local_40[0] * fVar2;
    local_28 = local_28 * fVar2;
  }
  else {
    local_40[0] = *(float *)(iVar1 + 0x18);
    local_28 = *(float *)(iVar1 + 0x20);
  }
  local_40[2] = -local_28;
  local_20 = local_40[0];
  puVar3 = (undefined4 *)zone_satellite_map_context_helper_004942f0(local_40,local_50);
  *param_1 = *puVar3;
  param_1[1] = puVar3[1];
  param_1[2] = puVar3[2];
  param_1[3] = puVar3[3];
  return;
}


