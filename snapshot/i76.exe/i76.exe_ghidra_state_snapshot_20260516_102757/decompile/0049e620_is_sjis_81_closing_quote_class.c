/*
 * Program: i76.exe
 * Function: is_sjis_81_closing_quote_class
 * Entry: 0049e620
 * Signature: undefined4 __cdecl is_sjis_81_closing_quote_class(char * param_1)
 */


/* [cgpt i76.exe chunk/parser/text rename v5; confidence=medium] SJIS/DBCS text-break classification
   helper for selected 0x81 closing quote/punctuation trails. */

undefined4 __cdecl is_sjis_81_closing_quote_class(char *param_1)

{
  if (param_1 == (char *)0x0) {
    return 0xffffffff;
  }
  if (*param_1 == -0x7f) {
    switch(param_1[1]) {
    case -0x71:
    case -0x70:
    case -0x6f:
    case -0x6e:
    case -0x6c:
    case -0x69:
    case -0x68:
    case -0x59:
      return 1;
    default:
    }
  }
  return 0;
}


