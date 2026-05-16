/*
 * Program: i76.exe
 * Function: radar_render_context_helper_00460de0
 * Entry: 00460de0
 * Signature: undefined __cdecl radar_render_context_helper_00460de0(int param_1)
 */


/* cgpt label refinement v19: was radar_classifier_specials_radar_render_helper_00460de0. Shorten
   readability label. */

void __cdecl radar_render_context_helper_00460de0(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  if (((*(int *)(param_1 + 0x70) != 0) &&
      (iVar1 = *(int *)(*(int *)(param_1 + 0x70) + 0x434), iVar1 != 0)) &&
     (puVar2 = *(undefined4 **)(iVar1 + 0x70), puVar2 != (undefined4 *)0x0)) {
    *puVar2 = 1;
  }
  return;
}


