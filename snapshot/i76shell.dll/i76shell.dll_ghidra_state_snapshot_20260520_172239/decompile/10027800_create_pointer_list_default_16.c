/*
 * Program: i76shell.dll
 * Function: create_pointer_list_default_16
 * Entry: 10027800
 * Signature: int * __stdcall create_pointer_list_default_16(void)
 */


int * create_pointer_list_default_16(void)

{
  int *lpMem;
  LPVOID pvVar1;
  int iVar2;
  
  lpMem = HeapAlloc(DAT_10051c50,1,0xc);
  if (lpMem != (int *)0x0) {
    lpMem[1] = 0;
    pvVar1 = HeapAlloc(DAT_10051c50,1,0x40);
    lpMem[2] = (int)pvVar1;
    if (pvVar1 == (LPVOID)0x0) {
      HeapFree(DAT_10051c50,1,lpMem);
      return (int *)0x0;
    }
  }
  *lpMem = 0x10;
  iVar2 = 0;
  do {
    iVar2 = iVar2 + 1;
    *(undefined4 *)(lpMem[2] + -4 + iVar2 * 4) = 0;
  } while (iVar2 < *lpMem);
  return lpMem;
}


