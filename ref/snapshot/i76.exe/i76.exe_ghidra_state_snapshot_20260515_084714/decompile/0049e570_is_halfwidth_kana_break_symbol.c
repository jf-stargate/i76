/*
 * Program: i76.exe
 * Function: is_halfwidth_kana_break_symbol
 * Entry: 0049e570
 * Signature: undefined4 __cdecl is_halfwidth_kana_break_symbol(char * param_1)
 */


/* [cgpt i76.exe chunk/parser/text rename v5; confidence=medium] Single-byte
   halfwidth-kana/punctuation text-break classification helper. */

undefined4 __cdecl is_halfwidth_kana_break_symbol(char *param_1)

{
  char cVar1;
  
  if (param_1 == (char *)0x0) {
    return 0xffffffff;
  }
  cVar1 = *param_1;
  if ((((cVar1 != -0x5c) && (cVar1 != -0x5f)) && (cVar1 != -0x5b)) &&
     (((cVar1 != -0x5d && (cVar1 != -0x22)) && (cVar1 != -0x21)))) {
    return 0;
  }
  return 1;
}


