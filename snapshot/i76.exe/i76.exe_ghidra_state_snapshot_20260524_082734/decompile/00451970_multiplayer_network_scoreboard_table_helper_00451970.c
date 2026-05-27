/*
 * Program: i76.exe
 * Function: multiplayer_network_scoreboard_table_helper_00451970
 * Entry: 00451970
 * Signature: undefined __stdcall multiplayer_network_scoreboard_table_helper_00451970(void)
 */


/* cgpt readability rename set B v14: Readability pass set B: likely multiplayer_network /
   scoreboard_table_helper based on address neighborhood and prior focused closure context. */

void multiplayer_network_scoreboard_table_helper_00451970(void)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = 0;
  if (0 < DAT_0053fd78) {
    piVar2 = &DAT_0053fcb0;
    do {
      if (*piVar2 != 0) break;
      iVar1 = iVar1 + 1;
      piVar2 = piVar2 + 1;
    } while (iVar1 < DAT_0053fd78);
  }
  DAT_0053fd80 = -1;
  if (iVar1 != DAT_0053fd78) {
    DAT_0053fd80 = iVar1;
  }
  return;
}


