/*
 * Program: i76shell.dll
 * Function: unlock_shell_surface_after_draw
 * Entry: 100399f0
 * Signature: undefined __fastcall unlock_shell_surface_after_draw(int param_1)
 */


void __fastcall unlock_shell_surface_after_draw(int param_1)

{
  if (DAT_100f6368 != 0) {
    (**(code **)(DAT_100533d8 + 0x24))();
    *(undefined4 *)(param_1 + 0x30) = 0;
  }
  return;
}


