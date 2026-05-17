/*
 * Program: i76.exe
 * Function: register_mouse_input_controls
 * Entry: 0044b6f0
 * Signature: undefined4 __cdecl register_mouse_input_controls(undefined4 param_1, char * param_2)
 */


/* cgpt whole-binary semantic rename v1: string evidence: mouse axes/buttons */

undefined4 __cdecl register_mouse_input_controls(undefined4 param_1,char *param_2)

{
  char *_Format;
  
  param_2[0x58] = '\x02';
  param_2[0x59] = '\0';
  param_2[0x5a] = '\0';
  param_2[0x5b] = '\0';
  param_2[0x5c] = '\x03';
  param_2[0x5d] = '\0';
  param_2[0x5e] = '\0';
  param_2[0x5f] = '\0';
  PTR_s_Mouse_Down_Up_Movement_004f2730 =
       (undefined *)
       StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Mouse_Down_Up_Movement_004f27d8)
  ;
  PTR_s_Mouse_Left_Right_Movement_004f2734 =
       (undefined *)
       StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,
                     s_Mouse_Left_Right_Movement_004f27bc);
  PTR_s_Left_button_004f2740 =
       (undefined *)
       StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Left_button_004f27b0);
  PTR_s_Middle_button_004f2744 =
       (undefined *)
       StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Middle_button_004f27a0);
  PTR_s_Right_button_004f2748 =
       (undefined *)
       StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Right_button_004f2790);
  sprintf(param_2,s_mouse_004f2788);
  _Format = (char *)StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Mouse_004f2780);
  sprintf(param_2 + 0xc,_Format);
  sprintf(param_2 + 0x4c,s_mouse_004f2788);
  *(undefined ***)(param_2 + 0x60) = &PTR_s_Mouse_Down_Up_Movement_004f2730;
  *(undefined ***)(param_2 + 100) = &PTR_s_Down_Up_004f2738;
  *(undefined ***)(param_2 + 0x68) = &PTR_s_Left_button_004f2740;
  *(undefined ***)(param_2 + 0x6c) = &PTR_s_LeftBtn_004f2750;
  param_2[0x70] = '\0';
  param_2[0x71] = '\0';
  param_2[0x72] = '\0';
  param_2[0x73] = '\0';
  return 0;
}


