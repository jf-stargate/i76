/*
 * Program: i76.exe
 * Function: definition_record_parser_context_helper_00448890
 * Entry: 00448890
 * Signature: undefined __cdecl definition_record_parser_context_helper_00448890(char * param_1, char * param_2, char * param_3)
 */


/* cgpt label refinement v18: was definition_record_parser_definition_parser_helper_00448890. Remove
   duplicated parser wording. */

void __cdecl
definition_record_parser_context_helper_00448890(char *param_1,char *param_2,char *param_3)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  size_t _Count;
  uint uVar4;
  char *pcVar5;
  
  _Count = 0xffffffff;
  if (param_1 != (char *)0x0) {
    DAT_00531d00 = param_1;
  }
  if (DAT_00531d00 != (char *)0x0) {
    param_1 = strpbrk(DAT_00531d00,param_2);
    _Count = (int)param_1 - (int)DAT_00531d00;
  }
  pcVar5 = param_3;
  for (iVar2 = 0x19; iVar2 != 0; iVar2 = iVar2 + -1) {
    pcVar5[0] = '\0';
    pcVar5[1] = '\0';
    pcVar5[2] = '\0';
    pcVar5[3] = '\0';
    pcVar5 = pcVar5 + 4;
  }
  if ((0 < (int)_Count) && (DAT_00531d00 != (char *)0x0)) {
    strncpy(param_3,DAT_00531d00,_Count);
  }
  if (param_1 == (char *)0x0) {
    DAT_00531d00 = param_1;
    return;
  }
  do {
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
      DAT_00531d00 = param_1;
      return;
    }
    while (*param_1 != param_2[uVar4]) {
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
        DAT_00531d00 = param_1;
        return;
      }
    }
    param_1 = param_1 + 1;
  } while( true );
}


