/*
 * Program: i76.exe
 * Function: dib_surface_palette_context_helper_00476450
 * Entry: 00476450
 * Signature: undefined4 __cdecl dib_surface_palette_context_helper_00476450(int * param_1)
 */


/* cgpt readability rename set C v15: Readability pass set C: dib surface palette context helper
   based on adjacent named subsystem context. */

undefined4 __cdecl dib_surface_palette_context_helper_00476450(int *param_1)

{
  undefined1 uVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  undefined1 *puVar6;
  undefined1 *puVar7;
  
  uVar2 = DAT_005dd32c;
  if (param_1[5] != 0) {
    iVar4 = *param_1;
    puVar7 = (undefined1 *)(param_1[5] + -1 + iVar4);
    uVar3 = (param_1[1] & 0xffffU) >> 2;
    uVar5 = param_1[1] & 3;
    do {
      uVar1 = puVar7[iVar4 + -1];
      *puVar7 = puVar7[-1];
      puVar7[iVar4] = uVar1;
      uVar1 = puVar7[iVar4 * 2 + -1];
      uVar2 = CONCAT31((int3)((uint)uVar2 >> 8),uVar1);
      puVar7[iVar4 * 2] = uVar1;
      puVar7[iVar4 * 3] = uVar1;
      puVar7 = puVar7 + iVar4 * 4;
      uVar3 = uVar3 - 1;
    } while (uVar3 != 0);
    for (; uVar5 != 0; uVar5 = uVar5 - 1) {
      *puVar7 = uVar1;
      puVar7 = puVar7 + iVar4;
    }
    puVar6 = puVar7 + iVar4 * -2 + 1 + -iVar4;
    puVar7 = puVar7 + iVar4 * -2 + 1;
    for (; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar7 = *puVar6;
      puVar6 = puVar6 + 1;
      puVar7 = puVar7 + 1;
    }
  }
  return uVar2;
}


