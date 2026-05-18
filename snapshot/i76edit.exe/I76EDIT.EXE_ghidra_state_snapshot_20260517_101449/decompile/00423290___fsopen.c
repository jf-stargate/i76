/*
 * Program: I76EDIT.EXE
 * Function: __fsopen
 * Entry: 00423290
 * Signature: FILE * __cdecl __fsopen(char * _Filename, char * _Mode, int _ShFlag)
 */


/* Library Function - Single Match
    __fsopen
   
   Library: Visual Studio 1998 Release */

FILE * __cdecl __fsopen(char *_Filename,char *_Mode,int _ShFlag)

{
  FILE *pFVar1;
  
  pFVar1 = __getstream();
  if (pFVar1 == (FILE *)0x0) {
    return (FILE *)0x0;
  }
  pFVar1 = __openfile(_Filename,_Mode,_ShFlag,pFVar1);
  return pFVar1;
}


