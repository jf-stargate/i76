/*
 * Program: i76.exe
 * Function: test_effect_target_forward_alignment
 * Entry: 00436120
 * Signature: undefined4 __cdecl test_effect_target_forward_alignment(int param_1, int param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v3: Compares transformed forward vectors for two effect targets and returns true when
   they are closely aligned. */

undefined4 __cdecl test_effect_target_forward_alignment(int param_1,int param_2)

{
  float *pfVar1;
  int iVar2;
  float *pfVar3;
  float local_80 [6];
  float local_68;
  float local_64;
  float local_60;
  float local_40 [6];
  float local_28;
  float local_24;
  float local_20;
  
  if (((param_2 != 0) && (*(int *)(param_2 + 0x70) != 0)) &&
     ((*(int *)(param_2 + 0x6c) != 1 || ((*(byte *)(*(int *)(param_2 + 0x70) + 0x454) & 1) != 0))))
  {
    pfVar1 = (float *)compute_transform_relative_to_ancestor(local_40,param_1,0);
    pfVar3 = local_40;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *pfVar3 = *pfVar1;
      pfVar1 = pfVar1 + 1;
      pfVar3 = pfVar3 + 1;
    }
    pfVar1 = (float *)compute_transform_relative_to_ancestor(local_80,param_2,0);
    pfVar3 = local_80;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *pfVar3 = *pfVar1;
      pfVar1 = pfVar1 + 1;
      pfVar3 = pfVar3 + 1;
    }
    if ((float)_DAT_004bd000 < ABS(local_60 * local_20 + local_64 * local_24 + local_68 * local_28))
    {
      return 1;
    }
  }
  return 0;
}


