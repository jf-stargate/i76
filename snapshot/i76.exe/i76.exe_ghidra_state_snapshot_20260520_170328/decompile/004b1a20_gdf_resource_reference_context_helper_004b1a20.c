/*
 * Program: i76.exe
 * Function: gdf_resource_reference_context_helper_004b1a20
 * Entry: 004b1a20
 * Signature: undefined __cdecl gdf_resource_reference_context_helper_004b1a20(char * param_1)
 */


/* cgpt readability rename set E v17: Readability pass set E: gdf resource reference context helper
   based on adjacent named subsystem context. */

void __cdecl gdf_resource_reference_context_helper_004b1a20(char *param_1)

{
  char cVar1;
  byte bVar2;
  bool bVar3;
  undefined3 extraout_var;
  int iVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  char *pcVar8;
  char *pcVar9;
  char *pcVar10;
  uint *local_32c;
  int local_328;
  char local_324 [16];
  char local_314 [4];
  char local_310 [16];
  byte local_300 [256];
  char local_200 [256];
  char local_100 [256];
  
  if (((byte)DAT_00654b98 & 2) == 0) {
    _splitpath(param_1,local_314,local_100,local_310,local_200);
    uVar5 = 0xffffffff;
    pcVar8 = local_310;
    do {
      pcVar10 = pcVar8;
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      pcVar10 = pcVar8 + 1;
      cVar1 = *pcVar8;
      pcVar8 = pcVar10;
    } while (cVar1 != '\0');
    uVar5 = ~uVar5;
    pcVar8 = pcVar10 + -uVar5;
    pcVar10 = local_324;
    for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined4 *)pcVar10 = *(undefined4 *)pcVar8;
      pcVar8 = pcVar8 + 4;
      pcVar10 = pcVar10 + 4;
    }
    for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
      *pcVar10 = *pcVar8;
      pcVar8 = pcVar8 + 1;
      pcVar10 = pcVar10 + 1;
    }
    uVar5 = 0xffffffff;
    pcVar8 = &DAT_004fff10;
    do {
      pcVar10 = pcVar8;
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      pcVar10 = pcVar8 + 1;
      cVar1 = *pcVar8;
      pcVar8 = pcVar10;
    } while (cVar1 != '\0');
    uVar5 = ~uVar5;
    iVar7 = -1;
    pcVar8 = local_324;
    do {
      pcVar9 = pcVar8;
      if (iVar7 == 0) break;
      iVar7 = iVar7 + -1;
      pcVar9 = pcVar8 + 1;
      cVar1 = *pcVar8;
      pcVar8 = pcVar9;
    } while (cVar1 != '\0');
    pcVar8 = pcVar10 + -uVar5;
    pcVar10 = pcVar9 + -1;
    for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined4 *)pcVar10 = *(undefined4 *)pcVar8;
      pcVar8 = pcVar8 + 4;
      pcVar10 = pcVar10 + 4;
    }
    for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
      *pcVar10 = *pcVar8;
      pcVar8 = pcVar8 + 1;
      pcVar10 = pcVar10 + 1;
    }
    bVar3 = resource_exists_in_cache_or_search_paths(local_324);
    if ((CONCAT31(extraout_var,bVar3) != 0) &&
       (local_32c = open_resource_file_into_memory(local_324), local_32c != (uint *)0x0)) {
      local_328 = get_loaded_resource_file_size(local_324);
      iVar7 = system_cutscene_memory_context_helper_00499110
                        ((int *)&local_32c,local_300,&local_328,0xff);
      while (iVar7 != 0) {
        if (local_300[0] != 0x23) {
          iVar7 = 0;
          bVar2 = local_300[0];
          while (bVar2 != 0) {
            iVar4 = _ismbcspace((int)(char)local_300[iVar7]);
            if (iVar4 != 0) {
              local_300[iVar7] = 0;
              break;
            }
            iVar4 = iVar7 + 1;
            iVar7 = iVar7 + 1;
            bVar2 = local_300[iVar4];
          }
          append_salvage_resource_reference_for_mission((char *)local_300,0xffffffff,1);
        }
        iVar7 = system_cutscene_memory_context_helper_00499110
                          ((int *)&local_32c,local_300,&local_328,0xff);
      }
      release_resource_file_reference(local_324);
    }
  }
  return;
}


