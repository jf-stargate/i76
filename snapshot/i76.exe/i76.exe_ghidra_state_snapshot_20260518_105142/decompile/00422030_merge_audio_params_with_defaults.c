/*
 * Program: i76.exe
 * Function: merge_audio_params_with_defaults
 * Entry: 00422030
 * Signature: undefined __cdecl merge_audio_params_with_defaults(int param_1, int param_2)
 */


/* cgpt rename v3: Merges audio parameter fields into an existing parameter block, preserving or
   defaulting sentinel -1 fields. */

void __cdecl merge_audio_params_with_defaults(int param_1,int param_2)

{
  if ((param_1 != 0) || (param_2 != 0)) {
    if ((param_1 != param_2) && (*(int *)(param_1 + 4) != -1)) {
      *(int *)(param_2 + 4) = *(int *)(param_2 + 4) + *(int *)(param_1 + 4);
    }
    if (*(int *)(param_1 + 8) == -1) {
      if (*(int *)(param_2 + 8) == -1) {
        *(undefined4 *)(param_2 + 8) = 1;
      }
    }
    else {
      *(int *)(param_2 + 8) = *(int *)(param_1 + 8);
    }
    if (*(int *)(param_1 + 0xc) == -1) {
      if (*(int *)(param_2 + 0xc) == -1) {
        *(undefined4 *)(param_2 + 0xc) = 0;
      }
    }
    else {
      *(int *)(param_2 + 0xc) = *(int *)(param_1 + 0xc);
    }
    if (*(int *)(param_1 + 0x14) == -1) {
      if (*(int *)(param_2 + 0x14) == -1) {
        *(undefined4 *)(param_2 + 0x14) = 0;
      }
    }
    else {
      *(int *)(param_2 + 0x14) = *(int *)(param_1 + 0x14);
    }
    if (*(int *)(param_1 + 0x10) != -1) {
      *(int *)(param_2 + 0x10) = *(int *)(param_1 + 0x10);
      return;
    }
    if (*(int *)(param_2 + 0x10) == -1) {
      *(undefined4 *)(param_2 + 0x10) = 100;
    }
  }
  return;
}


