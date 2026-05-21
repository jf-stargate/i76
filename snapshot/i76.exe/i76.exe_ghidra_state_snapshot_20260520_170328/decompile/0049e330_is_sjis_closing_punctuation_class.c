/*
 * Program: i76.exe
 * Function: is_sjis_closing_punctuation_class
 * Entry: 0049e330
 * Signature: undefined4 __cdecl is_sjis_closing_punctuation_class(char * param_1)
 */


/* [cgpt i76.exe chunk/parser/text rename v5; confidence=medium] SJIS/DBCS text-break classification
   helper for selected 0x81/0x82 closing punctuation and related marks. */

undefined4 __cdecl is_sjis_closing_punctuation_class(char *param_1)

{
  char cVar1;
  bool bVar2;
  
  if (param_1 == (char *)0x0) {
    return 0xffffffff;
  }
  cVar1 = *param_1;
  bVar2 = false;
  if (cVar1 == -0x7d) {
    switch(param_1[1]) {
    case '@':
    case 'B':
    case 'D':
    case 'F':
    case 'H':
    case -0x7d:
    case -0x7b:
    case -0x79:
    case -0x72:
switchD_0049e35a_caseD_40:
      bVar2 = true;
      break;
    default:
switchD_0049e35a_caseD_41:
      bVar2 = false;
    }
LAB_0049e38e:
    if (!bVar2) {
      if (cVar1 == -0x7d) {
        if (param_1[1] == 'b') {
          return 1;
        }
      }
      else if ((cVar1 == -0x7e) && (param_1[1] == -0x3f)) {
        return 1;
      }
      if (((cVar1 != -0x7d) || ((param_1[1] != -0x6b && (param_1[1] != -0x6a)))) &&
         ((cVar1 != -0x7f || ((param_1[1] != 'X' && (param_1[1] != '[')))))) {
        return 0;
      }
    }
    return 1;
  }
  if (cVar1 != -0x7e) goto LAB_0049e38e;
  switch(param_1[1]) {
  case -0x61:
  case -0x5f:
  case -0x5d:
  case -0x5b:
  case -0x59:
  case -0x1f:
  case -0x1d:
  case -0x1b:
  case -0x14:
    goto switchD_0049e35a_caseD_40;
  default:
    goto switchD_0049e35a_caseD_41;
  }
}


