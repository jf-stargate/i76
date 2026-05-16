/*
 * Program: i76.exe
 * Function: radar_render_context_helper_00461430
 * Entry: 00461430
 * Signature: undefined __cdecl radar_render_context_helper_00461430(int param_1, undefined4 param_2, int param_3)
 */


/* cgpt label refinement v19: was radar_classifier_specials_radar_render_helper_00461430. Shorten
   readability label. */

void __cdecl radar_render_context_helper_00461430(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  
  if ((((param_1 != 0) && (*(int *)(param_1 + 0x70) != 0)) &&
      (iVar1 = *(int *)(*(int *)(param_1 + 0x70) + 0x434), iVar1 != 0)) &&
     (iVar1 = *(int *)(iVar1 + 0x70), iVar1 != 0)) {
    if (param_3 == 1) {
      *(undefined4 *)(iVar1 + 0x5c) = param_2;
    }
    if (param_3 == 2) {
      *(undefined4 *)(iVar1 + 0x60) = param_2;
    }
    if (param_3 == 4) {
      *(undefined4 *)(iVar1 + 100) = param_2;
    }
  }
  return;
}


