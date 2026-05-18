/*
 * Program: i76.exe
 * Function: is_sjis_83_katakana_range_class
 * Entry: 0049e220
 * Signature: undefined4 __cdecl is_sjis_83_katakana_range_class(char * param_1)
 */


/* [cgpt i76.exe chunk/parser/text rename v5; confidence=medium] SJIS/DBCS text-break classification
   helper: lead 0x83, trail 0x9f..0xb6 or 0xbf..0xd6. */

undefined4 __cdecl is_sjis_83_katakana_range_class(char *param_1)

{
  byte bVar1;
  
  if (param_1 == (char *)0x0) {
    return 0xffffffff;
  }
  if ((*param_1 == -0x7d) &&
     (((bVar1 = param_1[1], 0x9e < bVar1 && (bVar1 < 0xb7)) || ((0xbe < bVar1 && (bVar1 < 0xd7))))))
  {
    return 1;
  }
  return 0;
}


