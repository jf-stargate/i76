/*
 * Program: i76.exe
 * Function: load_horizon_texture_manifest
 * Entry: 00401540
 * Signature: undefined __cdecl load_horizon_texture_manifest(char * param_1)
 */


/* cgpt whole-binary semantic rename v1: parses resource text into horizon texture slots; string
   evidence: Horizon Texture (%s) not found */

void __cdecl load_horizon_texture_manifest(char *param_1)

{
  char cVar1;
  uint *_Str;
  char *pcVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  char *pcVar7;
  undefined4 *puVar8;
  char *pcVar9;
  undefined4 local_108;
  undefined2 local_104;
  char local_100 [256];
  
  local_108 = DAT_004c20d0;
  local_104 = DAT_004c20d4;
  DAT_00504838 = 0;
  if (((param_1 == (char *)0x0) || (*param_1 == '\0')) ||
     (_Str = open_resource_file_into_memory(param_1), _Str == (uint *)0x0)) {
    return;
  }
  pcVar2 = strpbrk((char *)_Str,(char *)&local_108);
  pcVar6 = local_100;
  for (iVar3 = 0x3f; iVar3 != 0; iVar3 = iVar3 + -1) {
    pcVar6[0] = '\0';
    pcVar6[1] = '\0';
    pcVar6[2] = '\0';
    pcVar6[3] = '\0';
    pcVar6 = pcVar6 + 4;
  }
  pcVar6[0] = '\0';
  pcVar6[1] = '\0';
  pcVar6[2] = '\0';
  strncpy(local_100,(char *)_Str,(int)pcVar2 - (int)_Str);
  pcVar6 = (char *)&DAT_00504840;
  do {
    uVar4 = 0xffffffff;
    pcVar7 = local_100;
    do {
      pcVar9 = pcVar7;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      pcVar9 = pcVar7 + 1;
      cVar1 = *pcVar7;
      pcVar7 = pcVar9;
    } while (cVar1 != '\0');
    uVar4 = ~uVar4;
    pcVar7 = pcVar9 + -uVar4;
    pcVar9 = pcVar6;
    for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
      pcVar7 = pcVar7 + 4;
      pcVar9 = pcVar9 + 4;
    }
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pcVar9 = *pcVar7;
      pcVar7 = pcVar7 + 1;
      pcVar9 = pcVar9 + 1;
    }
    pcVar7 = pcVar2;
    if (pcVar6 + 0x18 == (char *)&DAT_005049c0) {
      release_resource_file_reference(param_1);
      puVar8 = (undefined4 *)&DAT_00504850;
      do {
        iVar3 = load_fullres_texture_list(puVar8,(byte *)(puVar8 + -4));
        if (iVar3 == 0) {
          report_error();
          return;
        }
        puVar8 = puVar8 + 6;
      } while ((int)puVar8 < 0x5049d0);
      DAT_00504838 = 1;
      return;
    }
    do {
      pcVar7 = pcVar7 + 1;
      if (*(int *)__mb_cur_max_exref < 2) {
        uVar4 = *(ushort *)(*(int *)_pctype_exref + *pcVar7 * 2) & 0x103;
      }
      else {
        uVar4 = _isctype((int)*pcVar7,0x103);
      }
    } while (uVar4 == 0);
    pcVar2 = strpbrk(pcVar7,(char *)&local_108);
    pcVar9 = local_100;
    for (iVar3 = 0x3f; iVar3 != 0; iVar3 = iVar3 + -1) {
      pcVar9[0] = '\0';
      pcVar9[1] = '\0';
      pcVar9[2] = '\0';
      pcVar9[3] = '\0';
      pcVar9 = pcVar9 + 4;
    }
    pcVar9[0] = '\0';
    pcVar9[1] = '\0';
    pcVar9[2] = '\0';
    strncpy(local_100,pcVar7,(int)pcVar2 - (int)pcVar7);
    pcVar6 = pcVar6 + 0x18;
  } while( true );
}


