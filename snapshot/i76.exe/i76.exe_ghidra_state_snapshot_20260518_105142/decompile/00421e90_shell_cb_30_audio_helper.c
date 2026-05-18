/*
 * Program: i76.exe
 * Function: shell_cb_30_audio_helper
 * Entry: 00421e90
 * Signature: undefined4 __cdecl shell_cb_30_audio_helper(uint param_1)
 */


/* [cgpt i76.exe shell callback rename v2; confidence=high] ShellMain callback slot +0x30. Finds an
   audio object by ID and stops/releases its active DirectSound buffer when appropriate. */

undefined4 __cdecl shell_cb_30_audio_helper(uint param_1)

{
  int *piVar1;
  uint uVar2;
  int *piVar3;
  
  if (DAT_00524564 != 0) {
    for (piVar3 = *(int **)(DAT_00524564 + 0x1c); piVar3 != (int *)0x0; piVar3 = (int *)*piVar3) {
      if ((piVar3[0x15] != 0) && (piVar3[0x13] == param_1)) goto LAB_00421ed7;
    }
    for (piVar3 = *(int **)(DAT_00524564 + 0x20); piVar3 != (int *)0x0; piVar3 = (int *)*piVar3) {
      if ((piVar3[0x15] != 0) && (piVar3[0x13] == param_1)) goto LAB_00421ed7;
    }
  }
  piVar3 = (int *)0x0;
LAB_00421ed7:
  if (piVar3 == (int *)0x0) {
    return 0;
  }
  if (piVar3[0x19] == 0) {
    if ((*(byte *)(piVar3 + 0x1e) & 2) == 0) {
      piVar1 = (int *)piVar3[0x15];
      uVar2 = 0;
      if (piVar1 != (int *)0x0) {
        (**(code **)(*piVar1 + 0x24))(piVar1,&param_1);
        uVar2 = param_1 & 1;
      }
      if (uVar2 != 0) {
        (**(code **)(*(int *)piVar3[0x15] + 0x48))((int *)piVar3[0x15]);
        piVar3[0x1e] = piVar3[0x1e] & 0xfffffffb;
        piVar3[0x18] = piVar3[0x18] + -1;
      }
      move_audio_object_between_active_and_pending_lists(piVar3,(undefined4 *)0x0);
      return 1;
    }
  }
  else {
    release_audio_object_resource_and_buffers(piVar3);
  }
  return 1;
}


