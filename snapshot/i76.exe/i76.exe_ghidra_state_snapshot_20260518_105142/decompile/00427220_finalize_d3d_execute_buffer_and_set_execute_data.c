/*
 * Program: i76.exe
 * Function: finalize_d3d_execute_buffer_and_set_execute_data
 * Entry: 00427220
 * Signature: undefined4 __cdecl finalize_d3d_execute_buffer_and_set_execute_data(undefined4 * param_1)
 */


/* cgpt rename v8 display/d3d cluster: Writes execute-buffer terminators, unlocks the buffer when
   needed, fills execute data, and calls SetExecuteData. */

undefined4 __cdecl finalize_d3d_execute_buffer_and_set_execute_data(undefined4 *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int local_30 [4];
  int iStack_20;
  
  if ((undefined1 *)param_1[4] == (undefined1 *)param_1[3]) {
    return 0;
  }
  *(undefined1 *)param_1[4] = 0xb;
  *(undefined1 *)(param_1[4] + 1) = 0;
  *(undefined2 *)(param_1[4] + 2) = 0;
  iVar1 = param_1[4];
  iVar2 = param_1[3];
  param_1[4] = iVar1 + 4;
  *DAT_0052676c = 2;
  *(undefined2 *)(DAT_0052676c + 1) = 0;
  *(undefined2 *)((int)DAT_0052676c + 6) = 0;
  DAT_0052676c[2] = param_1[6];
  DAT_0052676c[3] = 0;
  DAT_0052676c = DAT_0052676c + 4;
  if (param_1[5] == 2) {
    (**(code **)(*(int *)*param_1 + 0x14))((int *)*param_1);
    param_1[5] = 3;
  }
  local_30[2] = param_1[6];
  piVar4 = local_30;
  for (iVar3 = 0xc; iVar3 != 0; iVar3 = iVar3 + -1) {
    *piVar4 = 0;
    piVar4 = piVar4 + 1;
  }
  local_30[3] = param_1[3] - param_1[1];
  local_30[0] = 0x30;
  iStack_20 = (iVar1 + 4) - iVar2;
  (**(code **)(*(int *)*param_1 + 0x18))((int *)*param_1,local_30);
  return 1;
}


