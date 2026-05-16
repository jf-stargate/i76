/*
 * Program: i76.exe
 * Function: fsm_get_vehicle_weapon_info
 * Entry: 00409f60
 * Signature: undefined __cdecl fsm_get_vehicle_weapon_info(int param_1)
 */


/* cgpt whole-binary semantic rename v1: string evidence: Could not get weapon info in %d */

void __cdecl fsm_get_vehicle_weapon_info(int param_1)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  int *piVar6;
  
  piVar2 = *(int **)(*(int *)(param_1 + 0x70) + 0x108);
  if (piVar2[0x29c5] != 0) {
    piVar1 = piVar2 + 0x29c6;
    iVar3 = collect_vehicle_weapon_runtime_slots(param_1,piVar1);
    if (iVar3 == 1) {
      iVar3 = 0;
      if (0 < *piVar1) {
        piVar6 = piVar2 + 0x29c7;
        piVar5 = piVar2 + 0x29ce;
        do {
          iVar4 = copy_weapon_runtime_state_summary(*piVar6,piVar5);
          if (iVar4 != 1) {
            report_chunk_parse_error();
          }
          iVar3 = iVar3 + 1;
          piVar6 = piVar6 + 1;
          piVar5 = piVar5 + 8;
        } while (iVar3 < *piVar1);
      }
    }
    else {
      *piVar1 = 0;
    }
    collect_forward_facing_vehicle_weapon_slots(param_1,piVar2);
    piVar2[0x29c5] = 0;
  }
  return;
}


