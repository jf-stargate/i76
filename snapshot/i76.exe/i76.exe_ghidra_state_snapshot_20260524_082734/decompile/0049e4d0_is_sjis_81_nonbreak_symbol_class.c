/*
 * Program: i76.exe
 * Function: is_sjis_81_nonbreak_symbol_class
 * Entry: 0049e4d0
 * Signature: undefined4 __cdecl is_sjis_81_nonbreak_symbol_class(char * param_1)
 */


/* [cgpt i76.exe chunk/parser/text rename v5; confidence=medium] SJIS/DBCS text-break classification
   helper for selected 0x81 symbol trails that affect line break eligibility. */

undefined4 __cdecl is_sjis_81_nonbreak_symbol_class(char *param_1)

{
  if (param_1 == (char *)0x0) {
    return 0xffffffff;
  }
  if (*param_1 == -0x7f) {
    switch(param_1[1]) {
    case 'J':
    case 'K':
    case 'R':
    case 'S':
    case 'T':
    case 'U':
    case '\\':
    case ']':
    case -0x75:
    case -0x74:
    case -0x73:
    case -0x72:
    case -0x6d:
      return 1;
    default:
    }
  }
  return 0;
}


