/*
 * Program: i76shell.dll
 * Function: create_pointer_list_with_capacity
 * Entry: 10027870
 * Signature: int * __cdecl create_pointer_list_with_capacity(int param_1)
 */


int * __cdecl create_pointer_list_with_capacity(int param_1)

{
  int *lpMem;
  LPVOID pvVar1;
  int iVar2;
  
  lpMem = HeapAlloc(DAT_10051c50,1,0xc);
  if (lpMem != (int *)0x0) {
    lpMem[1] = 0;
    pvVar1 = HeapAlloc(DAT_10051c50,1,param_1 * 4);
    lpMem[2] = (int)pvVar1;
    if (pvVar1 == (LPVOID)0x0) {
      HeapFree(DAT_10051c50,1,lpMem);
      return (int *)0x0;
    }
  }
  iVar2 = 0;
  *lpMem = param_1;
  if (0 < param_1) {
    do {
      iVar2 = iVar2 + 1;
      *(undefined4 *)(lpMem[2] + -4 + iVar2 * 4) = 0;
    } while (iVar2 < *lpMem);
  }
  return lpMem;
}


