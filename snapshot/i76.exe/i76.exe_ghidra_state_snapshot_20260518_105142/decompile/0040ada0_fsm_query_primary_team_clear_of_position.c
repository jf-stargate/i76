/*
 * Program: i76.exe
 * Function: fsm_query_primary_team_clear_of_position
 * Entry: 0040ada0
 * Signature: undefined4 __cdecl fsm_query_primary_team_clear_of_position(float * param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v10 fsm/ai runtime core cluster: FSM predicate: checks primary team vehicles against
   a position vector and returns true when all are outside the near threshold. */

undefined4 __cdecl fsm_query_primary_team_clear_of_position(float *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  
  iVar3 = 0;
  if (DAT_0051f5d0 < 1) {
    return 1;
  }
  puVar2 = &DAT_00507da0;
  do {
    iVar1 = *(int *)*puVar2;
    if (*(double *)(iVar1 + 0x40) * (double)*param_1 +
        *(double *)(iVar1 + 0x50) * (double)param_1[2] +
        *(double *)(iVar1 + 0x48) * (double)param_1[1] < (double)_DAT_004bc60c) {
      return 0;
    }
    iVar3 = iVar3 + 1;
    puVar2 = puVar2 + 1;
  } while (iVar3 < DAT_0051f5d0);
  return 1;
}


