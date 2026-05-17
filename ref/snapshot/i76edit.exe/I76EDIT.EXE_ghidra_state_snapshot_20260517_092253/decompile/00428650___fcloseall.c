/*
 * Program: I76EDIT.EXE
 * Function: __fcloseall
 * Entry: 00428650
 * Signature: int __cdecl __fcloseall(void)
 */


/* Library Function - Single Match
    __fcloseall
   
   Library: Visual Studio 1998 Release */

int __cdecl __fcloseall(void)

{
  FILE *_File;
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = 0;
  iVar4 = 3;
  if (3 < DAT_01643850) {
    iVar2 = 0xc;
    do {
      _File = *(FILE **)(DAT_01642508 + iVar2);
      if (_File != (FILE *)0x0) {
        if ((_File->_flag & 0x83U) != 0) {
          iVar1 = _fclose(_File);
          if (iVar1 != -1) {
            iVar3 = iVar3 + 1;
          }
        }
        if (0x4f < iVar2) {
          _free(*(void **)(DAT_01642508 + iVar2));
          *(undefined4 *)(DAT_01642508 + iVar2) = 0;
        }
      }
      iVar2 = iVar2 + 4;
      iVar4 = iVar4 + 1;
    } while (iVar4 < DAT_01643850);
  }
  return iVar3;
}


