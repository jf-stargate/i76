/*
 * Program: i76.exe
 * Function: load_texture_resource_resolving_vqm_cbk_to_buffer
 * Entry: 004478b0
 * Signature: undefined4 __cdecl load_texture_resource_resolving_vqm_cbk_to_buffer(char * param_1, uint * param_2, uint * param_3)
 */


/* [cgpt i76.exe GEO mesh/render renames v29; confidence=high] Non-cache/buffer form of texture
   loading path; resolves VQM/CBK into M16-like indexed image data. */

undefined4 __cdecl
load_texture_resource_resolving_vqm_cbk_to_buffer(char *param_1,uint *param_2,uint *param_3)

{
  char cVar1;
  char *pcVar2;
  uint *puVar3;
  uint *puVar4;
  uint *puVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  char *pcVar9;
  char *pcVar10;
  char local_10 [16];
  
  uVar6 = 0xffffffff;
  pcVar2 = param_1;
  do {
    pcVar10 = pcVar2;
    if (uVar6 == 0) break;
    uVar6 = uVar6 - 1;
    pcVar10 = pcVar2 + 1;
    cVar1 = *pcVar2;
    pcVar2 = pcVar10;
  } while (cVar1 != '\0');
  uVar6 = ~uVar6;
  pcVar2 = pcVar10 + -uVar6;
  pcVar10 = local_10;
  for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
    *(undefined4 *)pcVar10 = *(undefined4 *)pcVar2;
    pcVar2 = pcVar2 + 4;
    pcVar10 = pcVar10 + 4;
  }
  for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
    *pcVar10 = *pcVar2;
    pcVar2 = pcVar2 + 1;
    pcVar10 = pcVar10 + 1;
  }
  pcVar2 = strchr(local_10,0x2e);
  if (pcVar2 != (char *)0x0) {
    *pcVar2 = '\0';
  }
  uVar6 = 0xffffffff;
  pcVar2 = s__vqm_004f2698;
  do {
    pcVar10 = pcVar2;
    if (uVar6 == 0) break;
    uVar6 = uVar6 - 1;
    pcVar10 = pcVar2 + 1;
    cVar1 = *pcVar2;
    pcVar2 = pcVar10;
  } while (cVar1 != '\0');
  uVar6 = ~uVar6;
  iVar8 = -1;
  pcVar2 = local_10;
  do {
    pcVar9 = pcVar2;
    if (iVar8 == 0) break;
    iVar8 = iVar8 + -1;
    pcVar9 = pcVar2 + 1;
    cVar1 = *pcVar2;
    pcVar2 = pcVar9;
  } while (cVar1 != '\0');
  pcVar2 = pcVar10 + -uVar6;
  pcVar10 = pcVar9 + -1;
  for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
    *(undefined4 *)pcVar10 = *(undefined4 *)pcVar2;
    pcVar2 = pcVar2 + 4;
    pcVar10 = pcVar10 + 4;
  }
  for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
    *pcVar10 = *pcVar2;
    pcVar2 = pcVar2 + 1;
    pcVar10 = pcVar10 + 1;
  }
  if (g_resource_cache_prefer_directory_first == 0) {
    iVar8 = get_loaded_resource_file_size(local_10);
    if (iVar8 != 0) {
LAB_00447a07:
      puVar4 = open_resource_file_into_memory(local_10);
      puVar3 = puVar4 + 2;
      puVar5 = open_resource_file_into_memory((char *)puVar3);
      if (puVar5 == (uint *)0x0) {
        report_chunk_parse_error();
        release_resource_file_reference(local_10);
        *param_3 = 0;
        return 0;
      }
      uVar6 = puVar4[1] * *puVar4 + 0x18;
      if ((*param_3 <= uVar6) && (param_2 != (uint *)0x0)) {
        iVar8 = decode_vqm_cbk_4x4_blocks_to_indexed_pixels(puVar4,(int)puVar5,param_2,uVar6);
        if (iVar8 != 0) {
          release_resource_file_reference((char *)puVar3);
          release_resource_file_reference(local_10);
          *param_3 = uVar6;
          return 1;
        }
        report_chunk_parse_error();
        release_resource_file_reference((char *)puVar3);
        release_resource_file_reference(local_10);
        return 0;
      }
      release_resource_file_reference((char *)puVar3);
      release_resource_file_reference(local_10);
      *param_3 = uVar6;
      return 0;
    }
    uVar6 = get_loaded_resource_file_size(param_1);
    if (uVar6 == 0) {
      report_chunk_parse_error();
      *param_3 = 0;
      return 0;
    }
    if ((uVar6 < *param_3) || (param_2 == (uint *)0x0)) {
LAB_004479e6:
      *param_3 = uVar6;
      return 0;
    }
    puVar3 = open_resource_file_into_memory(param_1);
    for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
      *param_2 = *puVar3;
      puVar3 = puVar3 + 1;
      param_2 = param_2 + 1;
    }
  }
  else {
    uVar6 = get_loaded_resource_file_size(param_1);
    if (uVar6 == 0) {
      iVar8 = get_loaded_resource_file_size(local_10);
      if (iVar8 == 0) {
        report_chunk_parse_error();
        *param_3 = 0;
        return 0;
      }
      goto LAB_00447a07;
    }
    if ((uVar6 < *param_3) || (param_2 == (uint *)0x0)) goto LAB_004479e6;
    puVar3 = open_resource_file_into_memory(param_1);
    for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
      *param_2 = *puVar3;
      puVar3 = puVar3 + 1;
      param_2 = param_2 + 1;
    }
  }
  for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(char *)param_2 = (char)*puVar3;
    puVar3 = (uint *)((int)puVar3 + 1);
    param_2 = (uint *)((int)param_2 + 1);
  }
  release_resource_file_reference(param_1);
  return 1;
}


