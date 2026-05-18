/*
 * Program: i76.exe
 * Function: is_sjis_81_leading_quote_class
 * Entry: 0049e5a0
 * Signature: undefined4 __cdecl is_sjis_81_leading_quote_class(char * param_1)
 */


/* [cgpt i76.exe chunk/parser/text rename v5; confidence=medium] SJIS/DBCS text-break classification
   helper for selected 0x81 quote/opening punctuation trails. */

undefined4 __cdecl is_sjis_81_leading_quote_class(char *param_1)

{
  if (param_1 == (char *)0x0) {
    return 0xffffffff;
  }
  if (*param_1 == -0x7f) {
    switch(param_1[1]) {
    case 'e':
    case 'h':
    case 'i':
    case 'k':
    case 'm':
    case 'o':
    case 'q':
    case 's':
    case 'u':
    case 'w':
    case 'y':
      return 1;
    default:
    }
  }
  return 0;
}


