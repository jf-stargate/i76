/*
 * Program: i76.exe
 * Function: fsm_query_all_other_team_vehicles_flag_0x20_set
 * Entry: 0040aa90
 * Signature: undefined4 __cdecl fsm_query_all_other_team_vehicles_flag_0x20_set(uint param_1)
 */


/* cgpt rename v10 fsm/ai runtime core cluster: FSM predicate: checks all vehicles outside the
   current object's team and returns true only when their runtime flag 0x20 is set. */

undefined4 __cdecl fsm_query_all_other_team_vehicles_flag_0x20_set(uint param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *local_8;
  
  uVar1 = *(uint *)(param_1 + 0x10);
  param_1 = 1;
  local_8 = &DAT_00507ea0;
  piVar4 = &DAT_0051f5d4;
  do {
    if (param_1 != (uVar1 >> 0x10 & 7)) {
      iVar2 = *piVar4;
      iVar5 = 0;
      puVar6 = local_8;
      if (0 < iVar2) {
        do {
          iVar3 = get_vehicle_runtime_context(*(int *)*puVar6);
          if ((*(byte *)(iVar3 + 0x454) & 0x20) == 0) {
            return 0;
          }
          iVar5 = iVar5 + 1;
          puVar6 = puVar6 + 1;
        } while (iVar5 < iVar2);
      }
    }
    piVar4 = piVar4 + 1;
    param_1 = param_1 + 1;
    local_8 = local_8 + 0x40;
  } while ((int)piVar4 < 0x51f5f0);
  return 1;
}


