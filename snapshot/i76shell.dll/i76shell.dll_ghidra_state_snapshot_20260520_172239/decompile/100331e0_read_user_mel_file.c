/*
 * Program: i76shell.dll
 * Function: read_user_mel_file
 * Entry: 100331e0
 * Signature: undefined4 __cdecl read_user_mel_file(char * param_1, char * param_2, undefined4 * param_3, undefined4 * param_4, undefined4 * param_5, char * param_6)
 */


undefined4 __cdecl
read_user_mel_file(char *param_1,char *param_2,undefined4 *param_3,undefined4 *param_4,
                  undefined4 *param_5,char *param_6)

{
  char cVar1;
  FILE *_File;
  uint uVar2;
  uint uVar3;
  char *pcVar4;
  char *pcVar5;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  char local_40 [32];
  char local_20 [32];
  
  _File = fopen(s_user_mel_1004cd4c,s_rb_1004cd48);
  if (_File == (FILE *)0x0) {
    return 0;
  }
  fread(&local_50,1,0x50,_File);
  fclose(_File);
  uVar2 = 0xffffffff;
  pcVar4 = local_20;
  do {
    pcVar5 = pcVar4;
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    pcVar5 = pcVar4 + 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar5;
  } while (cVar1 != '\0');
  uVar2 = ~uVar2;
  pcVar4 = pcVar5 + -uVar2;
  for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(undefined4 *)param_1 = *(undefined4 *)pcVar4;
    pcVar4 = pcVar4 + 4;
    param_1 = param_1 + 4;
  }
  for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *param_1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    param_1 = param_1 + 1;
  }
  uVar2 = 0xffffffff;
  pcVar4 = local_20;
  do {
    pcVar5 = pcVar4;
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    pcVar5 = pcVar4 + 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar5;
  } while (cVar1 != '\0');
  uVar2 = ~uVar2;
  pcVar4 = pcVar5 + -uVar2;
  for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(undefined4 *)param_2 = *(undefined4 *)pcVar4;
    pcVar4 = pcVar4 + 4;
    param_2 = param_2 + 4;
  }
  for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *param_2 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    param_2 = param_2 + 1;
  }
  uVar2 = 0xffffffff;
  pcVar4 = local_40;
  do {
    pcVar5 = pcVar4;
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    pcVar5 = pcVar4 + 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar5;
  } while (cVar1 != '\0');
  uVar2 = ~uVar2;
  pcVar4 = pcVar5 + -uVar2;
  for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(undefined4 *)param_6 = *(undefined4 *)pcVar4;
    pcVar4 = pcVar4 + 4;
    param_6 = param_6 + 4;
  }
  for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *param_6 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    param_6 = param_6 + 1;
  }
  *param_3 = local_50;
  *param_4 = local_48;
  *param_5 = local_44;
  *(undefined4 *)(DAT_100c5ad8 + 0x38) = local_4c;
  return 1;
}


