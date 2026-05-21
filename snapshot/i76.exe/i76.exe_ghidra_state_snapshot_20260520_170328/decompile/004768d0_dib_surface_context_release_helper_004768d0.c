/*
 * Program: i76.exe
 * Function: dib_surface_context_release_helper_004768d0
 * Entry: 004768d0
 * Signature: undefined __stdcall dib_surface_context_release_helper_004768d0(void)
 */


/* cgpt readability rename set C v15: Readability pass set C: dib surface context release helper
   based on adjacent named subsystem context. */

void dib_surface_context_release_helper_004768d0(void)

{
  int iVar1;
  int *piVar2;
  
  piVar2 = &DAT_004fa020;
  iVar1 = 0x20;
  do {
    *piVar2 = iVar1;
    iVar1 = iVar1 + 0x20;
    piVar2 = piVar2 + 1;
  } while (iVar1 < 0x120);
  return;
}


