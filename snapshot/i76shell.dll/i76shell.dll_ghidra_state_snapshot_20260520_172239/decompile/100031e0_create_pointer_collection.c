/*
 * Program: i76shell.dll
 * Function: create_pointer_collection
 * Entry: 100031e0
 * Signature: undefined4 __cdecl create_pointer_collection(undefined4 * param_1, int param_2, int param_3, undefined1 param_4, int param_5)
 */


undefined4 __cdecl
create_pointer_collection
          (undefined4 *param_1,int param_2,int param_3,undefined1 param_4,int param_5)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  
  piVar1 = HeapAlloc(DAT_10051c50,1,0x20);
  if (piVar1 == (int *)0x0) {
    fprintf((FILE *)(_iob_exref + 0x40),s_Could_not_allocate_collection_10043230);
    fflush((FILE *)(_iob_exref + 0x40));
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  *param_1 = piVar1;
  piVar1[6] = param_3;
  piVar1[1] = 0;
  piVar1[4] = 0;
  *(undefined1 *)(piVar1 + 3) = param_4;
  piVar1[2] = param_2;
  *piVar1 = param_2;
  piVar1[7] = param_5;
  puVar2 = HeapAlloc(DAT_10051c50,1,param_2 * 4);
  if (puVar2 != (undefined4 *)0x0) {
    iVar3 = 0;
    puVar4 = puVar2;
    if (0 < *piVar1) {
      do {
        *puVar4 = 0;
        iVar3 = iVar3 + 1;
        puVar4 = puVar4 + 1;
      } while (iVar3 < *piVar1);
    }
    piVar1[5] = (int)puVar2;
    return 0;
  }
  fprintf((FILE *)(_iob_exref + 0x40),s_Out_of_memory_in_create_collecti_10043250);
  fflush((FILE *)(_iob_exref + 0x40));
                    /* WARNING: Subroutine does not return */
  exit(1);
}


