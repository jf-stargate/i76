/*
 * Program: i76.exe
 * Function: copy_default_class_07_transform_matrix
 * Entry: 0046d6c0
 * Signature: undefined __cdecl copy_default_class_07_transform_matrix(undefined4 * param_1)
 */


void __cdecl copy_default_class_07_transform_matrix(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 local_3c [15];
  
  effect_target_list_scan_context_helper_004382e0(local_3c);
  puVar2 = local_3c;
  for (iVar1 = 0xf; iVar1 != 0; iVar1 = iVar1 + -1) {
    *param_1 = *puVar2;
    puVar2 = puVar2 + 1;
    param_1 = param_1 + 1;
  }
  return;
}


