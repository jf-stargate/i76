/*
 * Program: i76.exe
 * Function: fsm_query_enemy_vehicle_within_radius
 * Entry: 0040ab30
 * Signature: undefined4 __cdecl fsm_query_enemy_vehicle_within_radius(int param_1, int * param_2)
 */


/* cgpt rename v10 fsm/ai runtime core cluster: FSM predicate: scans vehicles on other teams and
   returns true if an active enemy is within the supplied radius. */

undefined4 __cdecl fsm_query_enemy_vehicle_within_radius(int param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  uint uVar4;
  int *piVar5;
  float10 fVar6;
  float10 fVar7;
  undefined4 *local_18;
  
  uVar4 = 1;
  local_18 = &DAT_00507ea0;
  piVar5 = &DAT_0051f5d4;
  do {
    if (uVar4 != (*(uint *)(param_1 + 0x10) >> 0x10 & 7)) {
      iVar2 = 0;
      puVar3 = local_18;
      if (0 < *piVar5) {
        do {
          iVar1 = *(int *)*puVar3;
          if (((*(byte *)(iVar1 + 0x11) & 2) == 0) &&
             (fVar6 = (float10)*(double *)(iVar1 + 0x40) - (float10)*(double *)(param_1 + 0x40),
             fVar7 = (float10)*(double *)(iVar1 + 0x50) - (float10)*(double *)(param_1 + 0x50),
             fVar7 * fVar7 + fVar6 * (float10)(float)fVar6 < (float10)(*param_2 * *param_2))) {
            return 1;
          }
          iVar2 = iVar2 + 1;
          puVar3 = puVar3 + 1;
        } while (iVar2 < *piVar5);
      }
    }
    piVar5 = piVar5 + 1;
    uVar4 = uVar4 + 1;
    local_18 = local_18 + 0x40;
    if (0x51f5ef < (int)piVar5) {
      return 0;
    }
  } while( true );
}


