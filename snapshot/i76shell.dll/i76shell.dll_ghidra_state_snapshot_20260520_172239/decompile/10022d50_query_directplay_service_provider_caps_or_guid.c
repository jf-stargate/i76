/*
 * Program: i76shell.dll
 * Function: query_directplay_service_provider_caps_or_guid
 * Entry: 10022d50
 * Signature: undefined4 __stdcall query_directplay_service_provider_caps_or_guid(undefined4 * param_1, undefined4 param_2, undefined4 param_3, int param_4)
 */


undefined4
query_directplay_service_provider_caps_or_guid
          (undefined4 *param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  if (param_1 != (undefined4 *)0x0) {
    strncpy((char *)(**(int **)(param_4 + 4) * 0x90 + *(int *)(param_4 + 8)),
            (char *)((int)param_1 + 0x17),0x20);
    puVar2 = param_1;
    puVar3 = (undefined4 *)(**(int **)(param_4 + 4) * 0x90 + 0x20 + *(int *)(param_4 + 8));
    for (iVar1 = 0x14; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar3 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar3 = puVar3 + 1;
    }
    *(undefined2 *)puVar3 = *(undefined2 *)puVar2;
    *(undefined1 *)((int)puVar3 + 2) = *(undefined1 *)((int)puVar2 + 2);
    *(int *)(**(int **)(param_4 + 4) * 0x90 + 0x7c + *(int *)(param_4 + 8)) =
         (int)*(short *)((int)param_1 + 0x11);
    *(int *)(**(int **)(param_4 + 4) * 0x90 + 0x78 + *(int *)(param_4 + 8)) =
         (int)*(short *)((int)param_1 + 0x13);
    *(uint *)(**(int **)(param_4 + 4) * 0x90 + 0x84 + *(int *)(param_4 + 8)) =
         *(uint *)((int)param_1 + 0x4f) >> 0x1f;
    *(uint *)(**(int **)(param_4 + 4) * 0x90 + 0x88 + *(int *)(param_4 + 8)) =
         *(uint *)((int)param_1 + 0x4f) >> 0x1e & 1;
    *(uint *)(**(int **)(param_4 + 4) * 0x90 + 0x8c + *(int *)(param_4 + 8)) =
         *(uint *)((int)param_1 + 0x4f) & 0x3fffffff;
    **(int **)(param_4 + 4) = **(int **)(param_4 + 4) + 1;
    return 1;
  }
  DAT_100f355c = 2;
  return 0;
}


