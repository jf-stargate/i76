/*
 * Program: i76.exe
 * Function: zfsf_payload_wrapper_context_helper_004b9e40
 * Entry: 004b9e40
 * Signature: uint __cdecl zfsf_payload_wrapper_context_helper_004b9e40(char * param_1, char * param_2)
 */


/* cgpt label refinement v20: was zfsf_record_payload_wrapper_context_helper_004b9e40. Shorten
   readability label. */

uint __cdecl zfsf_payload_wrapper_context_helper_004b9e40(char *param_1,char *param_2)

{
  char *pcVar1;
  char *pcVar2;
  char cVar3;
  char cVar4;
  uint uVar5;
  int iVar6;
  bool bVar7;
  bool bVar8;
  
  cVar4 = *param_2;
  if (cVar4 == '\0') {
    return (uint)(*param_1 == '\0');
  }
  while (cVar3 = *param_1, cVar3 != '\0') {
    switch(cVar4) {
    case '*':
      if ((param_2[1] != '\0') &&
         (uVar5 = zfsf_payload_wrapper_context_helper_004b9e40(param_1,param_2 + 1), uVar5 == 0)) {
        do {
          pcVar1 = param_1 + 1;
          param_1 = param_1 + 1;
          if (*pcVar1 == '\0') {
            return 0xffffffff;
          }
          uVar5 = zfsf_payload_wrapper_context_helper_004b9e40(param_1,param_2 + 1);
        } while (uVar5 == 0);
        return 1;
      }
      return 1;
    case '?':
      break;
    case '[':
      pcVar1 = param_2 + 1;
      if (*pcVar1 == '!') {
        param_2 = param_2 + 1;
      }
      pcVar2 = param_2 + 1;
      bVar7 = false;
      param_2 = param_2 + 1;
      iVar6 = 0x100;
      cVar4 = *pcVar2;
      while ((cVar4 != '\0' && (cVar4 != ']'))) {
        if (cVar4 == '-') {
          cVar4 = param_2[1];
          param_2 = param_2 + 1;
          if ((cVar4 < cVar3) || (cVar3 < iVar6)) {
            bVar8 = false;
          }
          else {
            bVar8 = true;
          }
        }
        else {
          bVar8 = cVar3 == cVar4;
        }
        if (bVar8) {
          bVar7 = true;
        }
        param_2 = param_2 + 1;
        iVar6 = (int)cVar4;
        cVar4 = *param_2;
      }
      if (bVar7 == (*pcVar1 == '!')) {
        return 0;
      }
      break;
    case '\\':
      param_2 = param_2 + 1;
    default:
      if (cVar3 != *param_2) {
        return 0;
      }
    }
    cVar4 = param_2[1];
    param_1 = param_1 + 1;
    param_2 = param_2 + 1;
    if (cVar4 == '\0') {
      return (uint)(*param_1 == '\0');
    }
  }
  if (*param_2 != '*') {
    return 0xffffffff;
  }
  if (param_2[1] != '\0') {
    return 0xffffffff;
  }
  return 1;
}


