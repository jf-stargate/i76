/*
 * Program: i76.exe
 * Function: matrix_rotation_context_helper_00479780
 * Entry: 00479780
 * Signature: undefined __cdecl matrix_rotation_context_helper_00479780(undefined4 param_1, byte param_2)
 */


/* cgpt readability rename set D v16: Readability pass set D: matrix rotation context helper based
   on adjacent named subsystem context. */

void __cdecl matrix_rotation_context_helper_00479780(undefined4 param_1,byte param_2)

{
  int iVar1;
  undefined4 *puVar2;
  
  memmove(&g_palette_blend_table_c + (uint)param_2 * 0x40,&g_palette_blend_table_b,0x100);
  puVar2 = &DAT_0061b0a0;
  for (iVar1 = 0x40; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = CONCAT22(CONCAT11(param_2,param_2),CONCAT11(param_2,param_2));
    puVar2 = puVar2 + 1;
  }
  memmove(&g_palette_blend_table_a + (uint)param_2 * 0x40,&g_palette_blend_table_b,0x100);
  return;
}


