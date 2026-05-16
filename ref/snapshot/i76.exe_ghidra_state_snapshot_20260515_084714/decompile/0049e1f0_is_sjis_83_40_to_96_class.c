/*
 * Program: i76.exe
 * Function: is_sjis_83_40_to_96_class
 * Entry: 0049e1f0
 * Signature: undefined4 __cdecl is_sjis_83_40_to_96_class(char * param_1)
 */


/* [cgpt i76.exe chunk/parser/text rename v5; confidence=medium] SJIS/DBCS text-break classification
   helper: lead 0x83, trail 0x40..0x96 except 0x7f. */

undefined4 __cdecl is_sjis_83_40_to_96_class(char *param_1)

{
  byte bVar1;
  
  if (param_1 == (char *)0x0) {
    return 0xffffffff;
  }
  if ((((*param_1 == -0x7d) && (bVar1 = param_1[1], 0x3f < bVar1)) && (bVar1 < 0x97)) &&
     (bVar1 != 0x7f)) {
    return 1;
  }
  return 0;
}


