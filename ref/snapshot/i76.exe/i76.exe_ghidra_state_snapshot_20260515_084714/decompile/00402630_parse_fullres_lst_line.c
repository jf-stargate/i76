/*
 * Program: i76.exe
 * Function: parse_fullres_lst_line
 * Entry: 00402630
 * Signature: char * __cdecl parse_fullres_lst_line(char * param_1, char * param_2, char * param_3, char * param_4)
 */


/* [cgpt i76.exe image payload renames v28; confidence=medium-high] Parses one FULLRES.LST line into
   an asset/name entry used by the full-resolution texture bitset. */

char * __cdecl parse_fullres_lst_line(char *param_1,char *param_2,char *param_3,char *param_4)

{
  char cVar1;
  char *pcVar2;
  
  for (; (param_3 < param_4 &&
         (((cVar1 = *param_3, cVar1 == ' ' || (cVar1 == '\n')) || (cVar1 == '\r'))));
      param_3 = param_3 + 1) {
  }
  if (param_4 <= param_3 + 1) {
    return (char *)0x0;
  }
  if (param_3[1] == ' ') {
    cVar1 = *param_3;
    param_3 = param_3 + 2;
    *param_1 = cVar1;
  }
  else {
    *param_1 = 'p';
  }
  for (; ((param_3 < param_4 && (cVar1 = *param_3, cVar1 != ' ')) &&
         ((cVar1 != '\n' && (cVar1 != '\r')))); param_3 = param_3 + 1) {
    *param_2 = cVar1;
    param_2 = param_2 + 1;
  }
  *param_2 = '\0';
  if (param_3 < param_4) {
    do {
      pcVar2 = param_3;
      param_3 = pcVar2 + 1;
      if (*pcVar2 == '\n') break;
    } while (param_3 < param_4);
    if ((param_3 < param_4) && (*param_3 == '\r')) {
      param_3 = pcVar2 + 2;
    }
  }
  return param_3;
}


