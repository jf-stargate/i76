/*
 * Program: i76.exe
 * Function: load_localized_m16_texture_resource
 * Entry: 00471e50
 * Signature: undefined __cdecl load_localized_m16_texture_resource(int * param_1, char * param_2)
 */


/* cgpt whole-binary semantic rename v1: references .m16 and texture loading path */

void __cdecl load_localized_m16_texture_resource(int *param_1,char *param_2)

{
  char cVar1;
  char *pcVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  char *pcVar6;
  char *pcVar7;
  char local_10 [16];
  
  if (*param_1 != 0) {
    release_vqm_texture_cache_reference_by_name(param_2);
    *param_1 = 0;
    if (param_1[1] != 0) {
      uVar3 = 0xffffffff;
      do {
        pcVar2 = param_2;
        if (uVar3 == 0) break;
        uVar3 = uVar3 - 1;
        pcVar2 = param_2 + 1;
        cVar1 = *param_2;
        param_2 = pcVar2;
      } while (cVar1 != '\0');
      uVar3 = ~uVar3;
      pcVar2 = pcVar2 + -uVar3;
      pcVar7 = local_10;
      for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
        *(undefined4 *)pcVar7 = *(undefined4 *)pcVar2;
        pcVar2 = pcVar2 + 4;
        pcVar7 = pcVar7 + 4;
      }
      for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *pcVar7 = *pcVar2;
        pcVar2 = pcVar2 + 1;
        pcVar7 = pcVar7 + 1;
      }
      pcVar2 = strrchr(local_10,0x2e);
      if (pcVar2 != (char *)0x0) {
        *pcVar2 = '\0';
      }
      uVar3 = 0xffffffff;
      pcVar2 = s__m16_004f8ca4;
      do {
        pcVar7 = pcVar2;
        if (uVar3 == 0) break;
        uVar3 = uVar3 - 1;
        pcVar7 = pcVar2 + 1;
        cVar1 = *pcVar2;
        pcVar2 = pcVar7;
      } while (cVar1 != '\0');
      uVar3 = ~uVar3;
      iVar5 = -1;
      pcVar2 = local_10;
      do {
        pcVar6 = pcVar2;
        if (iVar5 == 0) break;
        iVar5 = iVar5 + -1;
        pcVar6 = pcVar2 + 1;
        cVar1 = *pcVar2;
        pcVar2 = pcVar6;
      } while (cVar1 != '\0');
      pcVar2 = pcVar7 + -uVar3;
      pcVar7 = pcVar6 + -1;
      for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
        *(undefined4 *)pcVar7 = *(undefined4 *)pcVar2;
        pcVar2 = pcVar2 + 4;
        pcVar7 = pcVar7 + 4;
      }
      for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *pcVar7 = *pcVar2;
        pcVar2 = pcVar2 + 1;
        pcVar7 = pcVar7 + 1;
      }
      release_resource_file_reference(local_10);
      param_1[1] = 0;
    }
  }
  return;
}


