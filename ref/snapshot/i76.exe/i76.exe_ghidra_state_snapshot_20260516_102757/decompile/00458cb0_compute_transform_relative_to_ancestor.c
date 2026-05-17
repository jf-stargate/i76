/*
 * Program: i76.exe
 * Function: compute_transform_relative_to_ancestor
 * Entry: 00458cb0
 * Signature: undefined __cdecl compute_transform_relative_to_ancestor(float * param_1, int param_2, int param_3)
 */


/* [cgpt i76.exe geometry/texture rename v8; confidence=high] Composes local 4x4 transforms up the
   +0x68 parent chain until the requested ancestor and writes the resulting matrix. */

void __cdecl compute_transform_relative_to_ancestor(float *param_1,int param_2,int param_3)

{
  float *pfVar1;
  int iVar2;
  float *pfVar3;
  float local_80 [16];
  float local_40 [16];
  
  if (param_2 != param_3) {
    pfVar1 = (float *)(param_2 + 0x18);
    pfVar3 = local_80;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *pfVar3 = *pfVar1;
      pfVar1 = pfVar1 + 1;
      pfVar3 = pfVar3 + 1;
    }
    iVar2 = *(int *)(param_2 + 0x68);
    while ((iVar2 != 0 && (iVar2 != param_3))) {
      if (*(int *)(iVar2 + 100) == param_2) {
        pfVar1 = compose_matrix_or_transform_a(local_40,local_80,(float *)(iVar2 + 0x18));
        pfVar3 = local_80;
        for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
          *pfVar3 = *pfVar1;
          pfVar1 = pfVar1 + 1;
          pfVar3 = pfVar3 + 1;
        }
      }
      param_2 = *(int *)(param_2 + 0x68);
      iVar2 = *(int *)(param_2 + 0x68);
    }
    pfVar1 = local_80;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *param_1 = *pfVar1;
      pfVar1 = pfVar1 + 1;
      param_1 = param_1 + 1;
    }
    return;
  }
  pfVar1 = (float *)&DAT_004faed8;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *param_1 = *pfVar1;
    pfVar1 = pfVar1 + 1;
    param_1 = param_1 + 1;
  }
  return;
}


