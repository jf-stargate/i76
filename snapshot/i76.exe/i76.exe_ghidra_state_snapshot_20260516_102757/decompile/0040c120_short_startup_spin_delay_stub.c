/*
 * Program: i76.exe
 * Function: short_startup_spin_delay_stub
 * Entry: 0040c120
 * Signature: undefined __stdcall short_startup_spin_delay_stub(void)
 */


/* cgpt rename v7 fsm predicate/bridge cluster: Small startup spin-delay/no-op loop reached from
   winmain_top_level_game_fsm. */

void short_startup_spin_delay_stub(void)

{
  int iVar1;
  
  iVar1 = 0x20;
  do {
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  iVar1 = 5;
  do {
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}


