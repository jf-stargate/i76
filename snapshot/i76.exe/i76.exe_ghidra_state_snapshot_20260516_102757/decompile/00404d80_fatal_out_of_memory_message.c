/*
 * Program: i76.exe
 * Function: fatal_out_of_memory_message
 * Entry: 00404d80
 * Signature: undefined __cdecl fatal_out_of_memory_message(LPCSTR param_1)
 */


/* i76 second-pass rename
   old_name: FUN_00404d80
   suggested_name: fatal_out_of_memory_message
   basis: Shows out-of-memory MessageBox, destroys window, exits. */

void __cdecl fatal_out_of_memory_message(LPCSTR param_1)

{
  if (param_1 == (LPCSTR)0x0) {
    param_1 = (LPCSTR)StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,
                                    s_Sorry__there_is_not_enough_memor_004c24ac);
  }
  release_and_show_mouse_cursor();
  update_or_clear_input_binding_state_after_poll();
  shutdown_audio_runtime_directsound_cd();
  if (DAT_005dcfa0 != 0) {
    windowed_high_color_error_context_helper_00476190(0x5dcec0);
    if (DAT_005dcf7c != (HWND)0x0) {
      DestroyWindow(DAT_005dcf7c);
    }
  }
  MessageBoxA((HWND)0x0,param_1,s_Interstate__76_Gold_Edition_004c2680,0x10);
                    /* WARNING: Subroutine does not return */
  exit(1);
}


