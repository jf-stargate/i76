/*
 * Program: i76.exe
 * Function: get_tick_count_wrapper_c
 * Entry: 0049c920
 * Signature: undefined __stdcall get_tick_count_wrapper_c(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* i76 first-pass rename
   old_name: FUN_0049c920
   suggested_name: get_tick_count_wrapper_c
   basis: Small GetTickCount wrapper in utility/timing area. */

void get_tick_count_wrapper_c(void)

{
  float fVar1;
  bool bVar2;
  DWORD DVar3;
  int iVar4;
  undefined3 extraout_var;
  
  DAT_005a7e1c = DAT_005a7e1c + 1;
  DVar3 = GetTickCount();
  fVar1 = (float)DVar3 * _DAT_004be994;
  if (((byte)g_runtime_display_input_mode & 0x3e) != 0) {
    iVar4 = is_damage_side_effects_suppressed();
    if (iVar4 == 0) {
      _DAT_004fe420 = 0.0;
      _DAT_005a7e10 = fVar1;
      DAT_004fe428 = 0.0;
      DAT_004fe42c = 1e+30;
      _DAT_004fe424 = 1e+30;
      return;
    }
  }
  DAT_004fe428 = fVar1 - _DAT_005a7e10;
  if (DAT_005a7e18 < DAT_004be990) {
    DAT_005a7e18 = DAT_005a7e18 + 1;
  }
  else {
    _DAT_005a7e14 = _DAT_005a7e14 + DAT_004fe428;
  }
  iVar4 = is_damage_side_effects_suppressed();
  if (iVar4 == 0) {
    if (_DAT_004be9ac <= DAT_004fe428) {
      if (_DAT_004be9b0 < DAT_004fe428) {
        DAT_004fe428 = 0.2;
      }
    }
    else {
      DAT_004fe428 = 0.001;
    }
  }
  _DAT_005a7e74 = _DAT_005a7e74 + DAT_004fe428;
  if ((DAT_004fe428 <= _DAT_004be9b4) || (_DAT_004be9b8 <= DAT_004fe428)) {
    DAT_004fe42c = _DAT_004be9a4 / DAT_004fe428;
  }
  else {
    DAT_004fe42c = 1e+30;
  }
  _DAT_005a7e10 = fVar1;
  iVar4 = is_damage_side_effects_suppressed();
  if (iVar4 != 0) {
    bVar2 = is_local_multiplayer_sync_player_current();
    if (CONCAT31(extraout_var,bVar2) == 0) {
      if (DAT_005a7e80 == 0) {
        _DAT_004fe420 = DAT_004fe428;
        fVar1 = DAT_004fe428 + g_runtime_time_seconds;
      }
      else {
        _DAT_004fe420 = _DAT_005a7e7c + DAT_004fe428;
        DAT_005a7e80 = 0;
        fVar1 = _DAT_005a7e78 + DAT_004fe428;
        if (_DAT_004fe420 < _DAT_004be998) {
          fVar1 = DAT_004fe428 + _DAT_005a7e78 + DAT_004fe428;
          if (g_runtime_time_seconds <= fVar1) {
            _DAT_004fe420 = fVar1 - g_runtime_time_seconds;
          }
          else {
            _DAT_004fe420 = 0.0;
          }
        }
      }
      g_runtime_time_seconds = fVar1;
      if ((_DAT_004fe420 <= _DAT_004be9b4) || (_DAT_004be9b8 <= _DAT_004fe420)) {
        _DAT_004fe424 = _DAT_004be9a4 / _DAT_004fe420;
      }
      else {
        _DAT_004fe424 = 1e+30;
      }
      goto LAB_0049cbac;
    }
  }
  g_runtime_time_seconds = DAT_004fe428 + g_runtime_time_seconds;
  _DAT_004fe420 = DAT_004fe428;
  _DAT_004fe424 = DAT_004fe42c;
LAB_0049cbac:
  if (_DAT_004be9a4 < _DAT_004fe420) {
    _DAT_004fe420 = 1.0;
    _DAT_004fe424 = 1.0;
  }
  return;
}


