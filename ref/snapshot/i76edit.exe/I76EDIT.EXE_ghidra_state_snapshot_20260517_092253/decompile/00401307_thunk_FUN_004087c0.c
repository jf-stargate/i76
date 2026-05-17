/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_004087c0
 * Entry: 00401307
 * Signature: undefined __stdcall thunk_FUN_004087c0(void)
 */


void thunk_FUN_004087c0(void)

{
  float *pfVar1;
  int *piVar2;
  
  piVar2 = DAT_00439be4;
  do {
    if (piVar2 == (int *)0x0) {
      return;
    }
    while ((pfVar1 = (float *)piVar2[2], pfVar1[3] == *pfVar1 && (pfVar1[1] == pfVar1[4]))) {
      thunk_FUN_00408ac0(piVar2);
      piVar2 = DAT_00439be4;
      if (DAT_00439be4 == (int *)0x0) {
        return;
      }
    }
    piVar2 = (int *)*piVar2;
  } while( true );
}


