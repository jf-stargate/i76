/*
 * Program: i76.exe
 * Function: submit_d3d_unlit_indexed_primitive_batch_context
 * Entry: 00427de0
 * Signature: undefined __cdecl submit_d3d_unlit_indexed_primitive_batch_context(int param_1)
 */


/* cgpt label refinement v18: was d3d_execute_buffer_context_helper_00427de0. Refine generic D3D
   context label to primitive submission context based on adjacent lit-indexed primitive submitters.
    */

void __cdecl submit_d3d_unlit_indexed_primitive_batch_context(int param_1)

{
  short sVar1;
  short *psVar2;
  int iVar3;
  
  sVar1 = *(short *)(&DAT_00524780 + DAT_00526770 * 0x20);
  psVar2 = *(short **)(&DAT_00524778 + DAT_00526770 * 0x20);
  iVar3 = 1;
  *psVar2 = sVar1;
  psVar2[1] = sVar1 + 1;
  psVar2[2] = sVar1 + 2;
  psVar2[3] = 0;
  psVar2 = psVar2 + 4;
  if (1 < param_1 + -2) {
    do {
      *psVar2 = sVar1;
      psVar2[1] = (short)iVar3 + sVar1 + 1;
      psVar2[2] = (short)iVar3 + sVar1 + 2;
      psVar2[3] = 0x1f;
      psVar2 = psVar2 + 4;
      iVar3 = iVar3 + 1;
    } while (iVar3 < param_1 + -2);
  }
  iVar3 = DAT_00526770 * 0x20;
  *(short **)(&DAT_00524778 + iVar3) = psVar2;
  *(int *)(&DAT_00524780 + iVar3) = *(int *)(&DAT_00524780 + iVar3) + param_1;
  return;
}


