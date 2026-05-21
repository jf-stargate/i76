/*
 * Program: i76shell.dll
 * Function: hit_test_static_ui_descriptor_table
 * Entry: 100167a0
 * Signature: int * __cdecl hit_test_static_ui_descriptor_table(int * param_1, int param_2, int param_3)
 */


int * __cdecl hit_test_static_ui_descriptor_table(int *param_1,int param_2,int param_3)

{
  int *piVar1;
  int iVar2;
  
  if (param_1 != (int *)0x0) {
    iVar2 = *param_1;
    while (iVar2 != -1) {
      if ((((param_1[8] != 0) && (iVar2 <= param_2)) && (param_2 < param_1[2] + iVar2)) &&
         ((param_1[1] <= param_3 && (param_3 < param_1[3] + param_1[1])))) {
        return param_1;
      }
      piVar1 = param_1 + 0xb;
      param_1 = param_1 + 0xb;
      iVar2 = *piVar1;
    }
  }
  return (int *)0x0;
}


