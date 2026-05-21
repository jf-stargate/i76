/*
 * Program: i76shell.dll
 * Function: initialize_builtin_vehicle_catalog
 * Entry: 10017f80
 * Signature: undefined __stdcall initialize_builtin_vehicle_catalog(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void initialize_builtin_vehicle_catalog(void)

{
  char cVar1;
  undefined *puVar2;
  char *pcVar3;
  char *pcVar4;
  uint uVar5;
  uint uVar6;
  char *pcVar7;
  
  pcVar3 = (char *)resolve_localized_shell_string_cached
                             (*(size_t **)PTR_DAT_10041ed4,s_Stock_10047c44);
  pcVar4 = (char *)resolve_localized_shell_string_cached
                             (*(size_t **)PTR_DAT_10041ed4,s_Jefferson_Sovereign_10047c4c);
  uVar5 = 0xffffffff;
  do {
    pcVar7 = pcVar4;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar7 = pcVar4 + 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar7;
  } while (cVar1 != '\0');
  uVar5 = ~uVar5;
  pcVar4 = pcVar7 + -uVar5;
  pcVar7 = (char *)&DAT_100cda14;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar7 = *(undefined4 *)pcVar4;
    pcVar4 = pcVar4 + 4;
    pcVar7 = pcVar7 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar7 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    pcVar7 = pcVar7 + 1;
  }
  uVar5 = 0xffffffff;
  do {
    pcVar4 = pcVar3;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar4 = pcVar3 + 1;
    cVar1 = *pcVar3;
    pcVar3 = pcVar4;
  } while (cVar1 != '\0');
  uVar5 = ~uVar5;
  pcVar3 = pcVar4 + -uVar5;
  pcVar4 = (char *)&DAT_100cca74;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar4 = *(undefined4 *)pcVar3;
    pcVar3 = pcVar3 + 4;
    pcVar4 = pcVar4 + 4;
  }
  for (uVar5 = uVar5 & 3; puVar2 = PTR_DAT_10041ed4, uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar4 = *pcVar3;
    pcVar3 = pcVar3 + 1;
    pcVar4 = pcVar4 + 1;
  }
  uVar5 = 0xffffffff;
  pcVar3 = &DAT_10047c38;
  do {
    pcVar4 = pcVar3;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar4 = pcVar3 + 1;
    cVar1 = *pcVar3;
    pcVar3 = pcVar4;
  } while (cVar1 != '\0');
  uVar5 = ~uVar5;
  pcVar3 = pcVar4 + -uVar5;
  pcVar4 = (char *)&DAT_100ce9b4;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar4 = *(undefined4 *)pcVar3;
    pcVar3 = pcVar3 + 4;
    pcVar4 = pcVar4 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar4 = *pcVar3;
    pcVar3 = pcVar3 + 1;
    pcVar4 = pcVar4 + 1;
  }
  pcVar3 = (char *)resolve_localized_shell_string_cached
                             (*(size_t **)puVar2,s_Stock__Bondo__10047c6c);
  pcVar4 = (char *)resolve_localized_shell_string_cached
                             (*(size_t **)PTR_DAT_10041ed4,s_Courcheval_Cameo_10047c7c);
  uVar5 = 0xffffffff;
  do {
    pcVar7 = pcVar4;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar7 = pcVar4 + 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar7;
  } while (cVar1 != '\0');
  uVar5 = ~uVar5;
  pcVar4 = pcVar7 + -uVar5;
  pcVar7 = (char *)&DAT_100cdadc;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar7 = *(undefined4 *)pcVar4;
    pcVar4 = pcVar4 + 4;
    pcVar7 = pcVar7 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar7 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    pcVar7 = pcVar7 + 1;
  }
  uVar5 = 0xffffffff;
  do {
    pcVar4 = pcVar3;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar4 = pcVar3 + 1;
    cVar1 = *pcVar3;
    pcVar3 = pcVar4;
  } while (cVar1 != '\0');
  uVar5 = ~uVar5;
  pcVar3 = pcVar4 + -uVar5;
  pcVar4 = (char *)&DAT_100ccb3c;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar4 = *(undefined4 *)pcVar3;
    pcVar3 = pcVar3 + 4;
    pcVar4 = pcVar4 + 4;
  }
  for (uVar5 = uVar5 & 3; puVar2 = PTR_DAT_10041ed4, uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar4 = *pcVar3;
    pcVar3 = pcVar3 + 1;
    pcVar4 = pcVar4 + 1;
  }
  uVar5 = 0xffffffff;
  pcVar3 = &DAT_10047c60;
  do {
    pcVar4 = pcVar3;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar4 = pcVar3 + 1;
    cVar1 = *pcVar3;
    pcVar3 = pcVar4;
  } while (cVar1 != '\0');
  uVar5 = ~uVar5;
  pcVar3 = pcVar4 + -uVar5;
  pcVar4 = (char *)&DAT_100cea7c;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar4 = *(undefined4 *)pcVar3;
    pcVar3 = pcVar3 + 4;
    pcVar4 = pcVar4 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar4 = *pcVar3;
    pcVar3 = pcVar3 + 1;
    pcVar4 = pcVar4 + 1;
  }
  pcVar3 = (char *)resolve_localized_shell_string_cached
                             (*(size_t **)puVar2,s_Stock__Green__10047c9c);
  pcVar4 = (char *)resolve_localized_shell_string_cached
                             (*(size_t **)PTR_DAT_10041ed4,s_Phaedra_Pony_10047cac);
  uVar5 = 0xffffffff;
  do {
    pcVar7 = pcVar4;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar7 = pcVar4 + 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar7;
  } while (cVar1 != '\0');
  uVar5 = ~uVar5;
  pcVar4 = pcVar7 + -uVar5;
  pcVar7 = (char *)&DAT_100cdba4;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar7 = *(undefined4 *)pcVar4;
    pcVar4 = pcVar4 + 4;
    pcVar7 = pcVar7 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar7 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    pcVar7 = pcVar7 + 1;
  }
  uVar5 = 0xffffffff;
  do {
    pcVar4 = pcVar3;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar4 = pcVar3 + 1;
    cVar1 = *pcVar3;
    pcVar3 = pcVar4;
  } while (cVar1 != '\0');
  uVar5 = ~uVar5;
  pcVar3 = pcVar4 + -uVar5;
  pcVar4 = (char *)&DAT_100ccc04;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar4 = *(undefined4 *)pcVar3;
    pcVar3 = pcVar3 + 4;
    pcVar4 = pcVar4 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar4 = *pcVar3;
    pcVar3 = pcVar3 + 1;
    pcVar4 = pcVar4 + 1;
  }
  uVar5 = 0xffffffff;
  pcVar3 = &DAT_10047c90;
  do {
    pcVar4 = pcVar3;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar4 = pcVar3 + 1;
    cVar1 = *pcVar3;
    pcVar3 = pcVar4;
  } while (cVar1 != '\0');
  uVar5 = ~uVar5;
  pcVar3 = pcVar4 + -uVar5;
  pcVar4 = (char *)&DAT_100ceb44;
  for (uVar6 = uVar5 >> 2; puVar2 = PTR_DAT_10041ed4, uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar4 = *(undefined4 *)pcVar3;
    pcVar3 = pcVar3 + 4;
    pcVar4 = pcVar4 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar4 = *pcVar3;
    pcVar3 = pcVar3 + 1;
    pcVar4 = pcVar4 + 1;
  }
  pcVar3 = (char *)resolve_localized_shell_string_cached(*(size_t **)puVar2,s_Stock_10047cc8);
  pcVar4 = (char *)resolve_localized_shell_string_cached
                             (*(size_t **)PTR_DAT_10041ed4,s_Picard_Jackrabit_10047cd0);
  uVar5 = 0xffffffff;
  do {
    pcVar7 = pcVar4;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar7 = pcVar4 + 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar7;
  } while (cVar1 != '\0');
  uVar5 = ~uVar5;
  pcVar4 = pcVar7 + -uVar5;
  pcVar7 = (char *)&DAT_100cdc6c;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar7 = *(undefined4 *)pcVar4;
    pcVar4 = pcVar4 + 4;
    pcVar7 = pcVar7 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar7 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    pcVar7 = pcVar7 + 1;
  }
  uVar5 = 0xffffffff;
  do {
    pcVar4 = pcVar3;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar4 = pcVar3 + 1;
    cVar1 = *pcVar3;
    pcVar3 = pcVar4;
  } while (cVar1 != '\0');
  uVar5 = ~uVar5;
  pcVar3 = pcVar4 + -uVar5;
  pcVar4 = (char *)&DAT_100ccccc;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar4 = *(undefined4 *)pcVar3;
    pcVar3 = pcVar3 + 4;
    pcVar4 = pcVar4 + 4;
  }
  for (uVar5 = uVar5 & 3; puVar2 = PTR_DAT_10041ed4, uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar4 = *pcVar3;
    pcVar3 = pcVar3 + 1;
    pcVar4 = pcVar4 + 1;
  }
  uVar5 = 0xffffffff;
  pcVar3 = &DAT_10047cbc;
  do {
    pcVar4 = pcVar3;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar4 = pcVar3 + 1;
    cVar1 = *pcVar3;
    pcVar3 = pcVar4;
  } while (cVar1 != '\0');
  uVar5 = ~uVar5;
  pcVar3 = pcVar4 + -uVar5;
  pcVar4 = (char *)&DAT_100cec0c;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar4 = *(undefined4 *)pcVar3;
    pcVar3 = pcVar3 + 4;
    pcVar4 = pcVar4 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar4 = *pcVar3;
    pcVar3 = pcVar3 + 1;
    pcVar4 = pcVar4 + 1;
  }
  pcVar3 = (char *)resolve_localized_shell_string_cached(*(size_t **)puVar2,s_Stock_10047cf0);
  pcVar4 = (char *)resolve_localized_shell_string_cached
                             (*(size_t **)PTR_DAT_10041ed4,s_Phaedra_Palomino_10047cf8);
  uVar5 = 0xffffffff;
  do {
    pcVar7 = pcVar4;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar7 = pcVar4 + 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar7;
  } while (cVar1 != '\0');
  uVar5 = ~uVar5;
  pcVar4 = pcVar7 + -uVar5;
  pcVar7 = (char *)&DAT_100cdd34;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar7 = *(undefined4 *)pcVar4;
    pcVar4 = pcVar4 + 4;
    pcVar7 = pcVar7 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar7 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    pcVar7 = pcVar7 + 1;
  }
  uVar5 = 0xffffffff;
  do {
    pcVar4 = pcVar3;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar4 = pcVar3 + 1;
    cVar1 = *pcVar3;
    pcVar3 = pcVar4;
  } while (cVar1 != '\0');
  uVar5 = ~uVar5;
  pcVar3 = pcVar4 + -uVar5;
  pcVar4 = (char *)&DAT_100ccd94;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar4 = *(undefined4 *)pcVar3;
    pcVar3 = pcVar3 + 4;
    pcVar4 = pcVar4 + 4;
  }
  for (uVar5 = uVar5 & 3; puVar2 = PTR_DAT_10041ed4, uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar4 = *pcVar3;
    pcVar3 = pcVar3 + 1;
    pcVar4 = pcVar4 + 1;
  }
  uVar5 = 0xffffffff;
  pcVar3 = &DAT_10047ce4;
  do {
    pcVar4 = pcVar3;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar4 = pcVar3 + 1;
    cVar1 = *pcVar3;
    pcVar3 = pcVar4;
  } while (cVar1 != '\0');
  uVar5 = ~uVar5;
  pcVar3 = pcVar4 + -uVar5;
  pcVar4 = (char *)&DAT_100cecd4;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar4 = *(undefined4 *)pcVar3;
    pcVar3 = pcVar3 + 4;
    pcVar4 = pcVar4 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar4 = *pcVar3;
    pcVar3 = pcVar3 + 1;
    pcVar4 = pcVar4 + 1;
  }
  pcVar3 = (char *)resolve_localized_shell_string_cached(*(size_t **)puVar2,s_Stock__Blue__10047d18)
  ;
  pcVar4 = (char *)resolve_localized_shell_string_cached
                             (*(size_t **)PTR_DAT_10041ed4,s_Picard_Piranha_10047d28);
  uVar5 = 0xffffffff;
  do {
    pcVar7 = pcVar4;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar7 = pcVar4 + 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar7;
  } while (cVar1 != '\0');
  uVar5 = ~uVar5;
  pcVar4 = pcVar7 + -uVar5;
  pcVar7 = (char *)&DAT_100cddfc;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar7 = *(undefined4 *)pcVar4;
    pcVar4 = pcVar4 + 4;
    pcVar7 = pcVar7 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar7 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    pcVar7 = pcVar7 + 1;
  }
  uVar5 = 0xffffffff;
  do {
    pcVar4 = pcVar3;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar4 = pcVar3 + 1;
    cVar1 = *pcVar3;
    pcVar3 = pcVar4;
  } while (cVar1 != '\0');
  uVar5 = ~uVar5;
  pcVar3 = pcVar4 + -uVar5;
  pcVar4 = (char *)&DAT_100cce5c;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar4 = *(undefined4 *)pcVar3;
    pcVar3 = pcVar3 + 4;
    pcVar4 = pcVar4 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar4 = *pcVar3;
    pcVar3 = pcVar3 + 1;
    pcVar4 = pcVar4 + 1;
  }
  uVar5 = 0xffffffff;
  pcVar3 = &DAT_10047d0c;
  do {
    pcVar4 = pcVar3;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar4 = pcVar3 + 1;
    cVar1 = *pcVar3;
    pcVar3 = pcVar4;
  } while (cVar1 != '\0');
  uVar5 = ~uVar5;
  pcVar3 = pcVar4 + -uVar5;
  pcVar4 = (char *)&DAT_100ced9c;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar4 = *(undefined4 *)pcVar3;
    pcVar3 = pcVar3 + 4;
    pcVar4 = pcVar4 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar4 = *pcVar3;
    pcVar3 = pcVar3 + 1;
    pcVar4 = pcVar4 + 1;
  }
  _DAT_100cca70 = 6;
  return;
}


