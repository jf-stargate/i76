/*
 * Program: i76.exe
 * Function: polygon_renderer_context_helper_00471f00
 * Entry: 00471f00
 * Signature: int __cdecl polygon_renderer_context_helper_00471f00(int * param_1, int param_2)
 */


/* cgpt readability rename set C v15: Readability pass set C: polygon renderer context helper based
   on adjacent named subsystem context. */

int __cdecl polygon_renderer_context_helper_00471f00(int *param_1,int param_2)

{
  int iVar1;
  
  iVar1 = param_1[1];
  if (((iVar1 == 0) || (param_2 == 0)) || (*(int *)(*(int *)(param_2 + 0x3c) + 8) != 1)) {
    iVar1 = *param_1;
  }
  return iVar1;
}


