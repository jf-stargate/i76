/*
 * Program: I76EDIT.EXE
 * Function: i76edit_save_object_zone_lists
 * Entry: 0040131b
 * Signature: undefined __cdecl i76edit_save_object_zone_lists(int param_1)
 */


void __cdecl i76edit_save_object_zone_lists(int param_1)

{
  undefined4 *puVar1;
  long lVar2;
  long _Offset;
  uint uStack_10;
  int iStack_c;
  int iStack_8;
  long lStack_4;
  
  iStack_8 = 0;
  iStack_c = 0;
  lStack_4 = __tell(param_1);
  __write(param_1,&iStack_8,4);
  uStack_10 = 0;
  do {
    if ((&DAT_00439be8)[uStack_10] != 0) {
      iStack_8 = iStack_8 + 1;
      iStack_c = 0;
      __write(param_1,&uStack_10,4);
      lVar2 = __tell(param_1);
      __write(param_1,&iStack_c,4);
      for (puVar1 = (undefined4 *)(&DAT_00439be8)[uStack_10]; puVar1 != (undefined4 *)0x0;
          puVar1 = (undefined4 *)*puVar1) {
        iStack_c = iStack_c + 1;
        __write(param_1,(void *)puVar1[2],0x78);
      }
      _Offset = __tell(param_1);
      __lseek(param_1,lVar2,0);
      __write(param_1,&iStack_c,4);
      __lseek(param_1,_Offset,0);
    }
    uStack_10 = uStack_10 + 1;
  } while (uStack_10 < 0x50);
  lVar2 = __tell(param_1);
  __lseek(param_1,lStack_4,0);
  __write(param_1,&iStack_8,4);
  __lseek(param_1,lVar2,0);
  return;
}


