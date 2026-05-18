/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0041f5d0
 * Entry: 004014ce
 * Signature: undefined4 __cdecl thunk_FUN_0041f5d0(char * param_1)
 */


undefined4 __cdecl thunk_FUN_0041f5d0(char *param_1)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  char *pcVar7;
  char acStack_80 [128];
  
  pcVar5 = acStack_80;
  for (iVar2 = 0x20; iVar2 != 0; iVar2 = iVar2 + -1) {
    pcVar5[0] = '\0';
    pcVar5[1] = '\0';
    pcVar5[2] = '\0';
    pcVar5[3] = '\0';
    pcVar5 = pcVar5 + 4;
  }
  uVar3 = 0xffffffff;
  do {
    pcVar5 = param_1;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar5 = param_1 + 1;
    cVar1 = *param_1;
    param_1 = pcVar5;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  iVar2 = -1;
  pcVar7 = acStack_80;
  do {
    pcVar6 = pcVar7;
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    pcVar6 = pcVar7 + 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar6;
  } while (cVar1 != '\0');
  pcVar5 = pcVar5 + -uVar3;
  pcVar7 = pcVar6 + -1;
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)pcVar7 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcVar7 = pcVar7 + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pcVar7 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar7 = pcVar7 + 1;
  }
  uVar3 = 0xffffffff;
  pcVar5 = acStack_80;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar5 + 1;
  } while (cVar1 != '\0');
  iVar2 = 0;
  if (0 < (int)(~uVar3 - 1)) {
    do {
      cVar1 = acStack_80[iVar2];
      if ((((cVar1 < '0') || ('9' < cVar1)) && ((cVar1 < 'A' || ('Z' < cVar1)))) &&
         (((cVar1 < 'a' || ('z' < cVar1)) && (cVar1 != '_')))) {
        return 0;
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < (int)(~uVar3 - 1));
  }
  return 1;
}


