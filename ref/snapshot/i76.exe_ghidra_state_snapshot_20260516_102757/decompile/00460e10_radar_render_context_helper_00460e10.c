/*
 * Program: i76.exe
 * Function: radar_render_context_helper_00460e10
 * Entry: 00460e10
 * Signature: undefined __cdecl radar_render_context_helper_00460e10(int param_1)
 */


/* cgpt label refinement v19: was radar_classifier_specials_radar_render_helper_00460e10. Shorten
   readability label. */

void __cdecl radar_render_context_helper_00460e10(int param_1)

{
  int iVar1;
  
  if ((((*(int *)(param_1 + 0x70) != 0) &&
       (iVar1 = *(int *)(*(int *)(param_1 + 0x70) + 0x434), iVar1 != 0)) &&
      (iVar1 = *(int *)(iVar1 + 0x70), iVar1 != 0)) && (*(int *)(iVar1 + 0x54) != 0)) {
    *(uint *)(iVar1 + 0xc) =
         *(uint *)(iVar1 + 0xc) & 0xfffffffd | (uint)(((byte)*(uint *)(iVar1 + 0xc) & 2) != 2) << 1;
  }
  return;
}


