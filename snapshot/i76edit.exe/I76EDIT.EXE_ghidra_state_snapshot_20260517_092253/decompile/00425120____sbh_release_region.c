/*
 * Program: I76EDIT.EXE
 * Function: ___sbh_release_region
 * Entry: 00425120
 * Signature: undefined __cdecl ___sbh_release_region(undefined * * param_1)
 */


/* Library Function - Single Match
    ___sbh_release_region
   
   Library: Visual Studio 1998 Release */

void __cdecl ___sbh_release_region(undefined **param_1)

{
  VirtualFree(param_1[0x204],0,0x8000);
  if ((undefined **)PTR_LOOP_0043866c == param_1) {
    PTR_LOOP_0043866c = param_1[1];
  }
  if (param_1 != &PTR_LOOP_00437e58) {
    *(undefined **)param_1[1] = *param_1;
    *(undefined **)(*param_1 + 4) = param_1[1];
    HeapFree(DAT_016424f0,0,param_1);
    return;
  }
  DAT_00438668 = 0;
  return;
}


