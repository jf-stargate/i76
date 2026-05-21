/*
 * Program: i76shell.dll
 * Function: read_phone_list_file
 * Entry: 10030c80
 * Signature: undefined __stdcall read_phone_list_file(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void read_phone_list_file(void)

{
  FILE *_File;
  LPVOID _DstBuf;
  int iVar1;
  int local_4;
  
  iVar1 = 0;
  DAT_100f4f3c = 0;
  DAT_100f4f34 = create_pointer_list_default_16();
  insert_pointer_list_item_sorted_or_append((int)DAT_100f4f34,0x1004ca50,(undefined *)0x0);
  insert_pointer_list_item_sorted_or_append((int)DAT_100f4f34,0x1004ca64,(undefined *)0x0);
  insert_pointer_list_item_sorted_or_append((int)DAT_100f4f34,0x1004ca78,(undefined *)0x0);
  insert_pointer_list_item_sorted_or_append((int)DAT_100f4f34,0x1004ca8c,(undefined *)0x0);
  insert_pointer_list_item_sorted_or_append((int)DAT_100f4f34,0x1004caa0,(undefined *)0x0);
  insert_pointer_list_item_sorted_or_append((int)DAT_100f4f34,0x1004cab4,(undefined *)0x0);
  insert_pointer_list_item_sorted_or_append((int)DAT_100f4f34,0x1004cac8,(undefined *)0x0);
  insert_pointer_list_item_sorted_or_append((int)DAT_100f4f34,0x1004cadc,(undefined *)0x0);
  DAT_100f4f38 = create_pointer_list_with_capacity(0x40);
  _File = fopen(s_phone_lst_1004cb70,s_rb_1004cb6c);
  if (_File != (FILE *)0x0) {
    fread(&local_4,4,1,_File);
    if (0 < local_4) {
      do {
        _DstBuf = HeapAlloc(DAT_10051c50,1,0x60);
        fread(_DstBuf,0x60,1,_File);
        insert_pointer_list_item_sorted_or_append((int)DAT_100f4f38,(int)_DstBuf,&LAB_10030bc0);
        iVar1 = iVar1 + 1;
      } while (iVar1 < local_4);
    }
    fclose(_File);
  }
  _DAT_100f4f08 = 0x32;
  _DAT_100f4f0c = 0xde;
  _DAT_100f4f00 = 0x110;
  _DAT_100f4f04 = 0x194;
  DAT_100f4f28 = 0xffffffff;
  _DAT_100f4f10 = 4;
  _DAT_100f4f18 = DAT_100f4f38[1];
  DAT_100f4ef8 = 0xb8;
  DAT_100f4efc = 0x26;
  _DAT_100f4f1c = &LAB_10030820;
  _DAT_100f4f20 = &LAB_10030aa0;
  _DAT_100f4f24 = DAT_100f4f34;
  DAT_100f4f2c = 0x30;
  DAT_100f4f30 = 0x44;
  DAT_100533ac = 0x82;
  open_phonebook_entry_list_dialog(&DAT_100f4ef8);
  return;
}


