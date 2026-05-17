/*
 * Program: i76.exe
 * Function: get_engine_loop_sound_flags
 * Entry: 00469d70
 * Signature: undefined4 __cdecl get_engine_loop_sound_flags(int param_1)
 */


/* [cgpt i76.exe vehicle drivetrain/contact renames v33; confidence=medium] Returns the dword
   flag/config value associated with the engine loop sound-table entry. */

undefined4 __cdecl get_engine_loop_sound_flags(int param_1)

{
  if ((param_1 != 0) && (*(int *)(param_1 + 0x2c) != -1)) {
    return *(undefined4 *)(&DAT_00588e08 + *(int *)(param_1 + 0x2c) * 0x60);
  }
  return 0;
}


