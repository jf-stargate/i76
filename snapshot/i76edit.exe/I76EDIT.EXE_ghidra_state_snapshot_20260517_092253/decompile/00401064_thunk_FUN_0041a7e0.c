/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0041a7e0
 * Entry: 00401064
 * Signature: undefined __cdecl thunk_FUN_0041a7e0(char * param_1)
 */


void __cdecl thunk_FUN_0041a7e0(char *param_1)

{
  int _FileHandle;
  undefined4 unaff_ESI;
  undefined2 unaff_DI;
  undefined1 *_Buf;
  undefined1 *puVar1;
  undefined4 uVar2;
  undefined *puVar3;
  undefined4 uStack_4;
  
  _FileHandle = __open(param_1,0x8301,0x80);
  __write(_FileHandle,&DAT_004366ac,4);
  uStack_4 = 8;
  __write(_FileHandle,&stack0xfffffff8,4);
  __write(_FileHandle,&uStack_4,4);
  __write(_FileHandle,&stack0xfffffff8,4);
  __write(_FileHandle,&DAT_01641fc0,0x13e);
  thunk_FUN_0041e120(s_Saving_Terrain____0043677c);
  uStack_4 = 5;
  __write(_FileHandle,&stack0xfffffff8,4);
  __write(_FileHandle,&uStack_4,4);
  uVar2 = 0x454e4f5a;
  __write(_FileHandle,&stack0xfffffff8,4);
  thunk_FUN_00412500(_FileHandle);
  thunk_FUN_0040cbe0(_FileHandle,unaff_DI,unaff_ESI,uVar2);
  thunk_FUN_0041e120(s_Saving_Paths____00436768);
  __write(_FileHandle,&stack0xfffffff8,4);
  thunk_FUN_00408ec0();
  thunk_FUN_0041e120(s_Saving_Roads____00436754);
  uVar2 = 0x44414f52;
  __write(_FileHandle,&stack0xfffffff8,4);
  thunk_FUN_00415ca0(_FileHandle,unaff_DI,unaff_ESI,uVar2);
  thunk_FUN_0041e120(s_Saving_Objects____0043673c);
  uStack_4 = 3;
  __write(_FileHandle,&stack0xfffffff8,4);
  __write(_FileHandle,&uStack_4,4);
  puVar3 = &DAT_004a424f;
  __write(_FileHandle,&stack0xfffffff8,4);
  thunk_FUN_0040a280(_FileHandle);
  thunk_FUN_0040f6b0(_FileHandle,unaff_DI,unaff_ESI,puVar3);
  thunk_FUN_0041e120(s_Saving_Elevations____00436720);
  __write(_FileHandle,&stack0xfffffff8,4);
  _Buf = &DAT_0163ce70;
  do {
    puVar1 = _Buf + 200;
    __write(_FileHandle,_Buf,200);
    _Buf = puVar1;
  } while (puVar1 < &DAT_01640cf0);
  __write(_FileHandle,&stack0xfffffff8,4);
  __close(_FileHandle);
  thunk_FUN_0041e120(s_Ready__00434590);
  return;
}


