/*
 * Program: I76EDIT.EXE
 * Function: __control87
 * Entry: 00429e80
 * Signature: uint __cdecl __control87(uint _NewValue, uint _Mask)
 */


/* Library Function - Single Match
    __control87
   
   Library: Visual Studio 1998 Release */

uint __cdecl __control87(uint _NewValue,uint _Mask)

{
  uint uVar1;
  ushort in_FPUControlWord;
  
  uVar1 = __abstract_cw(in_FPUControlWord);
  __hw_cw();
  return ~_Mask & uVar1 | _NewValue & _Mask;
}


