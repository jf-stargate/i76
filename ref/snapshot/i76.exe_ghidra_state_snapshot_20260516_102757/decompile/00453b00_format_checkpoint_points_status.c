/*
 * Program: i76.exe
 * Function: format_checkpoint_points_status
 * Entry: 00453b00
 * Signature: undefined __stdcall format_checkpoint_points_status(void)
 */


/* cgpt whole-binary semantic rename v1: string evidence: %d of %d Points */

void format_checkpoint_points_status(void)

{
  int iVar1;
  char *_Format;
  uchar local_50 [80];
  
  clear_scrolling_text_widget_buffer(DAT_00609314);
  iVar1 = multiplayer_chat_ui_context_helper_00452df0();
  if (iVar1 != 0) {
    DAT_00541040 = 0;
    multiplayer_player_table_context_helper_00455490();
    if ((DAT_00541054 != 0) || (DAT_00541058 != 0)) {
      local_50[0] = '\0';
      if (DAT_00541054 != 0) {
        if ((DAT_00541040 < 0) || (DAT_00541048 < 0)) {
          sprintf((char *)local_50,&DAT_00504c28);
        }
        else {
          _Format = (char *)StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,
                                          s__d_of__d_Points_004f5ae4,DAT_00541040,DAT_00541048);
          sprintf((char *)local_50,_Format);
        }
      }
      if (local_50[0] != '\0') {
        append_scrolling_text_widget_message(DAT_00609314,local_50);
      }
    }
  }
  return;
}


