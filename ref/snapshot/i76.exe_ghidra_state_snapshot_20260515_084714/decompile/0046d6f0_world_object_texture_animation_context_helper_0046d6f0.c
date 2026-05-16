/*
 * Program: i76.exe
 * Function: world_object_texture_animation_context_helper_0046d6f0
 * Entry: 0046d6f0
 * Signature: undefined __cdecl world_object_texture_animation_context_helper_0046d6f0(int param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5, undefined4 param_6)
 */


/* cgpt readability rename set C v15: Readability pass set C: world object texture animation context
   helper based on adjacent named subsystem context. */

void __cdecl
world_object_texture_animation_context_helper_0046d6f0
          (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,
          undefined4 param_6)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x70);
  if (iVar1 != 0) {
    *(undefined4 *)(iVar1 + 0x90) = 1;
    *(undefined4 *)(iVar1 + 0x78) = param_2;
    *(undefined4 *)(iVar1 + 0x7c) = param_3;
    *(undefined4 *)(iVar1 + 0x80) = param_4;
    *(undefined4 *)(iVar1 + 0x94) = param_5;
    *(undefined4 *)(iVar1 + 0x9c) = param_6;
    *(undefined4 *)(iVar1 + 0x98) = param_6;
  }
  return;
}


