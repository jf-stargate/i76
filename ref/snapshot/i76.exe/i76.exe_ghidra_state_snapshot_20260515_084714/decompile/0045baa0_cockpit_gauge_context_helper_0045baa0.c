/*
 * Program: i76.exe
 * Function: cockpit_gauge_context_helper_0045baa0
 * Entry: 0045baa0
 * Signature: undefined4 __cdecl cockpit_gauge_context_helper_0045baa0(float * param_1, undefined4 param_2, int * param_3, int * param_4)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v19: was cockpit_hud_ui_cockpit_gauge_helper_0045baa0. Remove duplicated
   cockpit wording. */

undefined4 __cdecl
cockpit_gauge_context_helper_0045baa0(float *param_1,undefined4 param_2,int *param_3,int *param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  iVar1 = ftol();
  *param_3 = iVar1;
  iVar1 = ftol();
  *param_4 = iVar1;
  if (param_1[2] < _DAT_004bdfe8) {
    if (_DAT_004bdfe8 <= *param_1) {
      iVar1 = ftol();
      *param_3 = iVar1;
    }
    if (*param_1 < _DAT_004bdfe8) {
      iVar1 = ftol();
      *param_3 = iVar1;
    }
    uVar2 = 1;
  }
  iVar1 = ftol();
  if (*param_3 < iVar1) {
    *param_3 = iVar1;
    uVar2 = 1;
  }
  iVar1 = ftol();
  if (iVar1 < *param_3) {
    *param_3 = iVar1;
    uVar2 = 1;
  }
  iVar1 = ftol();
  if (*param_4 < iVar1) {
    *param_4 = iVar1;
    uVar2 = 1;
  }
  iVar1 = ftol();
  if (iVar1 < *param_4) {
    *param_4 = iVar1;
    uVar2 = 1;
  }
  return uVar2;
}


