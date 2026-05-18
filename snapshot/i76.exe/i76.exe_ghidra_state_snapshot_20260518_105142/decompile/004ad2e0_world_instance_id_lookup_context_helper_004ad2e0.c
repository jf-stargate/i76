/*
 * Program: i76.exe
 * Function: world_instance_id_lookup_context_helper_004ad2e0
 * Entry: 004ad2e0
 * Signature: int __cdecl world_instance_id_lookup_context_helper_004ad2e0(int param_1, float * param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set E v17: Readability pass set E: world instance id lookup context
   helper based on adjacent named subsystem context. */

int __cdecl world_instance_id_lookup_context_helper_004ad2e0(int param_1,float *param_2)

{
  float *pfVar1;
  float *pfVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = *(int *)(param_1 + 0x70);
  pfVar1 = (float *)(iVar3 + 0x18);
  *pfVar1 = *param_2;
  *(float *)(iVar3 + 0x1c) = param_2[1];
  *(float *)(iVar3 + 0x20) = param_2[2];
  pfVar2 = (float *)(&DAT_005da7c0 + DAT_005da7b8);
  DAT_005da7b8 = (DAT_005da7b8 + 1) % 0xfb;
  *pfVar1 = *pfVar1 - *pfVar2 * _DAT_004bec74;
  pfVar2 = (float *)(&DAT_005da7c0 + DAT_005da7b8);
  DAT_005da7b8 = (DAT_005da7b8 + 1) % 0xfb;
  *(float *)(iVar3 + 0x1c) = *(float *)(iVar3 + 0x1c) - *pfVar2 * _DAT_004bec74;
  pfVar2 = (float *)(&DAT_005da7c0 + DAT_005da7b8);
  DAT_005da7b8 = (DAT_005da7b8 + 1) % 0xfb;
  *(float *)(iVar3 + 0x20) = *(float *)(iVar3 + 0x20) - *pfVar2 * _DAT_004bec74;
  *(float *)(iVar3 + 8) =
       SQRT(*(float *)(iVar3 + 0x20) * *(float *)(iVar3 + 0x20) +
            *(float *)(iVar3 + 0x1c) * *(float *)(iVar3 + 0x1c) + *pfVar1 * *pfVar1);
  pfVar1 = (float *)(&DAT_005da7c0 + DAT_005da7b8);
  DAT_005da7b8 = (DAT_005da7b8 + 1) % 0xfb;
  *(float *)(iVar3 + 0x24) = *pfVar1 * _DAT_004bec78;
  pfVar1 = (float *)(&DAT_005da7c0 + DAT_005da7b8);
  DAT_005da7b8 = (DAT_005da7b8 + 1) % 0xfb;
  *(float *)(iVar3 + 0x28) = *pfVar1 * _DAT_004bec78;
  pfVar1 = (float *)(&DAT_005da7c0 + DAT_005da7b8);
  iVar4 = DAT_005da7b8 + 1;
  DAT_005da7b8 = iVar4 % 0xfb;
  *(float *)(iVar3 + 0x2c) = *pfVar1 * _DAT_004bec78;
  return iVar4 / 0xfb;
}


