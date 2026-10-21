/*
 * Program: i76.exe
 * Function: copy_class_0a_transform_with_runtime_position
 * Entry: 0046f840
 * Signature: undefined __cdecl copy_class_0a_transform_with_runtime_position(undefined4 * param_1, int param_2)
 */


void __cdecl copy_class_0a_transform_with_runtime_position(undefined4 *param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 local_3c [9];
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  
  puVar2 = *(undefined4 **)(param_2 + 0x70);
  effect_target_list_scan_context_helper_004382e0(local_3c);
  local_18 = *puVar2;
  local_14 = puVar2[1];
  local_10 = puVar2[2];
  puVar2 = local_3c;
  for (iVar1 = 0xf; iVar1 != 0; iVar1 = iVar1 + -1) {
    *param_1 = *puVar2;
    puVar2 = puVar2 + 1;
    param_1 = param_1 + 1;
  }
  return;
}


