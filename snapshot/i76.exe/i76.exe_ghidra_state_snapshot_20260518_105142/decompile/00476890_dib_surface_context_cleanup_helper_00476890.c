/*
 * Program: i76.exe
 * Function: dib_surface_context_cleanup_helper_00476890
 * Entry: 00476890
 * Signature: undefined __cdecl dib_surface_context_cleanup_helper_00476890(int param_1, int param_2)
 */


/* cgpt readability rename set C v15: Readability pass set C: dib surface context cleanup helper
   based on adjacent named subsystem context. */

void __cdecl dib_surface_context_cleanup_helper_00476890(int param_1,int param_2)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = 0;
  if (0 < param_1) {
    puVar1 = &DAT_004fa020;
    iVar2 = param_1;
    do {
      *puVar1 = *(undefined4 *)(param_2 + -0x4fa020 + (int)puVar1);
      puVar1 = puVar1 + 1;
      iVar2 = iVar2 + -1;
      iVar3 = param_1;
    } while (iVar2 != 0);
  }
  if (iVar3 < 8) {
    puVar1 = &DAT_004fa020 + iVar3;
    for (iVar2 = 8 - iVar3; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar1 = 0xffffffff;
      puVar1 = puVar1 + 1;
    }
  }
  return;
}


