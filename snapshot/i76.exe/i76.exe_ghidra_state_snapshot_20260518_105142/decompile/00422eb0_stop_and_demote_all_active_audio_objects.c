/*
 * Program: i76.exe
 * Function: stop_and_demote_all_active_audio_objects
 * Entry: 00422eb0
 * Signature: undefined __fastcall stop_and_demote_all_active_audio_objects(uint param_1)
 */


/* cgpt readability rename v13 set A: Stops currently active audio objects, releases playing
   buffers, and moves them to the pending/inactive list. */

void __fastcall stop_and_demote_all_active_audio_objects(uint param_1)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  uint uVar4;
  uint local_4;
  
  if (DAT_00524564 != 0) {
    piVar3 = *(int **)(DAT_00524564 + 0x1c);
    local_4 = param_1;
    while (piVar3 != (int *)0x0) {
      piVar1 = (int *)*piVar3;
      if (piVar3 != (int *)0x0) {
        piVar2 = (int *)piVar3[0x15];
        uVar4 = 0;
        if (piVar2 != (int *)0x0) {
          (**(code **)(*piVar2 + 0x24))(piVar2,&local_4);
          uVar4 = local_4 & 1;
        }
        if (uVar4 != 0) {
          (**(code **)(*(int *)piVar3[0x15] + 0x48))((int *)piVar3[0x15]);
          piVar3[0x1e] = piVar3[0x1e] & 0xfffffffb;
          piVar3[0x18] = piVar3[0x18] + -1;
        }
      }
      move_audio_object_between_active_and_pending_lists(piVar3,(undefined4 *)0x0);
      piVar3 = piVar1;
    }
  }
  return;
}


