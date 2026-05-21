/*
 * Program: i76shell.dll
 * Function: close_active_modal_list_dialog
 * Entry: 1000a360
 * Signature: undefined __stdcall close_active_modal_list_dialog(void)
 */


void close_active_modal_list_dialog(void)

{
  bool bVar1;
  int iVar2;
  
  iVar2 = DAT_100cc500;
  DAT_100d21a4 = 0;
  if (DAT_10053398 != (LPVOID)0x0) {
    HeapFree(DAT_10051c50,1,DAT_10053398);
    DAT_10053398 = (LPVOID)0x0;
  }
  clear_text_rect(DAT_100cc518,*DAT_100533b8,DAT_100533b8[1],DAT_100533b8[2] + 0x10,
                  DAT_100533b8[3] + 0x10);
  clear_pointer_list((int *)DAT_100533b8[6]);
  FUN_10027c40(DAT_100533b8);
  DAT_100533b8 = (int *)0x0;
  bVar1 = false;
  while (((iVar2 != 0 && (iVar2 != DAT_100cc500)) || (!bVar1))) {
    bVar1 = true;
    if (*(LPVOID *)(iVar2 + 0x18) != (LPVOID)0x0) {
      HeapFree(DAT_10051c50,1,*(LPVOID *)(iVar2 + 0x18));
      *(undefined4 *)(iVar2 + 0x18) = 0;
    }
    iVar2 = *(int *)(iVar2 + 4);
  }
  if (DAT_100533c4 != (int *)0x0) {
    clear_pointer_list(DAT_100533c4);
    destroy_pointer_list_with_optional_item_destructor(DAT_100533c4,(undefined *)0x0);
    DAT_100533c4 = (int *)0x0;
  }
  return;
}


