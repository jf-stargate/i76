/*
 * Program: I76EDIT.EXE
 * Function: __tell
 * Entry: 0042d530
 * Signature: long __cdecl __tell(int _FileHandle)
 */


/* Library Function - Single Match
    __tell
   
   Library: Visual Studio 1998 Release */

long __cdecl __tell(int _FileHandle)

{
  long lVar1;
  
  lVar1 = __lseek(_FileHandle,0,1);
  return lVar1;
}


