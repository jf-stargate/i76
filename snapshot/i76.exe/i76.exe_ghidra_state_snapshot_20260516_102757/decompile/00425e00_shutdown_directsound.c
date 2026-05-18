/*
 * Program: i76.exe
 * Function: shutdown_directsound
 * Entry: 00425e00
 * Signature: undefined4 __cdecl shutdown_directsound(int * param_1)
 */


/* i76 first-pass rename
   old_name: FUN_00425e00
   suggested_name: shutdown_directsound
   basis: DirectSound/COM shutdown path; calls CoUninitialize. */

undefined4 __cdecl shutdown_directsound(int *param_1)

{
  int *piVar1;
  int iVar2;
  
  if (param_1[1] != 0) {
    piVar1 = (int *)param_1[2];
    if (piVar1 != (int *)0x0) {
      (**(code **)(*piVar1 + 8))(piVar1);
    }
    (**(code **)(*(int *)param_1[1] + 8))((int *)param_1[1]);
    param_1[1] = 0;
    param_1[2] = 0;
  }
  piVar1 = (int *)*param_1;
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 8))(piVar1);
    *param_1 = 0;
    CoUninitialize();
  }
  for (iVar2 = 9; iVar2 != 0; iVar2 = iVar2 + -1) {
    *param_1 = 0;
    param_1 = param_1 + 1;
  }
  return 1;
}


