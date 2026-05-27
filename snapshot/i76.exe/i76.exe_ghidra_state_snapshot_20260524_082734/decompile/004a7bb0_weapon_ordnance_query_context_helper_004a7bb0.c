/*
 * Program: i76.exe
 * Function: weapon_ordnance_query_context_helper_004a7bb0
 * Entry: 004a7bb0
 * Signature: undefined __cdecl weapon_ordnance_query_context_helper_004a7bb0(int param_1, float param_2)
 */


/* cgpt label refinement v20: was ordnance_weapon_query_context_helper_004a7bb0. Normalize query
   label ordering. */

void __cdecl weapon_ordnance_query_context_helper_004a7bb0(int param_1,float param_2)

{
  float *pfVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40 [16];
  
  if (param_2 != 0.0) {
    local_70 = (float)*(double *)(param_1 + 0x40);
    local_6c = (float)*(double *)(param_1 + 0x48);
    local_68 = (float)*(double *)(param_1 + 0x50);
    local_64 = local_70;
    local_60 = local_6c;
    local_5c = local_68;
    pfVar1 = (float *)get_world_object_position_vector(&local_58,param_2);
    local_64 = *pfVar1;
    local_58 = local_64 - local_70;
    local_60 = pfVar1[1];
    local_5c = pfVar1[2];
    local_54 = local_60 - local_6c;
    local_50 = local_5c - local_68;
    local_4c = local_58;
    local_48 = local_54;
    local_44 = local_50;
    puVar2 = (undefined4 *)zone_satellite_map_context_helper_00494880(&local_70,&local_4c,local_40);
    puVar4 = (undefined4 *)(param_1 + 0x18);
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar4 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar4 = puVar4 + 1;
    }
  }
  return;
}


