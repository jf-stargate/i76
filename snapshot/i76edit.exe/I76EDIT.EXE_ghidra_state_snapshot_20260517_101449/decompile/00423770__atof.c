/*
 * Program: I76EDIT.EXE
 * Function: _atof
 * Entry: 00423770
 * Signature: double __cdecl _atof(char * _String)
 */


/* Library Function - Single Match
    _atof
   
   Library: Visual Studio 1998 Release */

double __cdecl _atof(char *_String)

{
  byte bVar1;
  uint uVar2;
  undefined *puVar3;
  int iVar4;
  byte *pbVar5;
  
  while( true ) {
    if (DAT_00438a4c < 2) {
      uVar2 = *(ushort *)(PTR_DAT_00438840 + (uint)(byte)*_String * 2) & 8;
    }
    else {
      uVar2 = __isctype((uint)(byte)*_String,8);
    }
    if (uVar2 == 0) break;
    _String = _String + 1;
  }
  iVar4 = -1;
  pbVar5 = (byte *)_String;
  do {
    if (iVar4 == 0) break;
    iVar4 = iVar4 + -1;
    bVar1 = *pbVar5;
    pbVar5 = pbVar5 + 1;
  } while (bVar1 != 0);
  puVar3 = __fltin(_String);
  return *(double *)(puVar3 + 0x10);
}


