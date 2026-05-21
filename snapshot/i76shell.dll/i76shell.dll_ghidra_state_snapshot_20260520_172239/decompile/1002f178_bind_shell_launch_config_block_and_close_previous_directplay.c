/*
 * Program: i76shell.dll
 * Function: bind_shell_launch_config_block_and_close_previous_directplay
 * Entry: 1002f178
 * Signature: undefined __cdecl bind_shell_launch_config_block_and_close_previous_directplay(byte * param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl bind_shell_launch_config_block_and_close_previous_directplay(byte *param_1)

{
  byte *pbVar1;
  
  DAT_100f231c = param_1;
  if ((*param_1 & 0x10) != 0) {
    s_0_1004cedc[0] = 'v';
    s_0_1004cedc[1] = '\'';
  }
  if ((*param_1 & 0x20) != 0) {
    s_0_1004cedc[0] = '/';
    s_0_1004cedc[1] = '\x01';
  }
  if (*(int *)(param_1 + 8) != 0) {
    DAT_100f21cc = 0;
    _DAT_100f21dc = 0;
    DAT_100f4ee8 = *(int *)(param_1 + 8);
    param_1[0x94] = 0;
    param_1[0x95] = 0;
    param_1[0x96] = 0;
    param_1[0x97] = 0;
    dpDestroyPlayer(DAT_100f4ee8,*(undefined2 *)(DAT_100f231c + 0xc));
    pbVar1 = DAT_100f231c;
    pbVar1[0xc] = 0;
    pbVar1[0xd] = 0;
    dpClose(DAT_100f4ee8);
  }
  return;
}


