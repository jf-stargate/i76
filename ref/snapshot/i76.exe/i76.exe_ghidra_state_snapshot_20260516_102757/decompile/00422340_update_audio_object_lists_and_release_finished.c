/*
 * Program: i76.exe
 * Function: update_audio_object_lists_and_release_finished
 * Entry: 00422340
 * Signature: undefined __stdcall update_audio_object_lists_and_release_finished(void)
 */


/* cgpt readability rename v13 set A: Scans audio object lists, releases finished buffers/resources,
   and moves or retires objects based on flags. */

void update_audio_object_lists_and_release_finished(void)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  uint uVar5;
  uint local_4;
  
  if ((DAT_00524564 != 0) && (iVar4 = is_damage_side_effects_suppressed(), iVar4 == 0)) {
    piVar1 = *(int **)(DAT_00524564 + 0x1c);
    while (piVar3 = piVar1, piVar3 != (int *)0x0) {
      piVar1 = (int *)*piVar3;
      if (((*(byte *)(piVar3 + 5) & 8) == 0) || (g_runtime_display_input_mode == 0x20)) {
        if (piVar3 != (int *)0x0) {
          piVar2 = (int *)piVar3[0x15];
          uVar5 = 0;
          if (piVar2 != (int *)0x0) {
            (**(code **)(*piVar2 + 0x24))(piVar2,&local_4);
            uVar5 = local_4 & 1;
          }
          if (uVar5 != 0) {
            (**(code **)(*(int *)piVar3[0x15] + 0x48))((int *)piVar3[0x15]);
            piVar3[0x1e] = piVar3[0x1e] & 0xfffffffb;
            piVar3[0x18] = piVar3[0x18] + -1;
          }
        }
        if ((*(byte *)(piVar3 + 5) & 1) == 0) {
          if ((piVar3[0x19] == 0) || (piVar3[0xf] == 1)) {
            move_audio_object_between_active_and_pending_lists(piVar3,(undefined4 *)0x0);
          }
          else {
            release_audio_object_resource_and_buffers(piVar3);
          }
        }
        else {
          piVar3[0x1e] = piVar3[0x1e] | 8;
        }
      }
    }
  }
  return;
}


