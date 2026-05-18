/*
 * Program: i76.exe
 * Function: copy_transform_forward_vector
 * Entry: 0043bcf0
 * Signature: undefined __cdecl copy_transform_forward_vector(undefined4 * param_1, int param_2)
 */


/* [cgpt i76.exe vehicle physics integrator rename v31; confidence=medium] Copies the forward/axis
   vector at transform offsets +0x0c/+0x10/+0x14. */

void __cdecl copy_transform_forward_vector(undefined4 *param_1,int param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  uVar1 = *(undefined4 *)(param_2 + 0x10);
  uVar2 = *(undefined4 *)(param_2 + 0x14);
  *param_1 = *(undefined4 *)(param_2 + 0xc);
  param_1[1] = uVar1;
  param_1[2] = uVar2;
  return;
}


