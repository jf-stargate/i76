/*
 * Program: i76.exe
 * Function: matrix_vector_projection_context_helper_00478b30
 * Entry: 00478b30
 * Signature: undefined __stdcall matrix_vector_projection_context_helper_00478b30(void)
 */


/* cgpt readability rename set D v16: Readability pass set D: matrix vector projection context
   helper based on adjacent named subsystem context. */

void matrix_vector_projection_context_helper_00478b30(void)

{
  int iVar1;
  undefined1 uVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  
  iVar3 = 0;
  puVar4 = &g_palette_blend_table_c;
  do {
    uVar2 = (undefined1)iVar3;
    (&g_palette_blend_table_b)[iVar3] = uVar2;
    puVar5 = puVar4 + 0x40;
    iVar3 = iVar3 + 1;
    for (iVar1 = 0x40; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar4 = CONCAT22(CONCAT11(uVar2,uVar2),CONCAT11(uVar2,uVar2));
      puVar4 = puVar4 + 1;
    }
    puVar4 = puVar5;
  } while ((int)puVar5 < 0x63b2c0);
  puVar4 = &DAT_0061b0a0;
  for (iVar3 = 0x40; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = 0xffffffff;
    puVar4 = puVar4 + 1;
  }
  return;
}


