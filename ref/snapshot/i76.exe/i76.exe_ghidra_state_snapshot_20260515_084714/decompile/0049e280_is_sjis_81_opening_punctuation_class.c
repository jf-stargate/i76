/*
 * Program: i76.exe
 * Function: is_sjis_81_opening_punctuation_class
 * Entry: 0049e280
 * Signature: undefined4 __cdecl is_sjis_81_opening_punctuation_class(char * param_1)
 */


/* [cgpt i76.exe chunk/parser/text rename v5; confidence=medium] SJIS/DBCS text-break classification
   helper for selected 0x81 punctuation trails used as non-break/opening punctuation class. */

undefined4 __cdecl is_sjis_81_opening_punctuation_class(char *param_1)

{
  if (param_1 == (char *)0x0) {
    return 0xffffffff;
  }
  if (*param_1 == -0x7f) {
    switch(param_1[1]) {
    case 'A':
    case 'B':
    case 'C':
    case 'D':
    case 'F':
    case 'G':
    case 'H':
    case 'I':
    case 'f':
    case 'h':
    case 'j':
    case 'l':
    case 'n':
    case 'p':
    case 'r':
    case 't':
    case 'v':
    case 'x':
    case 'z':
      return 1;
    default:
    }
  }
  return 0;
}


