/*
 * Program: i76shell.dll
 * Function: init_ui_image_rect_descriptor
 * Entry: 10033510
 * Signature: undefined __cdecl init_ui_image_rect_descriptor(undefined4 param_1, undefined4 * param_2, int param_3, int param_4, undefined4 param_5, int param_6, int param_7, int param_8, undefined4 param_9)
 */


void __cdecl
init_ui_image_rect_descriptor
          (undefined4 param_1,undefined4 *param_2,int param_3,int param_4,undefined4 param_5,
          int param_6,int param_7,int param_8,undefined4 param_9)

{
  *param_2 = param_1;
  param_2[5] = param_6;
  param_2[1] = param_3;
  param_2[6] = param_7;
  param_2[2] = param_6 + -1 + param_3;
  param_2[3] = param_4;
  param_2[10] = 0;
  param_2[0xc] = param_9;
  param_2[4] = param_7 + -1 + param_4;
  param_2[0xb] = param_5;
  param_2[7] = param_8;
  param_2[9] = param_8;
  param_2[8] = param_8 + -1;
  return;
}


