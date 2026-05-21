/*
 * Program: i76shell.dll
 * Function: clear_pointer_list
 * Entry: 10027b20
 * Signature: undefined __cdecl clear_pointer_list(int * param_1)
 */


void __cdecl clear_pointer_list(int *param_1)

{
  int iVar1;
  
  if (param_1 != (int *)0x0) {
    param_1[1] = 0;
  }
  iVar1 = 0;
  if (0 < *param_1) {
    do {
      iVar1 = iVar1 + 1;
      *(undefined4 *)(param_1[2] + -4 + iVar1 * 4) = 0;
    } while (iVar1 < *param_1);
  }
  return;
}


