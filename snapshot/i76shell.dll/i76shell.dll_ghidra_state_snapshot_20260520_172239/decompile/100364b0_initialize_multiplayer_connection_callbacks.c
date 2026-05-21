/*
 * Program: i76shell.dll
 * Function: initialize_multiplayer_connection_callbacks
 * Entry: 100364b0
 * Signature: undefined4 __cdecl initialize_multiplayer_connection_callbacks(undefined4 * param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl initialize_multiplayer_connection_callbacks(undefined4 *param_1)

{
  DAT_100f5324 = 0;
  DAT_100f5354 = 0;
  DAT_100f5320 = 1;
  _DAT_100f5328 = 0x2c;
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  dpEnumTransports(s_dll_1004d248,&LAB_10036500,param_1);
  return 1;
}


