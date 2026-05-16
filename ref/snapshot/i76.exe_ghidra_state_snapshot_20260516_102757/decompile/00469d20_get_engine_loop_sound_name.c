/*
 * Program: i76.exe
 * Function: get_engine_loop_sound_name
 * Entry: 00469d20
 * Signature: undefined * __cdecl get_engine_loop_sound_name(int param_1)
 */


/* [cgpt i76.exe vehicle drivetrain/contact renames v33; confidence=high] Returns the engine loop
   sound name from the engine sound table unless the entry is NONE. */

undefined * __cdecl get_engine_loop_sound_name(int param_1)

{
  int iVar1;
  
  if ((param_1 != 0) && (*(int *)(param_1 + 0x2c) != -1)) {
    iVar1 = _stricmp(&DAT_00588e0c + *(int *)(param_1 + 0x2c) * 0x60,s_NONE_004f8678);
    if (iVar1 != 0) {
      return &DAT_00588e0c + *(int *)(param_1 + 0x2c) * 0x60;
    }
  }
  return (undefined *)0x0;
}


