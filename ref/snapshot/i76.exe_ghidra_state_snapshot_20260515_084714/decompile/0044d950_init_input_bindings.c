/*
 * Program: i76.exe
 * Function: init_input_bindings
 * Entry: 0044d950
 * Signature: undefined __stdcall init_input_bindings(void)
 */


/* i76 second-pass rename
   old_name: FUN_0044d950
   suggested_name: init_input_bindings
   basis: Loads keyboard/gamekey/input map configuration. */

void init_input_bindings(void)

{
  int iVar1;
  char *_Str1;
  int iVar2;
  
  load_input_map();
  load_gamekey_map();
  iVar2 = 0;
  if (0 < g_input_device_context_count) {
    _Str1 = (char *)&DAT_0053da68;
    do {
      iVar1 = _stricmp(_Str1,s_keyboard_004f4c94);
      if (iVar1 == 0) {
        if ((&DAT_0053da50)[iVar2] == 0) {
          iVar2 = -1;
        }
        goto LAB_0044d99c;
      }
      iVar2 = iVar2 + 1;
      _Str1 = _Str1 + 0x28;
    } while (iVar2 < g_input_device_context_count);
  }
  iVar2 = validate_input_device(s_keyboard_004f4c94);
LAB_0044d99c:
  DAT_0053682c = iVar2;
  (**(code **)((&g_input_device_callback_table)[iVar2] + 0x1c))();
  DAT_00536818 = 0;
  DAT_0053681c = 0;
  return;
}


