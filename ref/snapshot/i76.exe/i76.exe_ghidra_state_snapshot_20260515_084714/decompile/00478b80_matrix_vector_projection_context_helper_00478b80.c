/*
 * Program: i76.exe
 * Function: matrix_vector_projection_context_helper_00478b80
 * Entry: 00478b80
 * Signature: undefined __cdecl matrix_vector_projection_context_helper_00478b80(undefined4 param_1, uint param_2, uint param_3, uint param_4)
 */


/* cgpt readability rename set D v16: Readability pass set D: matrix vector projection context
   helper based on adjacent named subsystem context. */

void __cdecl
matrix_vector_projection_context_helper_00478b80
          (undefined4 param_1,uint param_2,uint param_3,uint param_4)

{
  undefined1 uVar1;
  int iVar2;
  undefined *puVar3;
  int iVar4;
  uint uVar5;
  undefined1 *puVar6;
  int iVar7;
  
  iVar2 = (param_3 & 0xff) * 0x10000 + (param_2 & 0xff) * -0x10000;
  uVar5 = param_4 & 0xff;
  iVar7 = 0x20;
  iVar4 = (param_2 & 0xff) * 0x10000 + 0x8000;
  puVar6 = &DAT_0061b2a0 + uVar5;
  do {
    *puVar6 = (char)((uint)iVar4 >> 0x10);
    puVar6 = puVar6 + 0x100;
    iVar7 = iVar7 + -1;
    iVar4 = iVar4 + ((int)(iVar2 + (iVar2 >> 0x1f & 0x1fU)) >> 5);
  } while (iVar7 != 0);
  puVar3 = &DAT_0061d2a0 + uVar5;
  uVar1 = (&DAT_0061d1a0)[uVar5];
  iVar4 = 0x70;
  do {
    *puVar3 = uVar1;
    puVar3 = puVar3 + 0x100;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  puVar3 = &DAT_0062b1a0 + uVar5;
  uVar1 = (&DAT_0061b2a0)[uVar5];
  iVar4 = 0x70;
  do {
    *puVar3 = uVar1;
    puVar3 = puVar3 + -0x100;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  return;
}


