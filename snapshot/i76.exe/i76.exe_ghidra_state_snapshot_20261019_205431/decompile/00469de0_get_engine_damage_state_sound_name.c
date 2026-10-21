/*
 * Program: i76.exe
 * Function: get_engine_damage_state_sound_name
 * Entry: 00469de0
 * Signature: undefined * __cdecl get_engine_damage_state_sound_name(int * param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe vehicle drivetrain/contact renames v33; confidence=medium-high] Selects an engine
   damage-state sound name from the engine sound table based on current/max condition fraction. */

undefined * __cdecl get_engine_damage_state_sound_name(int *param_1)

{
  int iVar1;
  
  if ((param_1 != (int *)0x0) && (iVar1 = param_1[0xb], iVar1 != -1)) {
    if ((float)*param_1 / (float)param_1[1] <= _DAT_004be258) {
      if ((float)*param_1 / (float)param_1[1] <= _DAT_004be25c) {
        iVar1 = _stricmp(&DAT_00588e4c + iVar1 * 0x60,s_NONE_004f8678);
        if (iVar1 != 0) {
          return &DAT_00588e4c + param_1[0xb] * 0x60;
        }
      }
      else {
        iVar1 = _stricmp(&DAT_00588e38 + iVar1 * 0x60,s_NONE_004f8678);
        if (iVar1 != 0) {
          return &DAT_00588e38 + param_1[0xb] * 0x60;
        }
      }
    }
    else {
      iVar1 = _stricmp(&DAT_00588e26 + iVar1 * 0x60,s_NONE_004f8678);
      if (iVar1 != 0) {
        return &DAT_00588e26 + param_1[0xb] * 0x60;
      }
    }
  }
  return (undefined *)0x0;
}


