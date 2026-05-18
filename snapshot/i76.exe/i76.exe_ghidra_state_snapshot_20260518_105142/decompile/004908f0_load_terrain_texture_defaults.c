/*
 * Program: i76.exe
 * Function: load_terrain_texture_defaults
 * Entry: 004908f0
 * Signature: undefined __cdecl load_terrain_texture_defaults(char * param_1)
 */


/* i76 second-pass rename
   old_name: FUN_004908f0
   suggested_name: load_terrain_texture_defaults
   basis: References terrain texture defaults terr256.map, terr128.map, terr16.map. */

void __cdecl load_terrain_texture_defaults(char *param_1)

{
  char *pcVar1;
  char *pcVar2;
  char cVar3;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  undefined **ppuVar7;
  char *pcVar8;
  
  if (*param_1 != '\0') {
    uVar4 = 0xffffffff;
    pcVar1 = param_1;
    do {
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      cVar3 = *pcVar1;
      pcVar1 = pcVar1 + 1;
    } while (cVar3 != '\0');
    if ((3 < ~uVar4 - 1) && (param_1[4] == '1')) {
      pcVar1 = (char *)&DAT_005a45c8;
      do {
        uVar4 = 0xffffffff;
        pcVar2 = param_1;
        do {
          pcVar8 = pcVar2;
          if (uVar4 == 0) break;
          uVar4 = uVar4 - 1;
          pcVar8 = pcVar2 + 1;
          cVar3 = *pcVar2;
          pcVar2 = pcVar8;
        } while (cVar3 != '\0');
        uVar4 = ~uVar4;
        pcVar6 = pcVar1 + 0x10;
        pcVar2 = pcVar8 + -uVar4;
        for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
          *(undefined4 *)pcVar1 = *(undefined4 *)pcVar2;
          pcVar2 = pcVar2 + 4;
          pcVar1 = pcVar1 + 4;
        }
        for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
          *pcVar1 = *pcVar2;
          pcVar2 = pcVar2 + 1;
          pcVar1 = pcVar1 + 1;
        }
        pcVar1 = pcVar6;
        if ((char *)0x5a4617 < pcVar6) {
          pcVar1 = &DAT_005a45cc;
          cVar3 = '\0';
          do {
            pcVar2 = pcVar1 + 0x10;
            *pcVar1 = cVar3 + '2';
            pcVar1 = pcVar2;
            cVar3 = cVar3 + '\x01';
          } while (pcVar2 < &DAT_005a461c);
          return;
        }
      } while( true );
    }
  }
  report_chunk_parse_error();
  ppuVar7 = &PTR_s_terr256_map_004fad58;
  pcVar1 = (char *)&DAT_005a45c8;
  do {
    pcVar2 = *ppuVar7;
    uVar4 = 0xffffffff;
    ppuVar7 = ppuVar7 + 1;
    do {
      pcVar8 = pcVar2;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      pcVar8 = pcVar2 + 1;
      cVar3 = *pcVar2;
      pcVar2 = pcVar8;
    } while (cVar3 != '\0');
    uVar4 = ~uVar4;
    pcVar2 = pcVar8 + -uVar4;
    pcVar8 = pcVar1;
    for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined4 *)pcVar8 = *(undefined4 *)pcVar2;
      pcVar2 = pcVar2 + 4;
      pcVar8 = pcVar8 + 4;
    }
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pcVar8 = *pcVar2;
      pcVar2 = pcVar2 + 1;
      pcVar8 = pcVar8 + 1;
    }
    pcVar1 = pcVar1 + 0x10;
    if ((undefined **)((int)&PTR_s_terr16_map_004fad68 + 3) < ppuVar7) {
      return;
    }
  } while( true );
}


