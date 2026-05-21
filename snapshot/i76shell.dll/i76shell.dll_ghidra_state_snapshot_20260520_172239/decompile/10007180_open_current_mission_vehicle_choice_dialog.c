/*
 * Program: i76shell.dll
 * Function: open_current_mission_vehicle_choice_dialog
 * Entry: 10007180
 * Signature: undefined __stdcall open_current_mission_vehicle_choice_dialog(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void open_current_mission_vehicle_choice_dialog(void)

{
  int iVar1;
  char *_Str2;
  int iVar2;
  char local_8 [8];
  
  strncpy(local_8,&DAT_100589cd + *(int *)(DAT_100c5ad8 + 0x38) * 0x8c4,4);
  DAT_100520c8 = create_pointer_list_with_capacity(0x20);
  iVar2 = 0;
  if (0 < DAT_10047710) {
    _Str2 = &DAT_100c62c3;
    do {
      if ((*(int *)(_Str2 + -0x1d) == 0xe) && (iVar1 = strncmp(local_8,_Str2,4), iVar1 == 0)) {
        insert_pointer_list_item_sorted_or_append
                  ((int)DAT_100520c8,(int)(_Str2 + -0x3b),(undefined *)0x0);
      }
      iVar2 = iVar2 + 1;
      _Str2 = _Str2 + 0x54;
    } while (iVar2 < DAT_10047710);
  }
  DAT_100520c4 = create_pointer_list_default_16();
  insert_pointer_list_item_sorted_or_append((int)DAT_100520c4,0x10043618,(undefined *)0x0);
  insert_pointer_list_item_sorted_or_append((int)DAT_100520c4,0x1004362c,(undefined *)0x0);
  insert_pointer_list_item_sorted_or_append((int)DAT_100520c4,0x10043640,(undefined *)0x0);
  insert_pointer_list_item_sorted_or_append((int)DAT_100520c4,0x10043654,(undefined *)0x0);
  DAT_10043698 = 0xffffffff;
  _DAT_10043678 = 0x12;
  _DAT_1004367c = 0x30;
  _DAT_10043688 = DAT_100520c8[1];
  _DAT_10043668 = 0x140 - DAT_10043670 / 2;
  _DAT_1004366c = 0xf0 - DAT_10043674 / 2;
  _DAT_1004368c = &LAB_10007020;
  _DAT_10043690 = &LAB_10007110;
  _DAT_10043694 = DAT_100520c4;
  open_modal_scroll_list_dialog((int *)&DAT_10043668,0xf);
  return;
}


