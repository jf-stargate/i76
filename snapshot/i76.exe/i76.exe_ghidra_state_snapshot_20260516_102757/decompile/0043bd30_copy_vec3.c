/*
 * Program: i76.exe
 * Function: copy_vec3
 * Entry: 0043bd30
 * Signature: undefined __cdecl copy_vec3(undefined4 * param_1, undefined4 * param_2)
 */


/* [cgpt i76.exe vehicle physics integrator rename v31; confidence=high] Copies three dwords/floats
   from source to destination. */

void __cdecl copy_vec3(undefined4 *param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  uVar1 = param_2[1];
  uVar2 = param_2[2];
  *param_1 = *param_2;
  param_1[1] = uVar1;
  param_1[2] = uVar2;
  return;
}


