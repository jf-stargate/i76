/*
 * Program: i76.exe
 * Function: draw_multiplayer_chat_message
 * Entry: 00453df0
 * Signature: undefined __cdecl draw_multiplayer_chat_message(short param_1, uchar * param_2)
 */


/* cgpt whole-binary semantic rename v1: string evidence: Unknown Loser / From %s: */

void __cdecl draw_multiplayer_chat_message(short param_1,uchar *param_2)

{
  char cVar1;
  uchar uVar2;
  int iVar3;
  char *pcVar4;
  uint uVar5;
  uint uVar6;
  uchar *puVar7;
  char *pcVar8;
  uchar *puVar9;
  uchar local_68 [24];
  uchar local_50 [80];
  
  if (param_1 != 0) {
    iVar3 = multiplayer_player_count_context_helper_00454620(param_1,local_68);
    if (iVar3 != 0) goto LAB_00453e4a;
  }
  pcVar4 = (char *)StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,
                                 s_Unknown_Loser_004f5b10);
  uVar5 = 0xffffffff;
  do {
    pcVar8 = pcVar4;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar8 = pcVar4 + 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar8;
  } while (cVar1 != '\0');
  uVar5 = ~uVar5;
  puVar7 = (uchar *)(pcVar8 + -uVar5);
  puVar9 = local_68;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)puVar9 = *(undefined4 *)puVar7;
    puVar7 = puVar7 + 4;
    puVar9 = puVar9 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *puVar9 = *puVar7;
    puVar7 = puVar7 + 1;
    puVar9 = puVar9 + 1;
  }
LAB_00453e4a:
  if (param_1 == 0) {
    local_50[0] = '\0';
  }
  else {
    pcVar4 = (char *)StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_From__s__004f5b04,
                                   local_68);
    sprintf((char *)local_50,pcVar4);
  }
  uVar5 = 0xffffffff;
  puVar7 = local_50;
  do {
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    uVar2 = *puVar7;
    puVar7 = puVar7 + 1;
  } while (uVar2 != '\0');
  _mbsnbcat(local_50,param_2,0x4f - (~uVar5 - 1));
  append_scrolling_text_widget_message(DAT_0060931c,local_50);
  append_scrolling_text_widget_message(DAT_0060931c,&DAT_00504c28);
  return;
}


