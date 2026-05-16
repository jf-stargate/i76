/*
 * Program: i76.exe
 * Function: ordnance_object_release_context_helper_004a05f0
 * Entry: 004a05f0
 * Signature: undefined __cdecl ordnance_object_release_context_helper_004a05f0(int param_1, int param_2, int param_3)
 */


/* cgpt label refinement v20: was ordnance_world_object_release_context_helper_004a05f0. Shorten
   readability label. */

void __cdecl ordnance_object_release_context_helper_004a05f0(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  
  if (param_2 == 0) {
    *(undefined4 *)(param_3 + 0x60) = *(undefined4 *)((&DAT_0065528c)[param_1 * 0x34] + 100);
    if (*(int *)((&DAT_0065528c)[param_1 * 0x34] + 100) != 0) {
      *(int *)(*(int *)((&DAT_0065528c)[param_1 * 0x34] + 100) + 0x68) = param_3;
    }
    *(int *)((&DAT_0065528c)[param_1 * 0x34] + 100) = param_3;
    *(undefined4 *)(param_3 + 0x68) = (&DAT_0065528c)[param_1 * 0x34];
    (&DAT_006552a4)[param_1 * 0x34] = (&DAT_006552a4)[param_1 * 0x34] + 1;
  }
  else {
    if (param_2 == 1) {
      *(undefined4 *)(param_3 + 0x60) = (&DAT_00655290)[param_1 * 0x34];
      if ((&DAT_00655290)[param_1 * 0x34] != 0) {
        *(int *)((&DAT_00655290)[param_1 * 0x34] + 0x68) = param_3;
      }
      (&DAT_00655290)[param_1 * 0x34] = param_3;
      *(undefined4 *)(param_3 + 0x68) = 0;
      (&DAT_006552a8)[param_1 * 0x34] = (&DAT_006552a8)[param_1 * 0x34] + 1;
      return;
    }
    if (param_2 == 2) {
      iVar1 = (&DAT_00655294)[param_1 * 0x34];
      if (iVar1 == 0) {
        (&DAT_00655294)[param_1 * 0x34] = param_3;
        *(undefined4 *)(param_3 + 0x68) = 0;
      }
      else {
        for (iVar2 = *(int *)(iVar1 + 0x60); iVar2 != 0; iVar2 = *(int *)(iVar2 + 0x60)) {
          iVar1 = iVar2;
        }
        *(int *)(iVar1 + 0x60) = param_3;
        *(int *)(param_3 + 0x68) = iVar1;
      }
      *(undefined4 *)(param_3 + 0x60) = 0;
      (&DAT_006552a0)[param_1 * 0x34] = (&DAT_006552a0)[param_1 * 0x34] + 1;
      return;
    }
  }
  return;
}


