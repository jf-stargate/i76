/*
 * Program: i76.exe
 * Function: target_reticle_context_helper_00458f40
 * Entry: 00458f40
 * Signature: int __cdecl target_reticle_context_helper_00458f40(int param_1, int param_2)
 */


/* cgpt label refinement v19: was cockpit_hud_ui_target_reticle_helper_00458f40. Shorten readability
   label. */

int __cdecl target_reticle_context_helper_00458f40(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  if ((param_1 != 0) && (*(int *)(param_1 + 0x6c) != param_2)) {
    for (iVar1 = *(int *)(param_1 + 100); iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x60)) {
      iVar2 = target_reticle_context_helper_00458f40(iVar1,param_2);
      if (iVar2 != 0) {
        return iVar2;
      }
    }
    param_1 = 0;
  }
  return param_1;
}


