/*
 * Program: i76.exe
 * Function: parse_next_text_break_token
 * Entry: 0049e690
 * Signature: undefined __cdecl parse_next_text_break_token(int * param_1, byte * param_2)
 */


/* [cgpt i76.exe chunk/parser/text rename v5; confidence=high] Parses the next line-break token in
   multibyte text using punctuation, kana/full-width, DBCS, and alphanumeric classification helpers.
    */

void __cdecl parse_next_text_break_token(int *param_1,byte *param_2)

{
  byte bVar1;
  bool bVar2;
  int iVar3;
  byte *pbVar4;
  int iVar5;
  int iVar6;
  int local_c;
  int local_4;
  
  iVar6 = 0;
  bVar2 = false;
  if (param_2 != (byte *)0x0) {
    bVar1 = *param_2;
    iVar5 = 0;
    while ((bVar1 != 0 && (!bVar2))) {
      bVar1 = *param_2;
      if ((((bVar1 < 0x81) || (((bVar1 == 0x85 || (bVar1 == 0x86)) || (bVar1 == 0xeb)))) ||
          (bVar1 == 0xec)) ||
         (((0x90 < (bVar1 & 0xf0) && ((bVar1 & 0xf0) < 0xe0)) || ((0xee < bVar1 && (bVar1 < 0xfa))))
         )) {
        iVar3 = 0;
      }
      else {
        iVar3 = 1;
      }
      iVar6 = iVar6 + 1;
      iVar5 = iVar5 + 1 + iVar3;
      pbVar4 = param_2;
      if (param_2 != (byte *)0x0) {
        if ((((0x80 < bVar1) && (bVar1 != 0x85)) &&
            ((bVar1 != 0x86 && ((bVar1 != 0xeb && (bVar1 != 0xec)))))) &&
           ((((bVar1 & 0xf0) < 0x91 || (0xdf < (bVar1 & 0xf0))) &&
            ((bVar1 < 0xef || (0xf9 < bVar1)))))) {
          pbVar4 = param_2 + 1;
        }
        pbVar4 = pbVar4 + 1;
      }
      if (((param_2 == (byte *)0x0) || (pbVar4 == (byte *)0x0)) ||
         ((((iVar3 = is_sjis_81_leading_quote_class((char *)param_2), iVar3 == 0 &&
            (((iVar3 = is_sjis_81_closing_quote_class((char *)param_2), iVar3 == 0 &&
              (*param_2 != 0xa2)) &&
             (iVar3 = is_sjis_81_opening_punctuation_class((char *)pbVar4), iVar3 == 0)))) &&
           (((iVar3 = is_sjis_closing_punctuation_class((char *)pbVar4), iVar3 == 0 &&
             (iVar3 = is_sjis_81_nonbreak_symbol_class((char *)pbVar4), iVar3 == 0)) &&
            (iVar3 = is_halfwidth_kana_break_symbol((char *)pbVar4), iVar3 == 0)))) &&
          (((((*param_2 < 0xa1 || (0xdf < *param_2)) &&
             (iVar3 = is_sjis_83_40_to_96_class((char *)param_2), iVar3 == 0)) ||
            (((*pbVar4 < 0xa1 || (0xdf < *pbVar4)) &&
             (iVar3 = is_sjis_83_40_to_96_class((char *)pbVar4), iVar3 == 0)))) &&
           (((iVar3 = _ismbcalnum((int)(char)*param_2), iVar3 == 0 ||
             (iVar3 = _ismbcalnum((int)(char)*pbVar4), iVar3 == 0)) &&
            ((((*param_2 != 0x82 ||
               ((((bVar1 = param_2[1], bVar1 < 0x4f || (0x58 < bVar1)) &&
                 ((bVar1 < 0x60 || (0x79 < bVar1)))) && ((bVar1 < 0x81 || (0x79 < bVar1)))))) ||
              ((*pbVar4 != 0x82 ||
               ((((bVar1 = pbVar4[1], bVar1 < 0x4f || (0x58 < bVar1)) &&
                 ((bVar1 < 0x60 || (0x79 < bVar1)))) && ((bVar1 < 0x81 || (0x79 < bVar1)))))))) &&
             ((((*param_2 != 0x83 ||
                (((bVar1 = param_2[1], bVar1 < 0x9f || (0xb6 < bVar1)) &&
                 ((bVar1 < 0xbf || (0xd6 < bVar1)))))) ||
               (iVar3 = is_sjis_83_katakana_range_class((char *)pbVar4), iVar3 == 0)) &&
              (((iVar3 = is_sjis_84_extended_range_class((char *)param_2), iVar3 == 0 ||
                (iVar3 = is_sjis_84_extended_range_class((char *)pbVar4), iVar3 == 0)) &&
               (iVar3 = _ismbcpunct((int)(char)*pbVar4), iVar3 == 0)))))))))))))) {
        bVar2 = true;
      }
      bVar1 = *pbVar4;
      param_2 = pbVar4;
    }
    *param_1 = iVar6;
    param_1[1] = iVar5;
    param_1[2] = (int)param_2;
    return;
  }
  *param_1 = local_c;
  param_1[1] = 0;
  param_1[2] = local_4;
  return;
}


