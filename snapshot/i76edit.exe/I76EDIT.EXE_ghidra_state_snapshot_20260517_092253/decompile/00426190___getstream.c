/*
 * Program: I76EDIT.EXE
 * Function: __getstream
 * Entry: 00426190
 * Signature: FILE * __cdecl __getstream(void)
 */


/* Library Function - Single Match
    __getstream
   
   Library: Visual Studio 1998 Release */

FILE * __cdecl __getstream(void)

{
  void *pvVar1;
  int *piVar2;
  FILE *pFVar3;
  int iVar4;
  
  pFVar3 = (FILE *)0x0;
  iVar4 = 0;
  piVar2 = DAT_01642508;
  if (0 < DAT_01643850) {
    do {
      if (*piVar2 == 0) {
        pvVar1 = _malloc(0x20);
        DAT_01642508[iVar4] = (int)pvVar1;
        if ((FILE *)DAT_01642508[iVar4] != (FILE *)0x0) {
          pFVar3 = (FILE *)DAT_01642508[iVar4];
        }
        break;
      }
      if ((*(uint *)(*piVar2 + 0xc) & 0x83) == 0) {
        pFVar3 = (FILE *)DAT_01642508[iVar4];
        break;
      }
      iVar4 = iVar4 + 1;
      piVar2 = piVar2 + 1;
    } while (iVar4 < DAT_01643850);
  }
  if (pFVar3 != (FILE *)0x0) {
    pFVar3->_cnt = 0;
    pFVar3->_flag = 0;
    pFVar3->_base = (char *)0x0;
    pFVar3->_ptr = (char *)0x0;
    pFVar3->_tmpfname = (char *)0x0;
    pFVar3->_file = -1;
  }
  return pFVar3;
}


