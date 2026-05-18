/*
 * Program: I76EDIT.EXE
 * Function: __atoi64
 * Entry: 00423690
 * Signature: longlong __cdecl __atoi64(char * _String)
 */


/* Library Function - Single Match
    __atoi64
   
   Library: Visual Studio 1998 Release */

longlong __cdecl __atoi64(char *_String)

{
  uint uVar1;
  uint uVar2;
  uint _C;
  byte *pbVar3;
  undefined8 local_8;
  
  while( true ) {
    if (DAT_00438a4c < 2) {
      uVar1 = *(ushort *)(PTR_DAT_00438840 + (uint)(byte)*_String * 2) & 8;
    }
    else {
      uVar1 = __isctype((uint)(byte)*_String,8);
    }
    if (uVar1 == 0) break;
    _String = _String + 1;
  }
  uVar1 = (uint)(byte)*_String;
  pbVar3 = (byte *)(_String + 1);
  if ((uVar1 == 0x2d) || (_C = uVar1, uVar1 == 0x2b)) {
    _C = (uint)*pbVar3;
    pbVar3 = (byte *)(_String + 2);
  }
  local_8 = 0;
  while( true ) {
    if (DAT_00438a4c < 2) {
      uVar2 = *(ushort *)(PTR_DAT_00438840 + _C * 2) & 4;
    }
    else {
      uVar2 = __isctype(_C,4);
    }
    if (uVar2 == 0) break;
    local_8 = __allmul((uint)local_8,local_8._4_4_,10,0);
    local_8 = local_8 + (int)(_C - 0x30);
    _C = (uint)*pbVar3;
    pbVar3 = pbVar3 + 1;
  }
  if (uVar1 == 0x2d) {
    return CONCAT44(-(local_8._4_4_ + (uint)((uint)local_8 != 0)),-(uint)local_8);
  }
  return local_8;
}


