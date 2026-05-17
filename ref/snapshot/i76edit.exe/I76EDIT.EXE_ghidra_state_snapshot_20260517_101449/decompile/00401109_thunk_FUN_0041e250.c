/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0041e250
 * Entry: 00401109
 * Signature: undefined __stdcall thunk_FUN_0041e250(int param_1, int param_2)
 */


void thunk_FUN_0041e250(int param_1,int param_2)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  undefined4 *puVar6;
  char *pcVar7;
  char *pcVar8;
  char acStack_200 [512];
  
  pcVar5 = acStack_200;
  for (iVar2 = 0x80; iVar2 != 0; iVar2 = iVar2 + -1) {
    pcVar5[0] = '\0';
    pcVar5[1] = '\0';
    pcVar5[2] = '\0';
    pcVar5[3] = '\0';
    pcVar5 = pcVar5 + 4;
  }
  _sprintf(acStack_200,s_X___d__Y___d__00436a0c,param_1 * 5,param_2 * 5);
  puVar6 = (undefined4 *)&DAT_0043be28;
  for (iVar2 = 0x40; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar6 = 0;
    puVar6 = puVar6 + 1;
  }
  uVar3 = 0xffffffff;
  pcVar5 = acStack_200;
  do {
    pcVar8 = pcVar5;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar8 = pcVar5 + 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar8;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  iVar2 = -1;
  pcVar5 = &DAT_0043be28;
  do {
    pcVar7 = pcVar5;
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    pcVar7 = pcVar5 + 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar7;
  } while (cVar1 != '\0');
  pcVar5 = pcVar8 + -uVar3;
  pcVar8 = pcVar7 + -1;
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pcVar8 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar8 = pcVar8 + 1;
  }
  uVar3 = 0xffffffff;
  pcVar5 = (char *)&DAT_0043bd28;
  do {
    pcVar8 = pcVar5;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar8 = pcVar5 + 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar8;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  iVar2 = -1;
  pcVar5 = acStack_200;
  do {
    pcVar7 = pcVar5;
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    pcVar7 = pcVar5 + 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar7;
  } while (cVar1 != '\0');
  pcVar5 = pcVar8 + -uVar3;
  pcVar8 = pcVar7 + -1;
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pcVar8 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar8 = pcVar8 + 1;
  }
  SendMessageA(DAT_016423ac,0x401,0,(LPARAM)acStack_200);
  UpdateWindow(DAT_016423ac);
  return;
}


