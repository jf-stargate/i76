/*
 * Program: i76shell.dll
 * Function: reset_multiplayer_connection_session_state
 * Entry: 10036550
 * Signature: undefined4 __cdecl reset_multiplayer_connection_session_state(undefined4 * param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl reset_multiplayer_connection_session_state(undefined4 *param_1)

{
  uint uVar1;
  time_t tVar2;
  
  DAT_100f5324 = 3;
  DAT_100f5354 = 1;
  DAT_100f5320 = 0;
  _DAT_100f5328 = 0x2c;
  uVar1 = clock();
  tVar2 = time((time_t *)0x0);
  _DAT_100f532c = rand();
  _DAT_100f532c = uVar1 | (uint)tVar2 | _DAT_100f532c;
  _DAT_100f5330 = 0;
  _DAT_100f5334 = 0x4b00;
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  dpEnumTransports(s_dll_1004d24c,&LAB_100365e0,param_1);
  return 1;
}


