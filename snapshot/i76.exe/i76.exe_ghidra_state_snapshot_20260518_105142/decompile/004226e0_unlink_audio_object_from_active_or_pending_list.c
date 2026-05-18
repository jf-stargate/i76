/*
 * Program: i76.exe
 * Function: unlink_audio_object_from_active_or_pending_list
 * Entry: 004226e0
 * Signature: undefined __cdecl unlink_audio_object_from_active_or_pending_list(undefined4 * param_1)
 */


/* cgpt rename v4: Removes an audio object from the active/pending audio list selected by low
   playback-state bits and updates active-list count. */

void __cdecl unlink_audio_object_from_active_or_pending_list(undefined4 *param_1)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  uint uVar5;
  int *piVar6;
  
  uVar5 = param_1[0x1e] & 3;
  if (uVar5 != 0) {
    piVar6 = (int *)(DAT_00524564 + 0x1c);
    if (uVar5 != 1) {
      piVar6 = (int *)(DAT_00524564 + 0x20);
    }
    piVar1 = (int *)*piVar6;
    piVar4 = piVar1;
    piVar3 = piVar1;
    while (piVar2 = piVar4, piVar2 != (int *)0x0) {
      if (param_1 == piVar2) {
        if (piVar2 == piVar1) {
          *piVar6 = *param_1;
        }
        else {
          *piVar3 = *param_1;
        }
        *param_1 = 0;
        break;
      }
      piVar3 = piVar2;
      piVar4 = (int *)*piVar2;
    }
    if (uVar5 == 1) {
      *(int *)(DAT_00524564 + 0xc) = *(int *)(DAT_00524564 + 0xc) + -1;
    }
    param_1[0x1e] = param_1[0x1e] & ~uVar5;
  }
  return;
}


