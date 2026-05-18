/*
 * Program: i76.exe
 * Function: is_sjis_84_extended_range_class
 * Entry: 0049e250
 * Signature: undefined4 __cdecl is_sjis_84_extended_range_class(char * param_1)
 */


/* [cgpt i76.exe chunk/parser/text rename v5; confidence=medium] SJIS/DBCS text-break classification
   helper: lead 0x84, trail 0x40..0x60 or 0x70..0x91. */

undefined4 __cdecl is_sjis_84_extended_range_class(char *param_1)

{
  byte bVar1;
  
  if (param_1 == (char *)0x0) {
    return 0xffffffff;
  }
  if ((*param_1 == -0x7c) &&
     (((bVar1 = param_1[1], 0x3f < bVar1 && (bVar1 < 0x61)) || ((0x6f < bVar1 && (bVar1 < 0x92))))))
  {
    return 1;
  }
  return 0;
}


