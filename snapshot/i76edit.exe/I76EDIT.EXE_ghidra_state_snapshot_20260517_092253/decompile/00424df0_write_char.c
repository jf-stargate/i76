/*
 * Program: I76EDIT.EXE
 * Function: write_char
 * Entry: 00424df0
 * Signature: undefined __cdecl write_char(int param_1, FILE * param_2, int * param_3)
 */


/* Library Function - Single Match
    _write_char
   
   Library: Visual Studio 1998 Release */

void __cdecl write_char(int param_1,FILE *param_2,int *param_3)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = param_2->_cnt + -1;
  param_2->_cnt = iVar1;
  if (iVar1 < 0) {
    uVar2 = __flsbuf(param_1,param_2);
  }
  else {
    *param_2->_ptr = (char)param_1;
    uVar2 = (uint)(byte)*param_2->_ptr;
    param_2->_ptr = param_2->_ptr + 1;
  }
  if (uVar2 == 0xffffffff) {
    *param_3 = -1;
    return;
  }
  *param_3 = *param_3 + 1;
  return;
}


