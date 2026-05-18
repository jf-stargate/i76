/*
 * Program: i76.exe
 * Function: shell_cb_34_audio_helper
 * Entry: 00421f50
 * Signature: uint __cdecl shell_cb_34_audio_helper(int param_1)
 */


/* [cgpt i76.exe shell callback rename v2; confidence=high] ShellMain callback slot +0x34. Finds an
   audio object by ID and returns its active/playing state. */

uint __cdecl shell_cb_34_audio_helper(int param_1)

{
  undefined4 *puVar1;
  
  if (DAT_00524564 != 0) {
    for (puVar1 = *(undefined4 **)(DAT_00524564 + 0x1c); puVar1 != (undefined4 *)0x0;
        puVar1 = (undefined4 *)*puVar1) {
      if ((puVar1[0x15] != 0) && (puVar1[0x13] == param_1)) goto LAB_00421f93;
    }
    for (puVar1 = *(undefined4 **)(DAT_00524564 + 0x20); puVar1 != (undefined4 *)0x0;
        puVar1 = (undefined4 *)*puVar1) {
      if ((puVar1[0x15] != 0) && (puVar1[0x13] == param_1)) goto LAB_00421f93;
    }
  }
  puVar1 = (undefined4 *)0x0;
LAB_00421f93:
  if (puVar1 == (undefined4 *)0x0) {
    return 0;
  }
  return puVar1[0x1e] & 1;
}


