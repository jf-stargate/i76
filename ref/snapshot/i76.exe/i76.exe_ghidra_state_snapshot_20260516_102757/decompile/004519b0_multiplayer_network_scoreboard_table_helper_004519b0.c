/*
 * Program: i76.exe
 * Function: multiplayer_network_scoreboard_table_helper_004519b0
 * Entry: 004519b0
 * Signature: undefined4 __stdcall multiplayer_network_scoreboard_table_helper_004519b0(void)
 */


/* cgpt readability rename set B v14: Readability pass set B: likely multiplayer_network /
   scoreboard_table_helper based on address neighborhood and prior focused closure context. */

undefined4 multiplayer_network_scoreboard_table_helper_004519b0(void)

{
  undefined4 *puVar1;
  int iVar2;
  int *piVar3;
  
  if (DAT_0053fd80 == -1) {
    return 0;
  }
  puVar1 = &DAT_0053fcb0 + DAT_0053fd80;
  if (DAT_0053fd80 == DAT_0053fd78) {
    DAT_0053fd80 = 0xffffffff;
    return *puVar1;
  }
  iVar2 = DAT_0053fd80 + 1;
  if (iVar2 < DAT_0053fd78) {
    piVar3 = &DAT_0053fcb0 + iVar2;
    do {
      if (*piVar3 != 0) break;
      iVar2 = iVar2 + 1;
      piVar3 = piVar3 + 1;
    } while (iVar2 < DAT_0053fd78);
  }
  DAT_0053fd80 = -1;
  if (iVar2 != DAT_0053fd78) {
    DAT_0053fd80 = iVar2;
  }
  return *puVar1;
}


