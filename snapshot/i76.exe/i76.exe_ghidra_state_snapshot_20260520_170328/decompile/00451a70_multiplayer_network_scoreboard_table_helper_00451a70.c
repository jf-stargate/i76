/*
 * Program: i76.exe
 * Function: multiplayer_network_scoreboard_table_helper_00451a70
 * Entry: 00451a70
 * Signature: undefined __cdecl multiplayer_network_scoreboard_table_helper_00451a70(int * param_1)
 */


/* cgpt readability rename set B v14: Readability pass set B: likely multiplayer_network /
   scoreboard_table_helper based on address neighborhood and prior focused closure context. */

void __cdecl multiplayer_network_scoreboard_table_helper_00451a70(int *param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  iVar2 = is_vehicle_or_actor_runtime_world_object(*param_1);
  if (iVar2 != 0) {
    iVar2 = 0;
    if (0 < DAT_0053fd78) {
      piVar3 = &DAT_0053fcb0;
      while ((int *)*piVar3 != param_1) {
        iVar2 = iVar2 + 1;
        piVar3 = piVar3 + 1;
        if (DAT_0053fd78 <= iVar2) {
          return;
        }
      }
      iVar1 = DAT_0053fd78 + -1;
      (&DAT_0053fcb0)[iVar2] = 0;
      if (iVar2 == iVar1) {
        DAT_0053fd78 = iVar1;
      }
    }
  }
  return;
}


