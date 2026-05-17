/*
 * Program: i76.exe
 * Function: fsm_query_who_shot
 * Entry: 0040b0f0
 * Signature: undefined __cdecl fsm_query_who_shot(int param_1, int * param_2, int * param_3, int param_4)
 */


/* i76 first-pass rename
   old_name: FUN_0040b0f0
   suggested_name: fsm_query_who_shot
   basis: FSM diagnostic string indicates whoShot query when nobody has shot yet. */

void __cdecl fsm_query_who_shot(int param_1,int *param_2,int *param_3,int param_4)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  uint uVar6;
  uint uVar7;
  char *pcVar8;
  char *pcVar9;
  char local_50 [80];
  
  iVar3 = get_vehicle_runtime_context(param_1);
  iVar3 = get_vehicle_damage_event_state_block(iVar3);
  if (*(int *)(iVar3 + 0xa6e8) == 0) {
    report_chunk_parse_error();
  }
  iVar4 = 0;
  iVar2 = *param_3;
  if (0 < iVar2) {
    piVar5 = (int *)(param_4 + 0x58);
    do {
      if (*piVar5 == *(int *)(iVar3 + 0xa6e8)) {
        *param_2 = iVar4;
        return;
      }
      iVar4 = iVar4 + 1;
      piVar5 = piVar5 + 0x18;
    } while (iVar4 < iVar2);
  }
  sprintf(local_50,s_NoLabel_d_004c2a94,iVar2);
  uVar6 = 0xffffffff;
  pcVar8 = local_50;
  do {
    pcVar9 = pcVar8;
    if (uVar6 == 0) break;
    uVar6 = uVar6 - 1;
    pcVar9 = pcVar8 + 1;
    cVar1 = *pcVar8;
    pcVar8 = pcVar9;
  } while (cVar1 != '\0');
  uVar6 = ~uVar6;
  pcVar8 = pcVar9 + -uVar6;
  pcVar9 = (char *)(*param_3 * 0x60 + param_4);
  for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
    *(undefined4 *)pcVar9 = *(undefined4 *)pcVar8;
    pcVar8 = pcVar8 + 4;
    pcVar9 = pcVar9 + 4;
  }
  for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
    *pcVar9 = *pcVar8;
    pcVar8 = pcVar8 + 1;
    pcVar9 = pcVar9 + 1;
  }
  *(undefined4 *)(*param_3 * 0x60 + 0x58 + param_4) = *(undefined4 *)(iVar3 + 0xa6e8);
  increment_refcount_recursive_for_object_tree
            (*(int *)(*param_3 * 0x60 + 0x58 + param_4),&DAT_004c2a10);
  *param_2 = *param_3;
  *param_3 = *param_3 + 1;
  return;
}


