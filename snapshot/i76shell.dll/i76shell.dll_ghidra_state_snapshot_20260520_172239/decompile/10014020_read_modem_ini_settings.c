/*
 * Program: i76shell.dll
 * Function: read_modem_ini_settings
 * Entry: 10014020
 * Signature: undefined4 __stdcall read_modem_ini_settings(void)
 */


undefined4 read_modem_ini_settings(void)

{
  char cVar1;
  FILE *_File;
  uint uVar2;
  uint uVar3;
  char *pcVar4;
  char *pcVar5;
  
  _File = fopen(s_modem_ini_10047108,s_rb_10047104);
  if (_File == (FILE *)0x0) {
    DAT_10057a88 = DAT_10046fc0;
    DAT_10057a3c = 2;
    DAT_10057a8c = 2;
    DAT_10057a80 = 2;
    uVar2 = 0xffffffff;
    DAT_10057ad4 = 1;
    pcVar4 = &DAT_10047114;
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
    pcVar5 = &DAT_10057a40;
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
    pcVar4 = &DAT_10047118;
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
    pcVar5 = (char *)&DAT_10057a94;
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
    return 0;
  }
  fread(&DAT_10057a88,0x4c,1,_File);
  if (DAT_10057a88 < 0x4b01) {
    if (DAT_10057a88 == 0x4b00) {
      DAT_10057a3c = 1;
      goto LAB_100140c3;
    }
    if (DAT_10057a88 == 0x3840) {
      DAT_10057a3c = 0;
      goto LAB_100140c3;
    }
  }
  else {
    if (DAT_10057a88 == 0x7080) {
      DAT_10057a3c = 2;
      goto LAB_100140c3;
    }
    if (DAT_10057a88 == 0x8278) {
      DAT_10057a3c = 3;
      goto LAB_100140c3;
    }
    if (DAT_10057a88 == 0x9790) {
      DAT_10057a3c = 4;
      goto LAB_100140c3;
    }
  }
  DAT_10057a3c = 5;
LAB_100140c3:
  DAT_10057a80 = DAT_10057a8c;
  DAT_10057ad4 = DAT_10057a90;
  uVar2 = 0xffffffff;
  pcVar4 = (char *)&DAT_10057a94;
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
  pcVar5 = &DAT_10057a40;
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
  fclose(_File);
  return 1;
}


