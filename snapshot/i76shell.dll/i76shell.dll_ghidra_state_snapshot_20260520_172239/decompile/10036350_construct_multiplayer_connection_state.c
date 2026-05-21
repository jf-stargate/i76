/*
 * Program: i76shell.dll
 * Function: construct_multiplayer_connection_state
 * Entry: 10036350
 * Signature: undefined4 __cdecl construct_multiplayer_connection_state(undefined4 * param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl construct_multiplayer_connection_state(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  DAT_100f5324 = 2;
  DAT_100f5354 = 0;
  DAT_100f5320 = 0;
  _DAT_100f5328 = 0x2c;
  puVar2 = param_1;
  for (iVar1 = 0x20; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  dpEnumTransports(s_dll_1004d234,&LAB_100363a0,param_1);
  return 1;
}


