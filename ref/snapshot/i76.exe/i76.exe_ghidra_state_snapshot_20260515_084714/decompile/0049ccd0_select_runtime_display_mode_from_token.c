/*
 * Program: i76.exe
 * Function: select_runtime_display_mode_from_token
 * Entry: 0049ccd0
 * Signature: undefined __cdecl select_runtime_display_mode_from_token(char * param_1)
 */


/* [cgpt i76.exe main runtime/FSM rename v21; confidence=MEDIUM_HIGH] Parses a short token such as a
   one-letter/two-digit selector and maps it to a runtime display/input mode global.
   old_name: FUN_0049ccd0 */

void __cdecl select_runtime_display_mode_from_token(char *param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  undefined1 local_5;
  int local_4;
  
  if (param_1 == (char *)0x0) {
    DAT_004fe520 = 1;
    return;
  }
  sscanf(param_1,s__1s_2d_004fe52c,&local_5,&local_4);
  param_1 = (char *)CONCAT31(param_1._1_3_,local_5);
  iVar1 = _strnicmp((char *)&param_1,&DAT_004fe528,1);
  if (iVar1 != 0) {
    iVar1 = _strnicmp((char *)&param_1,&DAT_004fe524,1);
    if (iVar1 == 0) {
      DAT_004fe520 = 2;
      return;
    }
    iVar1 = 0;
    piVar3 = &DAT_004fe434;
    while( true ) {
      iVar2 = _strnicmp((char *)&param_1,(char *)(piVar3 + -1),1);
      if ((iVar2 == 0) && (local_4 == *piVar3)) break;
      piVar3 = piVar3 + 3;
      iVar1 = iVar1 + 1;
      if ((int *)((int)&DAT_004fe520 + 3) < piVar3) {
        DAT_004fe520 = 1;
        return;
      }
    }
    DAT_004fe520 = (&DAT_004fe438)[iVar1 * 3];
    return;
  }
  DAT_004fe520 = 1;
  return;
}


