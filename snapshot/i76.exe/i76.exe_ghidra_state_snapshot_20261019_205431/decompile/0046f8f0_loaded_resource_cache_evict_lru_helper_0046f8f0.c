/*
 * Program: i76.exe
 * Function: loaded_resource_cache_evict_lru_helper_0046f8f0
 * Entry: 0046f8f0
 * Signature: undefined __cdecl loaded_resource_cache_evict_lru_helper_0046f8f0(int param_1, float param_2, float param_3, float param_4)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set C v15: Readability pass set C: loaded resource cache evict lru helper
   based on adjacent named subsystem context. */

void __cdecl
loaded_resource_cache_evict_lru_helper_0046f8f0
          (int param_1,float param_2,float param_3,float param_4)

{
  float *pfVar1;
  float fVar2;
  float fVar3;
  
  fVar2 = param_3 * _DAT_004be580;
  pfVar1 = *(float **)(param_1 + 0x70);
  *pfVar1 = param_2 * _DAT_004be580;
  fVar3 = param_4 * _DAT_004be580;
  pfVar1[1] = fVar2;
  pfVar1[2] = fVar3;
  return;
}


