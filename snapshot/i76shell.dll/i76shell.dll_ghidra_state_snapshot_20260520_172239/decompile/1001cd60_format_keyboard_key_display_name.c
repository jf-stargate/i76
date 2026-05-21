/*
 * Program: i76shell.dll
 * Function: format_keyboard_key_display_name
 * Entry: 1001cd60
 * Signature: undefined4 __cdecl format_keyboard_key_display_name(undefined4 param_1, char * param_2)
 */


undefined4 __cdecl format_keyboard_key_display_name(undefined4 param_1,char *param_2)

{
  param_2[0x58] = '\0';
  param_2[0x59] = '\0';
  param_2[0x5a] = '\0';
  param_2[0x5b] = '\0';
  param_2[0x5c] = 'y';
  param_2[0x5d] = '\0';
  param_2[0x5e] = '\0';
  param_2[0x5f] = '\0';
  sprintf(param_2,s_keyboard_10049b98);
  sprintf(param_2 + 0xc,s_Keyboard_10049ba4);
  sprintf(param_2 + 0x4c,s_keyboard_10049bb0);
  param_2[0x60] = '\0';
  param_2[0x61] = '\0';
  param_2[0x62] = '\0';
  param_2[99] = '\0';
  param_2[100] = '\0';
  param_2[0x65] = '\0';
  param_2[0x66] = '\0';
  param_2[0x67] = '\0';
  *(undefined ***)(param_2 + 0x68) = &PTR_s_Escape_Key_10049628;
  *(undefined ***)(param_2 + 0x6c) = &PTR_s__Esc_10049440;
  param_2[0x70] = '\0';
  param_2[0x71] = '\0';
  param_2[0x72] = '\0';
  param_2[0x73] = '\0';
  return 0;
}


