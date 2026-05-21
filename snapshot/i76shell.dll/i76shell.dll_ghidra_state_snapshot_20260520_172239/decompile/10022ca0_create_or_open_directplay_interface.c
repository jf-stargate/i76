/*
 * Program: i76shell.dll
 * Function: create_or_open_directplay_interface
 * Entry: 10022ca0
 * Signature: undefined4 __stdcall create_or_open_directplay_interface(undefined4 * param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 create_or_open_directplay_interface(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 local_54;
  char local_47 [71];
  
  puVar2 = (undefined4 *)param_1[2];
  for (iVar1 = 0x480; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined4 *)param_1[1] = 0;
  puVar2 = &local_54;
  for (iVar1 = 0x14; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  _DAT_100d3948 = 0;
  *(undefined2 *)puVar2 = 0;
  *(undefined1 *)((int)puVar2 + 2) = 0;
  local_47[0] = s_0_1004cedc[0];
  local_47[1] = s_0_1004cedc[1];
  local_54._0_1_ = 0x53;
  dpEnumSessions(*param_1,&local_54,0,2000,query_directplay_service_provider_caps_or_guid,param_1);
  return 0;
}


