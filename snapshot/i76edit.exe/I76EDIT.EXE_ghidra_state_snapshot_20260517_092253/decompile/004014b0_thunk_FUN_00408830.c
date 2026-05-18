/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00408830
 * Entry: 004014b0
 * Signature: undefined __cdecl thunk_FUN_00408830(int * param_1)
 */


void __cdecl thunk_FUN_00408830(int *param_1)

{
  float *pfVar1;
  int iVar2;
  float *pfVar3;
  
  pfVar1 = _malloc(0x54);
  pfVar3 = pfVar1;
  for (iVar2 = 0x15; iVar2 != 0; iVar2 = iVar2 + -1) {
    *pfVar3 = 0.0;
    pfVar3 = pfVar3 + 1;
  }
  if (pfVar1 != (float *)0x0) {
    *pfVar1 = (float)*param_1;
    pfVar1[1] = (float)param_1[1];
    pfVar1[3] = (float)param_1[2];
    pfVar1[4] = (float)param_1[3];
    *(undefined1 *)(pfVar1 + 10) = DAT_00434334;
    pfVar1[0x14] = 0.0;
    DAT_00439be4 = thunk_FUN_0041c430(DAT_00439be4,(undefined4 *)0x0,(int)pfVar1);
  }
  return;
}


