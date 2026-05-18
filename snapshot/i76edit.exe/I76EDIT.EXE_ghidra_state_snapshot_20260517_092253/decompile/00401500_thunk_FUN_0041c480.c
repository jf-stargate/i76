/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0041c480
 * Entry: 00401500
 * Signature: undefined __cdecl thunk_FUN_0041c480(int * param_1, int * param_2)
 */


void __cdecl thunk_FUN_0041c480(int *param_1,int *param_2)

{
  int *piVar1;
  
  if (*param_2 != 0) {
    *(int *)(*param_2 + 4) = param_2[1];
  }
  piVar1 = (int *)param_2[1];
  if ((int *)param_2[1] == (int *)0x0) {
    piVar1 = param_1;
  }
  *piVar1 = *param_2;
  HeapFree(DAT_00436994,0,param_2);
  return;
}


