/*
 * Program: i76shell.dll
 * Function: write_user_mel_file
 * Entry: 10033120
 * Signature: undefined4 __cdecl write_user_mel_file(char * param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4, char * param_5)
 */


undefined4 __cdecl
write_user_mel_file(char *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                   char *param_5)

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
  
  local_50 = param_2;
  local_44 = param_4;
  local_4c = *(undefined4 *)(DAT_100c5ad8 + 0x38);
  local_48 = param_3;
  uVar2 = 0xffffffff;
  do {
    pcVar4 = param_1;
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    pcVar4 = param_1 + 1;
    cVar1 = *param_1;
    param_1 = pcVar4;
  } while (cVar1 != '\0');
  uVar2 = ~uVar2;
  pcVar4 = pcVar4 + -uVar2;
  pcVar5 = local_20;
  for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(undefined4 *)pcVar5 = *(undefined4 *)pcVar4;
    pcVar4 = pcVar4 + 4;
    pcVar5 = pcVar5 + 4;
  }
  for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *pcVar5 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    pcVar5 = pcVar5 + 1;
  }
  uVar2 = 0xffffffff;
  do {
    pcVar4 = param_5;
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    pcVar4 = param_5 + 1;
    cVar1 = *param_5;
    param_5 = pcVar4;
  } while (cVar1 != '\0');
  uVar2 = ~uVar2;
  pcVar4 = pcVar4 + -uVar2;
  pcVar5 = local_40;
  for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(undefined4 *)pcVar5 = *(undefined4 *)pcVar4;
    pcVar4 = pcVar4 + 4;
    pcVar5 = pcVar5 + 4;
  }
  for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *pcVar5 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    pcVar5 = pcVar5 + 1;
  }
  _File = fopen(s_user_mel_1004cd3c,s_wb_1004cd38);
  if (_File == (FILE *)0x0) {
    return 0;
  }
  fwrite(&local_50,1,0x50,_File);
  fclose(_File);
  return 1;
}


