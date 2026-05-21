/*
 * Program: i76shell.dll
 * Function: destroy_static_ui_descriptor_widgets
 * Entry: 10016760
 * Signature: undefined __cdecl destroy_static_ui_descriptor_widgets(int * param_1)
 */


void __cdecl destroy_static_ui_descriptor_widgets(int *param_1)

{
  int *piVar1;
  int iVar2;
  void *pvVar3;
  
  if (param_1 != (int *)0x0) {
    iVar2 = *param_1;
    while (iVar2 != -1) {
      pvVar3 = (void *)param_1[6];
      if (pvVar3 != (void *)0x0) {
        FUN_100378f0((int)pvVar3);
        operator_delete(pvVar3);
        param_1[6] = 0;
      }
      piVar1 = param_1 + 0xb;
      param_1 = param_1 + 0xb;
      iVar2 = *piVar1;
    }
  }
  return;
}


