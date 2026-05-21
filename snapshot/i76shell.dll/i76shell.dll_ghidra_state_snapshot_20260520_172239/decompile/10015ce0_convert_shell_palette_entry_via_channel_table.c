/*
 * Program: i76shell.dll
 * Function: convert_shell_palette_entry_via_channel_table
 * Entry: 10015ce0
 * Signature: undefined __cdecl convert_shell_palette_entry_via_channel_table(byte * param_1, undefined1 * param_2)
 */


void __cdecl convert_shell_palette_entry_via_channel_table(byte *param_1,undefined1 *param_2)

{
  int iVar1;
  
  iVar1 = DAT_10047704;
  *param_2 = (&DAT_100f67c0)[(uint)*param_1 + DAT_10047704 * 0x40];
  param_2[1] = (&DAT_100f67c0)[(uint)param_1[1] + iVar1 * 0x40];
  param_2[2] = (&DAT_100f67c0)[(uint)param_1[2] + iVar1 * 0x40];
  return;
}


