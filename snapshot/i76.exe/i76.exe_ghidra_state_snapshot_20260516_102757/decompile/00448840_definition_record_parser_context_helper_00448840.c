/*
 * Program: i76.exe
 * Function: definition_record_parser_context_helper_00448840
 * Entry: 00448840
 * Signature: undefined4 __cdecl definition_record_parser_context_helper_00448840(char * param_1, char * param_2)
 */


/* cgpt label refinement v18: was definition_record_parser_definition_parser_helper_00448840. Remove
   duplicated parser wording. */

undefined4 __cdecl definition_record_parser_context_helper_00448840(char *param_1,char *param_2)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  
  iVar2 = -1;
  uVar4 = 0;
  pcVar5 = param_2;
  do {
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar5 + 1;
  } while (cVar1 != '\0');
  if (iVar2 == -2) {
    return 0;
  }
  do {
    if (*param_1 == param_2[uVar4]) {
      return 1;
    }
    uVar3 = 0xffffffff;
    uVar4 = uVar4 + 1;
    pcVar5 = param_2;
    do {
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      cVar1 = *pcVar5;
      pcVar5 = pcVar5 + 1;
    } while (cVar1 != '\0');
    if (~uVar3 - 1 <= uVar4) {
      return 0;
    }
  } while( true );
}


