/*
 * Program: i76.exe
 * Function: trim_audio_object_list_to_priority_limit
 * Entry: 00421a60
 * Signature: undefined __cdecl trim_audio_object_list_to_priority_limit(int param_1)
 */


/* cgpt readability rename v13 set A: Walks active audio objects, queues lower-priority objects for
   stop/release, and updates the active audio count limit. */

void __cdecl trim_audio_object_list_to_priority_limit(int param_1)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  int iVar5;
  
  if (DAT_00524564 != 0) {
    if (param_1 == 1) {
      param_1 = 0;
    }
    iVar5 = 0;
    piVar2 = *(int **)(DAT_00524564 + 0x1c);
    piVar3 = (int *)0x0;
    while (piVar2 != (int *)0x0) {
      piVar1 = (int *)*piVar2;
      piVar4 = piVar3;
      if ((param_1 <= iVar5) && (piVar4 = piVar2, (*(byte *)(piVar2 + 5) & 4) == 0)) {
        set_audio_object_playback_flags_and_queue(piVar2,0x20);
        piVar4 = piVar3;
      }
      iVar5 = iVar5 + 1;
      piVar2 = piVar1;
      piVar3 = piVar4;
    }
    *(int *)(DAT_00524564 + 0x10) = param_1;
    if (piVar3 != (int *)0x0) {
      release_audio_world_object_attachment_records(0);
    }
  }
  return;
}


