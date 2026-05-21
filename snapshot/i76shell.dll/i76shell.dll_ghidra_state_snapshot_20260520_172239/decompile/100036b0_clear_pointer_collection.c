/*
 * Program: i76shell.dll
 * Function: clear_pointer_collection
 * Entry: 100036b0
 * Signature: undefined __cdecl clear_pointer_collection(int * param_1)
 */


void __cdecl clear_pointer_collection(int *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int iVar4;
  
  iVar4 = 0;
  if (0 < param_1[1]) {
    do {
      iVar1 = *(int *)(param_1[5] + iVar4 * 4);
      if (iVar1 != 0) {
        (*(code *)param_1[6])(iVar1);
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 < param_1[1]);
  }
  if ((LPVOID)param_1[5] != (LPVOID)0x0) {
    HeapFree(DAT_10051c50,1,(LPVOID)param_1[5]);
    param_1[5] = 0;
  }
  param_1[1] = 0;
  param_1[4] = 0;
  puVar2 = HeapAlloc(DAT_10051c50,1,param_1[2] << 2);
  if (puVar2 != (undefined4 *)0x0) {
    iVar4 = 0;
    *param_1 = param_1[2];
    puVar3 = puVar2;
    if (0 < param_1[2]) {
      do {
        *puVar3 = 0;
        iVar4 = iVar4 + 1;
        puVar3 = puVar3 + 1;
      } while (iVar4 < *param_1);
    }
    param_1[5] = (int)puVar2;
    return;
  }
  fprintf((FILE *)(_iob_exref + 0x40),s_Out_of_memory_in_clear_collectio_10043298);
  fflush((FILE *)(_iob_exref + 0x40));
                    /* WARNING: Subroutine does not return */
  exit(1);
}


