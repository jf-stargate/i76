/*
 * Program: i76.exe
 * Function: reticle_texture_context_helper_00458e30
 * Entry: 00458e30
 * Signature: undefined __cdecl reticle_texture_context_helper_00458e30(float * param_1, int param_2, int param_3)
 */


/* cgpt readability rename set B v14: Readability pass set B: reticle texture context helper based
   on prior focused closure context. */

void __cdecl reticle_texture_context_helper_00458e30(float *param_1,int param_2,int param_3)

{
  int *piVar1;
  float *pfVar2;
  int iVar3;
  float *pfVar4;
  float local_80 [10];
  double local_58;
  double local_50;
  double local_48;
  float local_40 [16];
  
  if (param_2 == param_3) {
    pfVar2 = (float *)&DAT_004faed8;
    pfVar4 = local_80;
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      *pfVar4 = *pfVar2;
      pfVar2 = pfVar2 + 1;
      pfVar4 = pfVar4 + 1;
    }
  }
  else {
    piVar1 = (int *)(param_2 + 0x68);
    pfVar2 = (float *)(param_2 + 0x18);
    pfVar4 = local_80;
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      *pfVar4 = *pfVar2;
      pfVar2 = pfVar2 + 1;
      pfVar4 = pfVar4 + 1;
    }
    iVar3 = *piVar1;
    while ((iVar3 != 0 && (iVar3 = *piVar1, iVar3 != param_3))) {
      if (*(int *)(iVar3 + 100) == param_2) {
        pfVar2 = compose_matrix_or_transform_a(local_40,local_80,(float *)(iVar3 + 0x18));
        pfVar4 = local_80;
        for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
          *pfVar4 = *pfVar2;
          pfVar2 = pfVar2 + 1;
          pfVar4 = pfVar4 + 1;
        }
      }
      param_2 = *piVar1;
      iVar3 = *(int *)(param_2 + 0x68);
      piVar1 = (int *)(param_2 + 0x68);
    }
    pfVar2 = local_80;
    pfVar4 = local_80;
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      *pfVar4 = *pfVar2;
      pfVar2 = pfVar2 + 1;
      pfVar4 = pfVar4 + 1;
    }
  }
  *param_1 = (float)local_58;
  param_1[1] = (float)local_50;
  param_1[2] = (float)local_48;
  return;
}


