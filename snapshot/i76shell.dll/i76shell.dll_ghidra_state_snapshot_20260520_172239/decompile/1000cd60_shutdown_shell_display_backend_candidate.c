/*
 * Program: i76shell.dll
 * Function: shutdown_shell_display_backend_candidate
 * Entry: 1000cd60
 * Signature: undefined __stdcall shutdown_shell_display_backend_candidate(void)
 */


void shutdown_shell_display_backend_candidate(void)

{
  if (DAT_100533dc != 0) {
    (**(code **)(DAT_100533dc + 0x14))();
  }
  if (DAT_100533d8 != 0) {
    (**(code **)(DAT_100533d8 + 0x10))();
  }
  DAT_100442f4 = 1;
  return;
}


