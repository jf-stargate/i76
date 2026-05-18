/*
 * Program: I76EDIT.EXE
 * Function: __controlfp
 * Entry: 00429ed0
 * Signature: uint __cdecl __controlfp(uint _NewValue, uint _Mask)
 */


/* Library Function - Single Match
    __controlfp
   
   Library: Visual Studio 1998 Release */

uint __cdecl __controlfp(uint _NewValue,uint _Mask)

{
  uint uVar1;
  
  uVar1 = __control87(_NewValue,_Mask & 0xfff7ffff);
  return uVar1;
}


