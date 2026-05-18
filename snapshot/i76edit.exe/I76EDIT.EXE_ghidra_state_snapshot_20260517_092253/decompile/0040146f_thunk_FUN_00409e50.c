/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00409e50
 * Entry: 0040146f
 * Signature: undefined __stdcall thunk_FUN_00409e50(void)
 */


void thunk_FUN_00409e50(void)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  
  piVar3 = &DAT_00439be8;
  do {
    piVar2 = (int *)*piVar3;
    while (piVar2 != (int *)0x0) {
      piVar1 = (int *)*piVar2;
      if (piVar2[2] == 0) {
        thunk_FUN_0041c480(piVar3,piVar2);
        piVar2 = piVar1;
      }
      else {
        thunk_FUN_00409a60(piVar2);
        piVar2 = piVar1;
      }
    }
    *piVar3 = 0;
    piVar3 = piVar3 + 1;
  } while (piVar3 < &DAT_00439d28);
  return;
}


