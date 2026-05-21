/*
 * Program: i76.exe
 * Function: get_engine_damage_state_sound_duration
 * Entry: 00469eb0
 * Signature: float10 __cdecl get_engine_damage_state_sound_duration(int * param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe vehicle drivetrain/contact renames v33; confidence=medium-high] Selects an engine
   damage-state sound duration/timing scalar based on current/max condition fraction. */

float10 __cdecl get_engine_damage_state_sound_duration(int *param_1)

{
  int iVar1;
  
  if ((param_1 == (int *)0x0) || (iVar1 = param_1[0xb], iVar1 == -1)) {
    return (float10)_DAT_004be260;
  }
  if (_DAT_004be258 < (float)*param_1 / (float)param_1[1]) {
    return (float10)*(float *)(&DAT_00588e34 + iVar1 * 0x60);
  }
  if (_DAT_004be25c < (float)*param_1 / (float)param_1[1]) {
    return (float10)*(float *)(&DAT_00588e48 + iVar1 * 0x60);
  }
  return (float10)*(float *)(&DAT_00588e5c + iVar1 * 0x60);
}


