/*
 * Program: i76.exe
 * Function: fsm_get_car_weapon_info_indexed
 * Entry: 00409de0
 * Signature: undefined __stdcall fsm_get_car_weapon_info_indexed(void)
 */


/* cgpt whole-binary semantic rename v1: string evidence: Could not get weapon info in car %d %d %d
    */

void fsm_get_car_weapon_info_indexed(void)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  int *piVar6;
  undefined4 *puVar7;
  int *piVar8;
  int local_1c;
  int *local_10;
  undefined4 *local_c;
  
  local_c = &DAT_00507da0;
  local_10 = &DAT_0051f5d0;
  do {
    iVar2 = *local_10;
    local_1c = 0;
    puVar7 = local_c;
    if (0 < iVar2) {
      do {
        iVar3 = get_vehicle_runtime_context(*(int *)*puVar7);
        piVar4 = (int *)get_vehicle_damage_event_state_block(iVar3);
        piVar1 = piVar4 + 0x29c6;
        iVar3 = collect_vehicle_weapon_runtime_slots(*(int *)*puVar7,piVar1);
        if (iVar3 == 1) {
          iVar3 = 0;
          if (0 < *piVar1) {
            piVar8 = piVar4 + 0x29c7;
            piVar6 = piVar4 + 0x29ce;
            do {
              iVar5 = copy_weapon_runtime_state_summary(*piVar8,piVar6);
              if (iVar5 != 1) {
                report_error();
              }
              iVar3 = iVar3 + 1;
              piVar8 = piVar8 + 1;
              piVar6 = piVar6 + 8;
            } while (iVar3 < *piVar1);
          }
        }
        else {
          *piVar1 = 0;
        }
        collect_forward_facing_vehicle_weapon_slots(*(int *)*puVar7,piVar4);
        local_1c = local_1c + 1;
        puVar7 = puVar7 + 1;
      } while (local_1c < iVar2);
    }
    local_10 = local_10 + 1;
    local_c = local_c + 0x40;
  } while ((int)local_10 < 0x51f5f0);
  return;
}


