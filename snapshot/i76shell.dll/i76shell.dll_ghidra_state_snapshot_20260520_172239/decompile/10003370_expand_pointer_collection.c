/*
 * Program: i76shell.dll
 * Function: expand_pointer_collection
 * Entry: 10003370
 * Signature: undefined4 __cdecl expand_pointer_collection(int * param_1, undefined4 param_2)
 */


undefined4 __cdecl expand_pointer_collection(int *param_1,undefined4 param_2)

{
  int iVar1;
  LPVOID pvVar2;
  undefined4 *puVar3;
  
  if (*param_1 + -1 < param_1[1]) {
    iVar1 = *param_1 + param_1[2];
    *param_1 = iVar1;
    if ((LPVOID)param_1[5] == (LPVOID)0x0) {
      pvVar2 = HeapAlloc(DAT_10051c50,1,iVar1 * 4);
    }
    else {
      pvVar2 = HeapReAlloc(DAT_10051c50,1,(LPVOID)param_1[5],iVar1 * 4);
    }
    if (pvVar2 == (LPVOID)0x0) {
      fprintf((FILE *)(_iob_exref + 0x40),s_Out_of_memory_in_expand_collecti_10043274);
      fflush((FILE *)(_iob_exref + 0x40));
                    /* WARNING: Subroutine does not return */
      exit(1);
    }
    iVar1 = *param_1 - param_1[2];
    if (iVar1 < *param_1) {
      puVar3 = (undefined4 *)((int)pvVar2 + iVar1 * 4);
      do {
        *puVar3 = 0;
        iVar1 = iVar1 + 1;
        puVar3 = puVar3 + 1;
      } while (iVar1 < *param_1);
    }
    param_1[5] = (int)pvVar2;
  }
  *(undefined4 *)(param_1[5] + param_1[1] * 4) = param_2;
  param_1[4] = 1;
  param_1[1] = param_1[1] + 1;
  return 0;
}


