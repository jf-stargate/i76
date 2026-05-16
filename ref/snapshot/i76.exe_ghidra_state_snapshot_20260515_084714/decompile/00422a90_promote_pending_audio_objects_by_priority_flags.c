/*
 * Program: i76.exe
 * Function: promote_pending_audio_objects_by_priority_flags
 * Entry: 00422a90
 * Signature: undefined __stdcall promote_pending_audio_objects_by_priority_flags(void)
 */


/* cgpt readability rename v13 set A: Promotes pending audio objects into the active list according
   to flags, priority, and active object count limit. */

void promote_pending_audio_objects_by_priority_flags(void)

{
  int *piVar1;
  uint uVar2;
  int *piVar3;
  int iVar4;
  char cVar5;
  undefined3 extraout_var;
  int iVar6;
  
  if (*(int *)(DAT_00524564 + 0xc) < *(int *)(DAT_00524564 + 0x10)) {
    piVar1 = *(int **)(DAT_00524564 + 0x20);
    iVar4 = DAT_00524564;
    do {
      do {
        do {
          piVar3 = piVar1;
          if (piVar3 == (int *)0x0) {
            return;
          }
          piVar1 = (int *)*piVar3;
          iVar6 = 0;
        } while (piVar3[0xf] == 0);
        uVar2 = piVar3[0x1e];
        if ((uVar2 & 0x80) == 0) {
          if ((uVar2 & 0x20) == 0) {
            if ((uVar2 & 0x40) == 0) {
              if ((uVar2 & 0x100) != 0) {
                iVar6 = 0x100;
              }
            }
            else {
              iVar6 = 0x40;
            }
          }
          else {
            iVar6 = 0x20;
          }
        }
        else if ((((piVar3[5] & 2U) != 0) && (*(int *)(iVar4 + 0x14) != 0)) ||
                (((piVar3[5] & 4U) != 0 && (*(int *)(iVar4 + 0x18) != 0)))) {
          iVar6 = 0x80;
        }
      } while (iVar6 == 0);
      cVar5 = evaluate_audio_object_priority_distance_state(piVar3);
      if (CONCAT31(extraout_var,cVar5) != 0) {
        move_audio_object_between_active_and_pending_lists(piVar3,(undefined4 *)0x1);
      }
      iVar4 = DAT_00524564;
    } while (*(int *)(DAT_00524564 + 0xc) < *(int *)(DAT_00524564 + 0x10));
  }
  return;
}


