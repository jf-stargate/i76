/*
 * Program: i76.exe
 * Function: dib_surface_context_setter_helper_004766e0
 * Entry: 004766e0
 * Signature: undefined __cdecl dib_surface_context_setter_helper_004766e0(int param_1, int param_2)
 */


/* cgpt readability rename set C v15: Readability pass set C: dib surface context setter helper
   based on adjacent named subsystem context. */

void __cdecl dib_surface_context_setter_helper_004766e0(int param_1,int param_2)

{
  int iVar1;
  undefined2 uVar2;
  undefined4 *puVar3;
  
  if ((-1 < param_2) && (param_2 < 0x100)) {
    uVar2 = CONCAT11((char)param_2,(char)param_2);
    puVar3 = (undefined4 *)(param_1 + 0x10c);
    for (iVar1 = 0x40; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar3 = CONCAT22(uVar2,uVar2);
      puVar3 = puVar3 + 1;
    }
    return;
  }
  memmove((void *)(param_1 + 0x10c),&g_palette_blend_table_b,0x100);
  return;
}


