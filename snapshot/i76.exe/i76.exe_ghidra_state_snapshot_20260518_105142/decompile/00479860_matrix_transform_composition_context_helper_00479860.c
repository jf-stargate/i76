/*
 * Program: i76.exe
 * Function: matrix_transform_composition_context_helper_00479860
 * Entry: 00479860
 * Signature: undefined __stdcall matrix_transform_composition_context_helper_00479860(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set D v16: Readability pass set D: matrix transform composition context
   helper based on adjacent named subsystem context. */

void matrix_transform_composition_context_helper_00479860(void)

{
  undefined1 uVar1;
  int iVar2;
  undefined1 *puVar3;
  
  puVar3 = &DAT_006095a0;
  do {
    iVar2 = 0;
    do {
      _CIpow();
      uVar1 = ftol();
      puVar3[iVar2] = uVar1;
      iVar2 = iVar2 + 1;
    } while (iVar2 < 0x100);
    puVar3 = puVar3 + 0x100;
  } while ((int)puVar3 < 0x609fa0);
  return;
}


