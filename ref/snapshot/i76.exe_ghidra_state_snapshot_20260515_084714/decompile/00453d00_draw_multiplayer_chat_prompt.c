/*
 * Program: i76.exe
 * Function: draw_multiplayer_chat_prompt
 * Entry: 00453d00
 * Signature: undefined __cdecl draw_multiplayer_chat_prompt(short param_1)
 */


/* cgpt whole-binary semantic rename v1: string evidence: To %s: / Say: */

void __cdecl draw_multiplayer_chat_prompt(short param_1)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  uchar local_40 [24];
  char local_28 [40];
  
  if (param_1 != 0) {
    iVar2 = multiplayer_player_count_context_helper_00454620(param_1,local_40);
    if (iVar2 != 0) {
      pcVar3 = (char *)StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_To__s__004f5afc,
                                     local_40);
      sprintf(local_28,pcVar3);
      goto LAB_00453d87;
    }
  }
  pcVar3 = (char *)StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Say__004f5af4);
  uVar4 = 0xffffffff;
  do {
    pcVar6 = pcVar3;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar6 = pcVar3 + 1;
    cVar1 = *pcVar3;
    pcVar3 = pcVar6;
  } while (cVar1 != '\0');
  uVar4 = ~uVar4;
  pcVar3 = pcVar6 + -uVar4;
  pcVar6 = local_28;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar6 = *(undefined4 *)pcVar3;
    pcVar3 = pcVar3 + 4;
    pcVar6 = pcVar6 + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar6 = *pcVar3;
    pcVar3 = pcVar3 + 1;
    pcVar6 = pcVar6 + 1;
  }
  param_1 = 0;
LAB_00453d87:
  ui_bitmap_region_context_helper_0049ba40(DAT_00609318,local_28);
  ui_bitmap_region_context_helper_0049bae0(DAT_00609318,&DAT_00504c28);
  set_text_widget_visible_flag(DAT_00609314,0);
  ui_bitmap_region_context_helper_0049b9b0(DAT_00609318,1);
  ui_bitmap_region_context_helper_0049b9e0(DAT_00609318,1);
  DAT_0054104c = param_1;
  return;
}


