/*
 * Program: i76.exe
 * Function: format_screenshot_pcx_name
 * Entry: 0049e0a0
 * Signature: undefined __cdecl format_screenshot_pcx_name(int * param_1)
 */


/* cgpt whole-binary semantic rename v1: string evidence SCR%04d.pcx */

void __cdecl format_screenshot_pcx_name(int *param_1)

{
  int iVar1;
  char local_100 [256];
  
  iVar1 = DAT_005a7f28;
  DAT_005a7f28 = DAT_005a7f28 + 1;
  sprintf(local_100,s_SCR_04d_pcx_004fe6ac,iVar1);
  write_8bpp_pcx_file_with_palette(local_100,param_1,param_1 + 0x3a);
  return;
}


