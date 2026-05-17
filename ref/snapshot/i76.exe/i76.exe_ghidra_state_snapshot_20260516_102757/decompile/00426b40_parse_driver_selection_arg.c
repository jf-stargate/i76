/*
 * Program: i76.exe
 * Function: parse_driver_selection_arg
 * Entry: 00426b40
 * Signature: undefined __cdecl parse_driver_selection_arg(char * param_1, char * param_2, undefined4 param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* i76 second-pass rename
   old_name: FUN_00426b40
   suggested_name: parse_driver_selection_arg
   basis: Checks RASTER/SOUND/DRIVER option strings. */

void __cdecl parse_driver_selection_arg(char *param_1,char *param_2,undefined4 param_3)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  
  iVar2 = _stricmp(param_1,s_RASTER_004c2628);
  if (iVar2 != 0) {
    iVar2 = _stricmp(param_1,s_SOUND_004ede6c);
    if (iVar2 != 0) {
      iVar2 = _stricmp(param_1,s_DRIVER_004ede64);
      if (iVar2 == 0) {
        uVar3 = 0xffffffff;
        DAT_00524690 = 1;
        do {
          pcVar5 = param_2;
          if (uVar3 == 0) break;
          uVar3 = uVar3 - 1;
          pcVar5 = param_2 + 1;
          cVar1 = *param_2;
          param_2 = pcVar5;
        } while (cVar1 != '\0');
        uVar3 = ~uVar3;
        pcVar5 = pcVar5 + -uVar3;
        pcVar6 = (char *)&DAT_005246b4;
        for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
          *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
          pcVar5 = pcVar5 + 4;
          pcVar6 = pcVar6 + 4;
        }
        for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
          *pcVar6 = *pcVar5;
          pcVar5 = pcVar5 + 1;
          pcVar6 = pcVar6 + 1;
        }
      }
      return;
    }
    _DAT_005246d8 = 1;
    if (param_2 == (char *)0x0) {
      _DAT_0052471c = param_3;
      return;
    }
    uVar3 = 0xffffffff;
    do {
      pcVar5 = param_2;
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      pcVar5 = param_2 + 1;
      cVar1 = *param_2;
      param_2 = pcVar5;
    } while (cVar1 != '\0');
    uVar3 = ~uVar3;
    pcVar5 = pcVar5 + -uVar3;
    pcVar6 = (char *)&DAT_005246dc;
    for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
      pcVar5 = pcVar5 + 4;
      pcVar6 = pcVar6 + 4;
    }
    for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *pcVar6 = *pcVar5;
      pcVar5 = pcVar5 + 1;
      pcVar6 = pcVar6 + 1;
    }
    return;
  }
  DAT_00524690 = 1;
  if (param_2 == (char *)0x0) {
    DAT_005246d4 = param_3;
    return;
  }
  uVar3 = 0xffffffff;
  do {
    pcVar5 = param_2;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar5 = param_2 + 1;
    cVar1 = *param_2;
    param_2 = pcVar5;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  pcVar5 = pcVar5 + -uVar3;
  pcVar6 = (char *)&DAT_00524694;
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcVar6 = pcVar6 + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pcVar6 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar6 = pcVar6 + 1;
  }
  return;
}


