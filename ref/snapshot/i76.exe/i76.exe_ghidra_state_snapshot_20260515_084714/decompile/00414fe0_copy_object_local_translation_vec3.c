/*
 * Program: i76.exe
 * Function: copy_object_local_translation_vec3
 * Entry: 00414fe0
 * Signature: undefined __cdecl copy_object_local_translation_vec3(undefined4 * param_1, int param_2)
 */


/* cgpt rename v12 fsm/roadwar/path cluster: Copies three float/vector fields from object/transform
   offsets +0x18/+0x1c/+0x20 into an output vector. */

void __cdecl copy_object_local_translation_vec3(undefined4 *param_1,int param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  uVar1 = *(undefined4 *)(param_2 + 0x1c);
  uVar2 = *(undefined4 *)(param_2 + 0x20);
  *param_1 = *(undefined4 *)(param_2 + 0x18);
  param_1[1] = uVar1;
  param_1[2] = uVar2;
  return;
}


