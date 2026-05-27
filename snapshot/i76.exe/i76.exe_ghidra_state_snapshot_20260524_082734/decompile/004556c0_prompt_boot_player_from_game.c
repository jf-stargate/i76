/*
 * Program: i76.exe
 * Function: prompt_boot_player_from_game
 * Entry: 004556c0
 * Signature: undefined __cdecl prompt_boot_player_from_game(uint param_1)
 */


/* cgpt whole-binary semantic rename v1: string evidence: Boot %s from the game? */

void __cdecl prompt_boot_player_from_game(uint param_1)

{
  int iVar1;
  char *_Format;
  uchar local_68 [24];
  uchar local_50 [80];
  
  if (param_1 < DAT_005414f8) {
    iVar1 = multiplayer_player_count_context_helper_00454620
                      (*(short *)(&DAT_00541500 + param_1 * 2),local_68);
    if (iVar1 != 0) {
      DAT_005414f0 = *(undefined2 *)(&DAT_00541500 + param_1 * 2);
      DAT_005414f4 = 1;
      set_text_widget_visible_flag(DAT_00609310,0);
      _Format = (char *)StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,
                                      s_Boot__s_from_the_game___CTRL_Y___004f5b54,local_68);
      sprintf((char *)local_50,_Format);
      set_text_widget_visible_flag(DAT_005414fc,1);
      clear_scrolling_text_widget_buffer(DAT_005414fc);
      append_scrolling_text_widget_message(DAT_005414fc,local_50);
      return;
    }
  }
  DAT_005414f0 = 0;
  DAT_005414f4 = 0;
  set_text_widget_visible_flag(DAT_005414fc,0);
  return;
}


