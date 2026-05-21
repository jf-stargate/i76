/*
 * Program: i76shell.dll
 * Function: set_shell_image_palette_remap_table
 * Entry: 1003ae6b
 * Signature: undefined __cdecl set_shell_image_palette_remap_table(undefined4 * param_1)
 */


void __cdecl set_shell_image_palette_remap_table(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = &DAT_1004ee3c;
  for (iVar1 = 0x40; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = *param_1;
    param_1 = param_1 + 1;
    puVar2 = puVar2 + 1;
  }
  return;
}


