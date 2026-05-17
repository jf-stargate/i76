/*
 * Program: i76.exe
 * Function: measure_text_prefix_to_fit_hdc_width
 * Entry: 00499360
 * Signature: undefined __cdecl measure_text_prefix_to_fit_hdc_width(int * param_1, byte * param_2, int param_3, HDC param_4)
 */


/* [cgpt i76.exe damage dispatch rename v19; confidence=HIGH] Uses GetTextExtentExPointA to measure
   how many bytes/characters fit into a target HDC width. */

void __cdecl
measure_text_prefix_to_fit_hdc_width(int *param_1,byte *param_2,int param_3,HDC param_4)

{
  byte bVar1;
  int iVar2;
  BOOL BVar3;
  uint uVar4;
  int iVar5;
  byte *pbVar6;
  tagSIZE local_c;
  int local_4;
  
  iVar5 = 0;
  uVar4 = 0xffffffff;
  pbVar6 = param_2;
  do {
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    bVar1 = *pbVar6;
    pbVar6 = pbVar6 + 1;
  } while (bVar1 != 0);
  BVar3 = GetTextExtentExPointA
                    (param_4,(LPCSTR)param_2,~uVar4 - 1,param_3,&param_3,(LPINT)0x0,&local_c);
  iVar2 = param_3;
  if (BVar3 == 0) {
    *param_1 = 0;
    param_1[1] = local_c.cy;
    param_1[2] = local_4;
    return;
  }
  for (; iVar2 != 0; iVar2 = iVar2 + -1) {
    bVar1 = *param_2;
    if ((((((bVar1 < 0x81) || (bVar1 == 0x85)) || (bVar1 == 0x86)) ||
         ((bVar1 == 0xeb || (bVar1 == 0xec)))) ||
        ((0x90 < (bVar1 & 0xf0) && ((bVar1 & 0xf0) < 0xe0)))) || ((0xee < bVar1 && (bVar1 < 0xfa))))
    {
      iVar5 = iVar5 + 1;
    }
    param_2 = param_2 + 1;
  }
  *param_1 = iVar5;
  param_1[1] = param_3;
  param_1[2] = (int)param_2;
  return;
}


