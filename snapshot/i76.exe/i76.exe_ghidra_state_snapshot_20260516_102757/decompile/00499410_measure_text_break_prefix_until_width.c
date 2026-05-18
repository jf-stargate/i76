/*
 * Program: i76.exe
 * Function: measure_text_break_prefix_until_width
 * Entry: 00499410
 * Signature: undefined __cdecl measure_text_break_prefix_until_width(int * param_1, byte * param_2, undefined4 param_3, undefined * param_4, undefined4 param_5)
 */


/* [cgpt i76.exe chunk/parser/text rename v5; confidence=high] Uses a measurement callback and
   parse_next_text_break_token to find a line-break-safe text prefix fitting a width limit. */

void __cdecl
measure_text_break_prefix_until_width
          (int *param_1,byte *param_2,undefined4 param_3,undefined *param_4,undefined4 param_5)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined1 local_18 [8];
  byte *local_10;
  int local_c;
  int local_8;
  
  iVar4 = 0;
  iVar5 = 0;
  if (*param_2 != 0) {
    if (param_4 == (undefined *)0x0) {
      param_4 = measure_multibyte_text_width_until_limit;
    }
    piVar2 = (int *)(*(code *)param_4)(local_18,param_2,param_3,param_5);
    iVar1 = *piVar2;
    local_8 = piVar2[1];
    if (*(char *)piVar2[2] == '\0') {
      iVar5 = *piVar2;
      iVar4 = piVar2[1];
      local_10 = (byte *)piVar2[2];
    }
    else {
      while( true ) {
        piVar2 = (int *)parse_next_text_break_token(&local_c,param_2);
        param_2 = (byte *)piVar2[2];
        if ((*piVar2 == 0) || (iVar3 = *piVar2 + iVar5, iVar1 < iVar3)) break;
        iVar4 = iVar4 + piVar2[1];
        iVar5 = iVar3;
        local_10 = param_2;
      }
    }
  }
  *param_1 = iVar5;
  param_1[1] = iVar4;
  param_1[2] = (int)local_10;
  return;
}


