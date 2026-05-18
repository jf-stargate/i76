/*
 * Program: i76.exe
 * Function: fsm_query_target_not_over_subscribed
 * Entry: 0040ac00
 * Signature: undefined4 __cdecl fsm_query_target_not_over_subscribed(int param_1, int param_2)
 */


/* cgpt rename v10 fsm/ai runtime core cluster: FSM predicate: counts other active vehicles
   targeting the supplied object and rejects when the target's allowed attacker count is reached. */

undefined4 __cdecl fsm_query_target_not_over_subscribed(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  int iVar6;
  int local_10;
  int *local_c;
  undefined4 *local_8;
  
  local_10 = 0;
  iVar3 = is_vehicle_or_actor_runtime_world_object(param_2);
  if (iVar3 == 0) {
    return 1;
  }
  local_8 = &DAT_00507da0;
  local_c = &DAT_0051f5d0;
  iVar3 = *(int *)(*(int *)(*(int *)(param_2 + 0x70) + 0x108) + 0xa948);
  do {
    iVar1 = *local_c;
    iVar6 = 0;
    puVar5 = local_8;
    if (0 < iVar1) {
      do {
        iVar2 = *(int *)*puVar5;
        if ((((iVar2 != param_2) && (iVar2 != param_1)) &&
            (iVar4 = get_vehicle_runtime_context(iVar2), (*(byte *)(iVar4 + 0x454) & 0x20) == 0)) &&
           ((*(int *)(*(int *)(*(int *)(iVar2 + 0x70) + 0x108) + 0xa998) == param_2 &&
            (local_10 = local_10 + 1, iVar3 <= local_10)))) {
          return 0;
        }
        iVar6 = iVar6 + 1;
        puVar5 = puVar5 + 1;
      } while (iVar6 < iVar1);
    }
    local_c = local_c + 1;
    local_8 = local_8 + 0x40;
    if (0x51f5ef < (int)local_c) {
      return 1;
    }
  } while( true );
}


