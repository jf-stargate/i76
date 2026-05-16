/*
 * Program: i76.exe
 * Function: dib_surface_context_update_helper_00476780
 * Entry: 00476780
 * Signature: int __cdecl dib_surface_context_update_helper_00476780(uint * param_1, ushort * param_2)
 */


/* cgpt readability rename set C v15: Readability pass set C: dib surface context update helper
   based on adjacent named subsystem context. */

int __cdecl dib_surface_context_update_helper_00476780(uint *param_1,ushort *param_2)

{
  byte bVar1;
  short sVar2;
  ushort uVar3;
  uint uVar4;
  int *piVar5;
  ushort *puVar6;
  
  puVar6 = param_2;
  if (param_2 == (ushort *)0x0) {
    return 0;
  }
  uVar3 = *param_2;
  param_2 = (ushort *)0x0;
  bVar1 = (byte)uVar3;
  while (bVar1 != 0) {
    uVar3 = *puVar6;
    if ((*param_1 & 0x100) == 0) {
      uVar4 = uVar3 & 0xff;
      if ((int)param_1[1] < (int)uVar4) {
        uVar4 = 0x2a;
      }
      piVar5 = (int *)param_1[uVar4 + 0x83];
    }
    else {
      sVar2 = *(short *)(DAT_006547e4 + (uVar3 & 0xffff00ff) * 2);
      if (sVar2 == 0) {
        uVar3 = uVar3 & 0xff;
      }
      else {
        uVar3 = sVar2 + (uVar3 >> 8);
      }
      piVar5 = (int *)param_1[uVar3 + 0x83];
    }
    param_2 = (ushort *)((int)param_2 + *piVar5 + 2);
    if ((((((DAT_005a7c94 == 0) || (bVar1 = (byte)*puVar6, bVar1 < 0x81)) || (bVar1 == 0x85)) ||
         ((bVar1 == 0x86 || (bVar1 == 0xeb)))) ||
        ((bVar1 == 0xec || ((0x90 < (bVar1 & 0xf0) && ((bVar1 & 0xf0) < 0xe0)))))) ||
       ((0xee < bVar1 && (bVar1 < 0xfa)))) {
      puVar6 = (ushort *)((int)puVar6 + 1);
    }
    else {
      puVar6 = puVar6 + 1;
    }
    bVar1 = (byte)*puVar6;
  }
  return (int)param_2;
}


