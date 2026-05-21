/*
 * Program: i76.exe
 * Function: copy_vehicle_runtime_transform_matrix
 * Entry: 004643a0
 * Signature: undefined __cdecl copy_vehicle_runtime_transform_matrix(undefined4 * param_1, int param_2)
 */


/* [cgpt i76.exe vehicle class physics rename v29; confidence=high] Class-id 1 callback that copies
   15 dwords from vehicle runtime +0xa4 to a caller matrix/transform buffer. */

void __cdecl copy_vehicle_runtime_transform_matrix(undefined4 *param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = (undefined4 *)(*(int *)(param_2 + 0x70) + 0xa4);
  for (iVar1 = 0xf; iVar1 != 0; iVar1 = iVar1 + -1) {
    *param_1 = *puVar2;
    puVar2 = puVar2 + 1;
    param_1 = param_1 + 1;
  }
  return;
}


