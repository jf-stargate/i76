/*
 * Program: i76.exe
 * Function: ordnance_projectile_update_context_helper_004a06f0
 * Entry: 004a06f0
 * Signature: undefined __cdecl ordnance_projectile_update_context_helper_004a06f0(int param_1, int param_2, int param_3)
 */


/* cgpt readability rename set D v16: Readability pass set D: ordnance projectile update context
   helper based on adjacent named subsystem context. */

void __cdecl ordnance_projectile_update_context_helper_004a06f0(int param_1,int param_2,int param_3)

{
  int iVar1;
  
  iVar1 = *(int *)(param_3 + 0x68);
  if (iVar1 != 0) {
    if (*(int *)(iVar1 + 100) == param_3) {
      *(undefined4 *)(iVar1 + 100) = *(undefined4 *)(param_3 + 0x60);
    }
    if (*(int *)(*(int *)(param_3 + 0x68) + 0x60) == param_3) {
      *(undefined4 *)(*(int *)(param_3 + 0x68) + 0x60) = *(undefined4 *)(param_3 + 0x60);
    }
  }
  if (*(int *)(param_3 + 0x60) != 0) {
    *(undefined4 *)(*(int *)(param_3 + 0x60) + 0x68) = *(undefined4 *)(param_3 + 0x68);
  }
  if (param_2 == 0) {
    (&DAT_006552a4)[param_1 * 0x34] = (&DAT_006552a4)[param_1 * 0x34] + -1;
  }
  else {
    if (param_2 == 1) {
      if (param_3 == (&DAT_00655290)[param_1 * 0x34]) {
        (&DAT_00655290)[param_1 * 0x34] = *(undefined4 *)(param_3 + 0x60);
      }
      (&DAT_006552a8)[param_1 * 0x34] = (&DAT_006552a8)[param_1 * 0x34] + -1;
      *(undefined4 *)(param_3 + 100) = 0;
      *(undefined4 *)(param_3 + 0x60) = 0;
      *(undefined4 *)(param_3 + 0x68) = 0;
      return;
    }
    if (param_2 == 2) {
      if (param_3 == (&DAT_00655294)[param_1 * 0x34]) {
        (&DAT_00655294)[param_1 * 0x34] = *(undefined4 *)(param_3 + 0x60);
      }
      (&DAT_006552a0)[param_1 * 0x34] = (&DAT_006552a0)[param_1 * 0x34] + -1;
      *(undefined4 *)(param_3 + 100) = 0;
      *(undefined4 *)(param_3 + 0x60) = 0;
      *(undefined4 *)(param_3 + 0x68) = 0;
      return;
    }
  }
  *(undefined4 *)(param_3 + 100) = 0;
  *(undefined4 *)(param_3 + 0x60) = 0;
  *(undefined4 *)(param_3 + 0x68) = 0;
  return;
}


