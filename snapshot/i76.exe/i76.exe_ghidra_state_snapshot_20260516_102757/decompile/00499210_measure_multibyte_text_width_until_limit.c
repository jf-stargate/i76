/*
 * Program: i76.exe
 * Function: measure_multibyte_text_width_until_limit
 * Entry: 00499210
 * Signature: undefined __cdecl measure_multibyte_text_width_until_limit(int * param_1, ushort * param_2, int param_3, uint * param_4)
 */


/* [cgpt i76.exe chunk/parser/text rename v5; confidence=high] Measures glyph advance over
   ASCII/DBCS text until a pixel/advance limit and returns character count, byte count, and end
   pointer. */

void __cdecl
measure_multibyte_text_width_until_limit(int *param_1,ushort *param_2,int param_3,uint *param_4)

{
  byte bVar1;
  short sVar2;
  ushort uVar3;
  uint uVar4;
  int *piVar5;
  ushort *puVar6;
  int local_18;
  int local_14;
  int local_c;
  int local_8;
  
  local_8 = 0;
  local_c = 0;
  if (param_2 != (ushort *)0x0) {
    bVar1 = (byte)*param_2;
    puVar6 = param_2;
    while ((bVar1 != 0 && (local_c < param_3))) {
      uVar3 = *puVar6;
      if ((*param_4 & 0x100) == 0) {
        uVar4 = uVar3 & 0xff;
        if ((int)param_4[1] < (int)uVar4) {
          uVar4 = 0x2a;
        }
        piVar5 = (int *)param_4[uVar4 + 0x83];
      }
      else {
        sVar2 = *(short *)(DAT_006547e4 + (uVar3 & 0xffff00ff) * 2);
        if (sVar2 == 0) {
          uVar3 = uVar3 & 0xff;
        }
        else {
          uVar3 = sVar2 + (uVar3 >> 8);
        }
        piVar5 = (int *)param_4[uVar3 + 0x83];
      }
      local_c = local_c + *piVar5;
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
      local_8 = local_8 + 1;
    }
    *param_1 = local_8;
    param_1[1] = (int)puVar6 - (int)param_2;
    param_1[2] = (int)puVar6;
    return;
  }
  *param_1 = 0;
  param_1[1] = local_18;
  param_1[2] = local_14;
  return;
}


