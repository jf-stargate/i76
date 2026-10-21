/*
 * Program: i76.exe
 * Function: copy_class_09_vehicle_transform_matrix
 * Entry: 0046bcc0
 * Signature: undefined __cdecl copy_class_09_vehicle_transform_matrix(undefined4 * param_1, int param_2)
 */


void __cdecl copy_class_09_vehicle_transform_matrix(undefined4 *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  
  iVar1 = get_vehicle_runtime_context(param_2);
  puVar3 = (undefined4 *)(iVar1 + 0xa4);
  for (iVar2 = 0xf; iVar2 != 0; iVar2 = iVar2 + -1) {
    *param_1 = *puVar3;
    puVar3 = puVar3 + 1;
    param_1 = param_1 + 1;
  }
  return;
}


