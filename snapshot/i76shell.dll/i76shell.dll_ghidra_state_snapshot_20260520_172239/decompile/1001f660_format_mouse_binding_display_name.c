/*
 * Program: i76shell.dll
 * Function: format_mouse_binding_display_name
 * Entry: 1001f660
 * Signature: undefined4 __cdecl format_mouse_binding_display_name(undefined4 param_1, char * param_2)
 */


undefined4 __cdecl format_mouse_binding_display_name(undefined4 param_1,char *param_2)

{
  param_2[0x58] = '\x02';
  param_2[0x59] = '\0';
  param_2[0x5a] = '\0';
  param_2[0x5b] = '\0';
  param_2[0x5c] = '\x03';
  param_2[0x5d] = '\0';
  param_2[0x5e] = '\0';
  param_2[0x5f] = '\0';
  sprintf(param_2,s_mouse_1004a290);
  sprintf(param_2 + 0xc,s_Mouse_1004a298);
  sprintf(param_2 + 0x4c,s_mouse_1004a2a0);
  *(undefined ***)(param_2 + 0x60) = &PTR_s_Mouse_Down_Up_Movement_1004a240;
  *(undefined ***)(param_2 + 100) = &PTR_s_Down_Up_1004a248;
  *(undefined ***)(param_2 + 0x68) = &PTR_s_Left_button_1004a250;
  *(undefined ***)(param_2 + 0x6c) = &PTR_s_LeftBtn_1004a260;
  param_2[0x70] = '\0';
  param_2[0x71] = '\0';
  param_2[0x72] = '\0';
  param_2[0x73] = '\0';
  return 0;
}


