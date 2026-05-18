/*
 * Program: I76EDIT.EXE
 * Function: flsall
 * Entry: 00425b90
 * Signature: int __cdecl flsall(int param_1)
 */


/* Library Function - Single Match
    _flsall
   
   Library: Visual Studio 1998 Release */

int __cdecl flsall(int param_1)

{
  FILE *_File;
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int local_4;
  
  iVar2 = 0;
  iVar4 = 0;
  local_4 = 0;
  if (0 < DAT_01643850) {
    iVar3 = 0;
    do {
      _File = *(FILE **)(DAT_01642508 + iVar3);
      if ((_File != (FILE *)0x0) && ((_File->_flag & 0x83U) != 0)) {
        if (param_1 == 1) {
          iVar1 = _fflush(_File);
          if (iVar1 != -1) {
            iVar2 = iVar2 + 1;
          }
        }
        else if (((param_1 == 0) && ((_File->_flag & 2U) != 0)) &&
                (iVar1 = _fflush(_File), iVar1 == -1)) {
          local_4 = -1;
        }
      }
      iVar3 = iVar3 + 4;
      iVar4 = iVar4 + 1;
    } while (iVar4 < DAT_01643850);
  }
  if (param_1 != 1) {
    iVar2 = local_4;
  }
  return iVar2;
}


