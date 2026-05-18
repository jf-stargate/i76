/*
 * Program: i76.exe
 * Function: prompt_allow_player_join_game
 * Entry: 004559a0
 * Signature: undefined __stdcall prompt_allow_player_join_game(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: string evidence: Let %s join the game? */

void prompt_allow_player_join_game(void)

{
  uint uVar1;
  bool bVar2;
  uint uVar3;
  undefined4 *puVar4;
  uint uVar5;
  char *_Format;
  int iVar6;
  undefined4 *puVar7;
  float10 fVar8;
  undefined4 local_b8 [26];
  uchar local_50 [80];
  
  bVar2 = false;
  fVar8 = get_network_or_session_runtime_seconds();
  puVar7 = (undefined4 *)(float)fVar8;
  uVar5 = DAT_005419b4;
  if (_DAT_004bdf84 < (float)puVar7 - *(float *)(&DAT_00541838 + (DAT_005419b0 + 1 & 0x1f) * 0xc)) {
    do {
      if (DAT_005419b0 == DAT_00541828) break;
      DAT_005419b0 = DAT_005419b0 + 1 & 0x1f;
      uVar1 = DAT_005419b0 + 1;
      uVar3 = DAT_00541520;
      do {
        if (uVar3 == uVar5) {
          puVar4 = (undefined4 *)0x0;
          goto LAB_00455a4b;
        }
        uVar3 = uVar3 + 1 & 0x3f;
      } while ((*(short *)(&DAT_00541528 + uVar3 * 3) !=
                *(short *)(&DAT_00541830 + DAT_005419b0 * 3)) ||
              ((&DAT_0054152c)[uVar3 * 3] != (&DAT_00541834)[DAT_005419b0 * 3]));
      puVar4 = &DAT_00541528 + uVar3 * 3;
LAB_00455a4b:
      if (puVar4 != (undefined4 *)0x0) {
        puVar4[2] = puVar4[2] & 0xfffffff9 | 1;
        uVar5 = DAT_005419b4;
      }
    } while (_DAT_004bdf84 < (float)puVar7 - *(float *)(&DAT_00541838 + (uVar1 & 0x1f) * 0xc));
  }
  do {
    if (DAT_005419b0 == DAT_00541828) break;
    puVar7 = local_b8;
    for (iVar6 = 6; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar7 = 0;
      puVar7 = puVar7 + 1;
    }
    puVar7 = local_b8;
    iVar6 = dpGetPlayerName(DAT_00541024,
                            *(undefined2 *)(&DAT_00541830 + (DAT_005419b0 + 1 & 0x1f) * 3),local_b8,
                            0x68);
    if (iVar6 == 0) {
      bVar2 = true;
    }
    else {
      DAT_005419b0 = DAT_005419b0 + 1 & 0x1f;
      uVar5 = DAT_00541520;
      do {
        if (uVar5 == DAT_005419b4) {
          puVar4 = (undefined4 *)0x0;
          goto LAB_00455b35;
        }
        uVar5 = uVar5 + 1 & 0x3f;
      } while ((*(short *)(&DAT_00541528 + uVar5 * 3) !=
                *(short *)(&DAT_00541830 + DAT_005419b0 * 3)) ||
              ((&DAT_0054152c)[uVar5 * 3] != (&DAT_00541834)[DAT_005419b0 * 3]));
      puVar4 = &DAT_00541528 + uVar5 * 3;
LAB_00455b35:
      if (puVar4 != (undefined4 *)0x0) {
        puVar4[2] = puVar4[2] & 0xfffffff9 | 1;
      }
    }
  } while (!bVar2);
  if (bVar2) {
    _Format = (char *)StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,
                                    s_Let__s_join_the_game___CTRL_Y___C_004f5b80,puVar7);
    sprintf((char *)local_50,_Format);
    set_text_widget_visible_flag(DAT_00609310,1);
    clear_scrolling_text_widget_buffer(DAT_00609310);
    append_scrolling_text_widget_message(DAT_00609310,local_50);
    return;
  }
  set_text_widget_visible_flag(DAT_00609310,0);
  return;
}


