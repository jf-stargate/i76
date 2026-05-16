/*
 * Program: i76.exe
 * Function: matrix_identity_or_copy_context_helper_00479740
 * Entry: 00479740
 * Signature: undefined __cdecl matrix_identity_or_copy_context_helper_00479740(uint param_1, undefined1 param_2)
 */


/* cgpt readability rename set D v16: Readability pass set D: matrix identity or copy context helper
   based on adjacent named subsystem context. */

void __cdecl matrix_identity_or_copy_context_helper_00479740(uint param_1,undefined1 param_2)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = &g_palette_blend_table_c + (param_1 & 0xff) * 0x40;
  for (iVar1 = 0x40; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = CONCAT22(CONCAT11(param_2,param_2),CONCAT11(param_2,param_2));
    puVar2 = puVar2 + 1;
  }
  return;
}


