/*
 * Program: i76.exe
 * Function: get_current_headlight_runtime_state
 * Entry: 00477ac0
 * Signature: undefined4 __stdcall get_current_headlight_runtime_state(void)
 */


/* [cgpt i76.exe geometry/texture rename v8; confidence=medium] Returns current headlight/runtime
   entry field from DAT_004fa0b0 indexed by DAT_0058db00; exact state enum awaits lighting pass. */

undefined4 get_current_headlight_runtime_state(void)

{
  return *(undefined4 *)(&DAT_004fa0b0 + DAT_0058db00 * 0x14);
}


