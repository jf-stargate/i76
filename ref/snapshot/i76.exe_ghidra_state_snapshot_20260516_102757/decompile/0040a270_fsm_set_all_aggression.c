/*
 * Program: i76.exe
 * Function: fsm_set_all_aggression
 * Entry: 0040a270
 * Signature: undefined __cdecl fsm_set_all_aggression(int param_1)
 */


/* cgpt whole-binary semantic rename v1: string evidence: illigal value in setAllAggresion */

void __cdecl fsm_set_all_aggression(int param_1)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  int *local_8;
  
  piVar2 = (int *)get_active_player_or_camera_world_object_entry();
  if ((0 < param_1) && (param_1 < 6)) {
    piVar4 = &DAT_0051f5d0;
    local_8 = &DAT_00507da0;
    do {
      iVar3 = *piVar4;
      piVar5 = local_8;
      if (0 < iVar3) {
        do {
          piVar1 = (int *)*piVar5;
          if ((piVar1 != (int *)0x0) && (piVar2 != piVar1)) {
            fsm_set_tactics_weights_from_script_indices(*piVar1,&param_1,&param_1);
            *(int *)(*(int *)(*(int *)(*piVar1 + 0x70) + 0x108) + 0xa818) = param_1 + -1;
          }
          iVar3 = iVar3 + -1;
          piVar5 = piVar5 + 1;
        } while (iVar3 != 0);
      }
      piVar4 = piVar4 + 1;
      local_8 = local_8 + 0x40;
    } while ((int)piVar4 < 0x51f5f0);
    return;
  }
  report_chunk_parse_error();
  return;
}


